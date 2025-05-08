#include <pu/ui/ui_Application.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

    void Application::UpdateInput() {
        this->renderer->UpdateInput();
        this->keys_down = this->renderer->GetButtonsDown();
        this->keys_up = this->renderer->GetButtonsUp();
        this->keys_held = this->renderer->GetButtonsHeld();

        HidTouchScreenState touch_state = {};
        hidGetTouchScreenStates(&touch_state, 1);
        if(touch_state.count > 0) {
            // Touch positions are based on a default (handheld) 720p, need to scale them to 1080p width/height
            this->touch_pos = {
                (u32)((double)touch_state.touches[0].x * render::ScreenFactor),
                (u32)((double)touch_state.touches[0].y * render::ScreenFactor)
            };
        }
        else {
            this->touch_pos = {};
        }
    }

    void Application::OnRender(const bool handle_input) {
        this->UpdateInput();
        GetStyle()->Update();

        for(auto &render_cb: this->render_cbs) {
            if(render_cb) {
                render_cb();
            }
        }

        // Render the layers in the order they were added
        for(auto layer: this->layers) {
            layer->OnRender(this->renderer);
        }

        if(handle_input) {
            // Iterate layers backwards to get the topmost layer
            for(auto it = this->layers.rbegin(); it != this->layers.rend(); ++it) {
                if(*it != nullptr) {
                    if((*it)->CapturesInput()) {
                        // Top layer that captures input
                        (*it)->OnInput(this->keys_down, this->keys_up, this->keys_held, this->touch_pos);
                        break;
                    }
                }
            }
        }

        for(auto &layer: this->layers) {
            if(!layer->IsActive()) {
                layer->OnStop();
            }
        }

        // Remove non-active layers from the input loop
        this->layers.erase(std::remove_if(this->layers.begin(), this->layers.end(), [](const Layer::Ref &layer) {
            return !layer->IsActive();
        }), this->layers.end());

        const auto over_alpha = static_cast<u8>(0xFF - this->fade_alpha);
        if(over_alpha > 0) {
            if(this->fade_bg_tex != nullptr) {
                this->renderer->RenderTexture(this->fade_bg_tex->Get(), 0, 0, render::TextureRenderOptions(over_alpha, {}, {}, {}, {}, {}));
            }
            else {
                this->renderer->RenderRectangleFill(this->fade_bg_clr.WithAlpha(over_alpha), 0, 0, render::ScreenWidth, render::ScreenHeight);
            }
        }
    }

    Application::Application(render::Renderer::Ref renderer) : loaded(false), is_shown(false), fade_alpha_increment_steps(DefaultFadeAlphaIncrementSteps), fade_alpha_incr(), fade_alpha(0xFF), fade_bg_tex(nullptr), fade_bg_clr({ 0, 0, 0, 0xFF }), layers(), render_cbs(), renderer(renderer), keys_down(0), keys_up(0), keys_held(0), touch_pos() {
        SetStyle(Style::New());
    }

    Application::~Application() {
        this->ResetFadeBackgroundImage();
    }

    Result Application::Load() {
        this->layers.push_back(nullptr);
        PU_RC_TRY(this->renderer->Initialize());

        if(!this->loaded) {
            this->OnLoad();
            this->loaded = true;
        }

        return 0;
    }

    void Application::AddLayer(Layer::Ref layer) {
        this->layers.push_back(layer);
        layer->OnStart();
        layer->SetActive(true);
    }

    s32 Application::ShowDialog(ly::Dialog::Ref dialog) {
        this->AddLayer(dialog);

        while(true) {
            if(!dialog->IsActive()) {
                return dialog->GetSelectedOption();
            }

            if(!this->CallForRender(true)) {
                return -3;
            }
        }
    }

    s32 Application::CreateShowDialog(const std::string &title, const std::string &content, const std::vector<std::string> &opts, const bool use_last_opt_as_cancel, sdl2::TextureHandle::Ref icon, DialogPrepareCallback prepare_cb) {
        auto dialog = ly::Dialog::New(title, content);
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

    Result Application::Show() {
        if(!this->CanBeShown()) {
            return ResultApplicationNotReady;
        }

        this->is_shown = true;
        while(this->is_shown) {
            this->CallForRender(true);
        }

        return ResultSuccess;
    }

    bool Application::CallForRender(const bool handle_input) {
        if(!this->CanBeShown()) {
            return false;
        }

        Layout::Ref lyt = this->GetLayout<Layout>();
        lyt->SetActive(true);
        this->renderer->InitializeRender(lyt->GetBackgroundColor());
        this->OnRender(handle_input);
        this->renderer->FinalizeRender();
        
        return true;
    }

    void Application::FadeIn() {
        this->fade_alpha = 0;
        this->fade_alpha_incr.StartFromZero(this->fade_alpha_increment_steps, 0xFF);
        while(true) {
            this->CallForRender(false);
            if(this->fade_alpha_incr.Increment(this->fade_alpha)) {
                break;
            }
        }
        this->CallForRender(false);
    }

    void Application::FadeOut() {
        this->fade_alpha = 0xFF;
        this->fade_alpha_incr.StartToZero(this->fade_alpha_increment_steps, this->fade_alpha);
        while(true) {
            this->CallForRender(false);
            if(this->fade_alpha_incr.Increment(this->fade_alpha)) {
                break;
            }
        }
        this->CallForRender(false);
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
        this->layers.clear();
        this->render_cbs.clear();
        this->renderer->Finalize();
        this->loaded = false;
        SetStyle(nullptr);

        if(do_exit) {
            exit(0);
        }
    }

}
