#include <pu/ui/ui_Application.hpp>

namespace pu::ui {

    void Application::OnRender() {
        this->LockRender();
        this->renderer->UpdateInput();
        const auto keys_down = this->GetButtonsDown();
        const auto keys_up = this->GetButtonsUp();
        const auto keys_held = this->GetButtonsHeld();
        auto start_lyt = this->lyt;
        auto lyt_changed = false;

        #define _ONLY_DO_UNCHANGED(...) { \
            if(!lyt_changed) { \
                __VA_ARGS__ \
                lyt_changed = this->lyt != start_lyt; \
            } \
        }

        const auto tch_state = this->GetTouchState();
        TouchPoint tch_pos = {};
        if(tch_state.count > 0) {
            // Touch positions are based on a default 1280x720 size, need to scale them to our width/height
            tch_pos = {
                (u32)((double)tch_state.touches[0].x * render::ScreenFactor),
                (u32)((double)tch_state.touches[0].y * render::ScreenFactor)
            };
        }
        const auto sim_tch_pos = this->lyt->ConsumeSimulatedTouchPosition();
        if(!sim_tch_pos.IsEmpty()) {
            tch_pos = sim_tch_pos;
        }

        for(auto &render_cb: this->render_cbs) {
            if(render_cb) {
                _ONLY_DO_UNCHANGED(
                    render_cb();
                );
            }
        }

        this->lyt->PreRender();

        for(auto &lyt_render_cb: this->lyt->GetRenderCallbacks()) {
            if(lyt_render_cb) {
                _ONLY_DO_UNCHANGED(
                    lyt_render_cb();
                );
            }
        }

        if(!this->in_render_over) {
            if(this->on_ipt_cb) {
                _ONLY_DO_UNCHANGED(
                    (this->on_ipt_cb)(keys_down, keys_up, keys_held, tch_pos);
                );
            }
        }

        auto lyt_bg_tex = this->lyt->GetBackgroundImageTexture();
        if(lyt_bg_tex != nullptr) {
            const auto x_offset = this->lyt->GetBackgroundImageXOffset();
            if(x_offset == 0) {
                this->renderer->RenderTexture(lyt_bg_tex->Get(), 0, 0);
            }
            else if(x_offset > 0) {
                this->renderer->RenderTexture(lyt_bg_tex->Get(), x_offset, 0);
                this->renderer->RenderTexture(lyt_bg_tex->Get(), x_offset - render::ScreenWidth, 0);
            }
            else if(x_offset < 0) {
                this->renderer->RenderTexture(lyt_bg_tex->Get(), x_offset, 0);
                this->renderer->RenderTexture(lyt_bg_tex->Get(), x_offset + render::ScreenWidth, 0);
            }
        }

        if(!this->in_render_over) {
            auto lyt_on_ipt_cb = this->lyt->GetOnInput();
            if(lyt_on_ipt_cb) {
                _ONLY_DO_UNCHANGED(
                    lyt_on_ipt_cb(keys_down, keys_up, keys_held, tch_pos);
                );
            }
        }

        auto lyt_elems = this->lyt->GetElements();
        for(auto &elem: lyt_elems) {
            _ONLY_DO_UNCHANGED(
                if(elem->IsVisible()) {
                    elem->OnRender(this->renderer, elem->GetProcessedX(), elem->GetProcessedY());
                    if(!this->in_render_over) {
                        elem->OnInput(keys_down, keys_up, keys_held, tch_pos);
                    }
                }
            );
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

        const auto over_alpha = static_cast<u8>(0xFF - this->fade_alpha);
        if(over_alpha > 0) {
            if(this->fade_bg_tex != nullptr) {
                this->renderer->RenderTexture(this->fade_bg_tex->Get(), 0, 0, render::TextureRenderOptions(over_alpha, {}, {}, {}, {}, {}));
            }
            else {
                this->renderer->RenderRectangleFill(this->fade_bg_clr.WithAlpha(over_alpha), 0, 0, render::ScreenWidth, render::ScreenHeight);
            }
        }

        this->UnlockRender();
    }

    Application::Application(render::Renderer::Ref renderer) {
        this->renderer = renderer;
        this->is_shown = false;
        this->on_ipt_cb = {};
        this->in_render_over = false;
        this->ovl = nullptr;
        this->lyt = nullptr;
        this->loaded = false;
        this->render_over_fn = {};
        this->fade_alpha = 0xFF;
        this->fade_alpha_increment_steps = DefaultFadeAlphaIncrementSteps;
        this->fade_alpha_incr = {};
        this->fade_bg_tex = {};
        this->fade_bg_clr = { 0, 0, 0, 0xFF };
        rmutexInit(&this->render_lock);
    }

    Application::~Application() {
        this->ResetFadeBackgroundImage();
    }

    Result Application::Load() {
        PU_RC_TRY(this->renderer->Initialize());

        if(!this->loaded) {
            this->OnLoad();
            this->loaded = true;
        }

        return 0;
    }

    i32 Application::CreateShowDialog(const std::string &title, const std::string &content, const std::vector<std::string> &opts, const bool use_last_opt_as_cancel, sdl2::TextureHandle::Ref icon, DialogPrepareCallback prepare_cb) {
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

        if(icon != nullptr) {
            dialog->SetIcon(icon);
        }

        if(prepare_cb != nullptr) {
            prepare_cb(dialog);
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
            continue_render = this->render_over_fn(this->renderer);
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
        this->fade_alpha_incr.StartFromZero(this->fade_alpha_increment_steps, 0xFF);
        while(true) {
            this->CallForRender();
            if(this->fade_alpha_incr.Increment(this->fade_alpha)) {
                break;
            }
        }
        this->CallForRender();
    }

    void Application::FadeOut() {
        this->fade_alpha = 0xFF;
        this->fade_alpha_incr.StartToZero(this->fade_alpha_increment_steps, this->fade_alpha);
        while(true) {
            this->CallForRender();
            if(this->fade_alpha_incr.Increment(this->fade_alpha)) {
                break;
            }
        }
        this->CallForRender();
    }

    void Application::SetFadeBackgroundImage(sdl2::TextureHandle::Ref bg_tex) {
        this->ResetFadeBackgroundImage();
        this->fade_bg_tex = bg_tex;
    }

    void Application::SetFadeBackgroundColor(const Color clr) {
        this->ResetFadeBackgroundImage();
        this->fade_bg_clr = clr;
    }

    void Application::ResetFadeBackgroundImage() {
       this->fade_bg_tex = {};
    }

    void Application::Close(const bool do_exit) {
        this->is_shown = false;
        this->renderer->Finalize();

        if(do_exit) {
            exit(0);
        }
    }

}
