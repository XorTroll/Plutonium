#include <pu/ui/ui_Application.hpp>

namespace pu::ui {

    Application::Application(render::Renderer::Ref renderer) {
        this->renderer = renderer;
        // TODO: do it outside ctor, get result...?
        this->renderer->Initialize();
        this->is_shown = false;
        this->on_ipt_cb = {};
        this->in_render_over = false;
        this->ovl = nullptr;
        this->lyt = nullptr;
        this->loaded = false;
        this->render_over_fn = {};
        this->fade_alpha = 0xFF;
        this->fade_alpha_increment = DefaultFadeAlphaIncrement;
        padConfigureInput(1, HidNpadStyleSet_NpadStandard);
        padInitializeDefault(&this->input_pad);
    }

    void Application::Prepare() {
        if(!this->loaded) {
            this->OnLoad();
            this->loaded = true;
        }
    }

    i32 Application::CreateShowDialog(const std::string &title, const std::string &content, const std::vector<std::string> &opts, const bool use_last_opt_as_cancel, const std::string &icon_path) {
        auto dialog = Dialog::New(title, content);
        for(u32 i = 0; i < opts.size(); i++) {
            const auto &opt = opts.at(i);
            if(use_last_opt_as_cancel && (i == (opts.size() - 1))) {
                dialog->SetCancelOption(opt);
            }
            else {
                dialog->AddOption(opt);
            }
        }

        if(!icon_path.empty()) {
            dialog->SetIcon(icon_path);
        }

        const auto opt = this->ShowDialog(dialog);
        if(dialog->UserCancelled()) {
            return -1;
        }
        else if(!dialog->IsOk()) {
            return -2;
        }
        else {
            return opt;
        }
    }

    void Application::StartOverlayWithTimeout(Overlay::Ref ovl, const u64 ms) {
        if(this->ovl == nullptr) {
            this->ovl = ovl;
            this->ovl_timeout_ms = ms;
            this->ovl_start_time = std::chrono::steady_clock::now();
        }
    }

    void Application::EndOverlay() {
        if(this->ovl != nullptr) {
            this->ovl->NotifyEnding(false);
            this->ovl_timeout_ms = 0;
            this->ovl = nullptr;
        }
    }

    void Application::Show() {
        if(!this->CanBeShown()) {
            return;
        }

        this->is_shown = true;
        while(this->is_shown) {
            this->CallForRender();
        }
    }

    bool Application::CallForRender() {
        if(!this->CanBeShown()) {
            return false;
        }

        auto continue_render = true;
        this->renderer->InitializeRender(this->lyt->GetBackgroundColor());
        this->OnRender();
        if(this->in_render_over) {
            continue_render = (this->render_over_fn)(this->renderer);
            this->in_render_over = false;
            this->render_over_fn = {};
        }
        this->renderer->FinalizeRender();
        return continue_render;
    }

    bool Application::CallForRenderWithRenderOver(RenderOverFunction render_over_fn) {
        this->in_render_over = true;
        this->render_over_fn = render_over_fn;
        return this->CallForRender();
    }

    void Application::FadeIn() {
        this->fade_alpha = 0;
        while(true) {
            this->CallForRender();
            this->fade_alpha += this->fade_alpha_increment;
            if(this->fade_alpha > 0xFF) {
                this->fade_alpha = 0xFF;
                this->CallForRender();
                break;
            }
        }
    }

    void Application::FadeOut() {
        this->fade_alpha = 0xFF;
        while(true) {
            this->CallForRender();
            this->fade_alpha -= this->fade_alpha_increment;
            if(this->fade_alpha < 0) {
                this->fade_alpha = 0;
                this->CallForRender();
                break;
            }
        }
    }

    void Application::OnRender() {
        padUpdate(&this->input_pad);
        const auto keys_down = this->GetButtonsDown();
        const auto keys_up = this->GetButtonsUp();
        const auto keys_held = this->GetButtonsHeld();

        const auto tch_state = this->GetTouchState();
        TouchPoint tch_pos = {};
        if(tch_state.count > 0) {
            tch_pos = { tch_state.touches[0].x, tch_state.touches[0].y };
        }
        const auto sim_tch_pos = this->lyt->ConsumeSimulatedTouchPosition();
        if(!sim_tch_pos.IsEmpty()) {
            tch_pos = sim_tch_pos;
        }

        for(auto &render_cb: this->render_cbs) {
            if(render_cb) {
                render_cb();
            }
        }
        
        this->lyt->PreRender();

        for(auto &lyt_render_cb: this->lyt->GetRenderCallbacks()) {
            if(lyt_render_cb) {
                lyt_render_cb();
            }
        }

        if(!this->in_render_over) {
            if(this->on_ipt_cb) {
                (this->on_ipt_cb)(keys_down, keys_up, keys_held, tch_pos);
            }
        }

        if(this->lyt->HasBackgroundImage()) {
            this->renderer->RenderTexture(this->lyt->GetBackgroundImageTexture(), 0, 0);
        }

        if(!this->in_render_over) {
            auto lyt_on_ipt_cb = this->lyt->GetOnInput();
            if(lyt_on_ipt_cb) {
                lyt_on_ipt_cb(keys_down, keys_up, keys_held, tch_pos);
            }
        }

        for(u32 i = 0; i < this->lyt->GetCount(); i++) {
            auto elm = this->lyt->At(i);
            if(elm->IsVisible()) {
                elm->OnRender(this->renderer, elm->GetProcessedX(), elm->GetProcessedY());
                if(!this->in_render_over) {
                    elm->OnInput(keys_down, keys_up, keys_held, tch_pos);
                }
            }
        }

        if(this->ovl != nullptr) {
            const auto ovl_continue_render = this->ovl->Render(this->renderer);
            if(this->ovl_timeout_ms > 0) {
                const auto time_now = std::chrono::steady_clock::now();
                const u64 elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - this->ovl_start_time).count();
                if(elapsed_time_ms >= this->ovl_timeout_ms) {
                    this->ovl->NotifyEnding(true);
                }
            }
            if(!ovl_continue_render) {
                this->EndOverlay();
            }
        }

        this->renderer->RenderRectangleFill({ 0, 0, 0, static_cast<u8>(0xFF - this->fade_alpha) }, 0, 0, render::ScreenWidth, render::ScreenHeight);
    }

    void Application::Close() {
        this->is_shown = false;
        this->renderer->Finalize();
    }

}