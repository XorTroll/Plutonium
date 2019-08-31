#include <pu/ui/ui_Application.hpp>

namespace pu::ui
{
    Application::Application(u32 Flags, bool RenderAccel)
    {
        this->rend = render::Renderer::New();
        this->rend->Initialize(Flags, RenderAccel);
        this->show = false;
        this->cbipt = [&](u64,u64,u64,bool){};
        this->rover = false;
        this->ovl = nullptr;
        this->closefact = false;
        this->fovl = false;
        this->ffovl = false;
        this->lyt = nullptr;
        this->rof = [](render::Renderer::Ref&) -> bool { return true; };
        this->fadea = 255;
        this->aapf = 35;
    }

    void Application::AddThread(std::function<void()> Callback)
    {
        this->thds.push_back(Callback);
    }

    void Application::SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> Callback)
    {
        this->cbipt = Callback;
    }

    s32 Application::ShowDialog(Dialog::Ref &ToShow)
    {
        return ToShow->Show(this->rend, this);
    }

    int Application::CreateShowDialog(String Title, String Content, std::vector<String> Options, bool UseLastOptionAsCancel, std::string Icon)
    {
        Dialog dlg(Title, Content);
        for(s32 i = 0; i < Options.size(); i++)
        {
            if(UseLastOptionAsCancel && (i == Options.size() - 1)) dlg.SetCancelOption(Options[i]);
            else dlg.AddOption(Options[i]);
        }
        if(!Icon.empty()) dlg.SetIcon(Icon);
        int opt = dlg.Show(this->rend, this);
        if(dlg.UserCancelled()) opt = -1;
        else if(!dlg.IsOk()) opt = -2;
        return opt;
    }

    void Application::EndOverlay()
    {
        if(this->ovl != nullptr)
        {
            this->ovl->NotifyEnding(false);
            this->tmillis = 0;
            this->ovl = nullptr;
            this->fovl = false;
            this->ffovl = false;
        }
    }

    void Application::Show()
    {
        if(this->lyt == nullptr) return;
        this->show = true;
        while(this->show) this->CallForRender();
    }

    void Application::ShowWithFadeIn()
    {
        this->FadeIn();
        this->Show();
    }

    bool Application::IsShown()
    {
        return this->show;
    }

    bool Application::CallForRender()
    {
        bool c = true;
        this->rend->InitializeRender(this->lyt->GetBackgroundColor());
        this->OnRender();
        if(this->rover)
        {
            c = (this->rof)(this->rend);
            this->rover = false;
            this->rof = [](render::Renderer::Ref &Drawer) -> bool { return true; };
        }
        this->rend->FinalizeRender();
        return c;
    }

    bool Application::CallForRenderWithRenderOver(std::function<bool(render::Renderer::Ref &Drawer)> RenderFunc)
    {
        this->rover = true;
        this->rof = RenderFunc;
        return this->CallForRender();
    }

    void Application::FadeIn()
    {
        fadea = 0;
        while(true)
        {
            CallForRender();
            fadea += aapf;
            if(fadea > 255)
            {
                fadea = 255;
                CallForRender();
                break;
            }
        }
    }

    void Application::FadeOut()
    {
        fadea = 255;
        while(true)
        {
            CallForRender();
            fadea -= aapf;
            if(fadea < 0)
            {
                fadea = 0;
                CallForRender();
                break;
            }
        }
    }

    bool Application::IsFadedIn()
    {
        return (fadea > 0);
    }

    void Application::SetFadeAlphaAmountPerFrame(u8 Alpha)
    {
        aapf = Alpha;
    }

    void Application::OnRender()
    {
        hidScanInput();
        u64 d = hidKeysDown(CONTROLLER_P1_AUTO);
        u64 u = hidKeysUp(CONTROLLER_P1_AUTO);
        u64 h = hidKeysHeld(CONTROLLER_P1_AUTO);
        u64 th = hidKeysDown(CONTROLLER_HANDHELD);
        bool touch = (th & KEY_TOUCH);
        if(!this->thds.empty()) for(s32 i = 0; i < this->thds.size(); i++) (this->thds[i])();
        this->lyt->PreRender();
        auto lyth = this->lyt->GetAllThreads();
        if(!lyth.empty()) for(s32 i = 0; i < lyth.size(); i++) (lyth[i])();
        if(!this->rover) (this->cbipt)(d, u, h, touch);
        if(this->lyt->HasBackgroundImage()) this->rend->RenderTexture(this->lyt->GetBackgroundImageTexture(), 0, 0);
        if(!this->rover) (this->lyt->GetOnInput())(d, u, h, touch);
        if(this->lyt->HasChilds()) for(s32 i = 0; i < this->lyt->GetCount(); i++)
        {
            auto elm = this->lyt->At(i);
            if(elm->IsVisible())
            {
                elm->OnRender(this->rend, elm->GetProcessedX(), elm->GetProcessedY());
                if(!this->rover) elm->OnInput(d, u, h, touch);
            }
        }
        if(this->ovl != NULL)
        {
            bool rok = this->ovl->Render(this->rend);
            if(this->tmillis > 0)
            {
                auto nclk = std::chrono::steady_clock::now();
                u64 cctime = std::chrono::duration_cast<std::chrono::milliseconds>(nclk - this->tclock).count();
                if(cctime >= this->tmillis) this->ovl->NotifyEnding(true);
            }
            if(!rok) this->EndOverlay();
        }
        this->rend->RenderRectangleFill({ 0, 0, 0, 255 - (u8)fadea }, 0, 0, 1280, 720);
    }

    void Application::Close()
    {
        this->show = false;
        this->rend->Finalize();
    }

    void Application::CloseWithFadeOut()
    {
        this->FadeOut();
        this->Close();
    }
}