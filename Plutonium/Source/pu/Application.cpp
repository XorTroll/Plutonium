#include <pu/Application.hpp>

namespace pu
{
    Application::Application()
    {
        this->rend = new render::Renderer();
        this->rend->Initialize();
        this->show = false;
        this->bgcolor = { 235, 235, 235, 255 };
        this->bgimage = "";
        this->hasimage = false;
        this->cbipt = [&](u64 Down, u64 Up, u64 Held, bool Touch){};
        this->rover = false;
        this->ovl = NULL;
        this->fovl = false;
        this->ffovl = false;
        this->rof = [](render::Renderer *Drawer){ return true; };
    }

    Application::~Application()
    {
        this->rend->Finalize();
    }

    void Application::LoadLayout(Layout *Layout)
    {
        this->lyt = Layout;
    }

    draw::Color Application::GetBackgroundColor()
    {
        return this->bgcolor;
    }

    void Application::SetBackgroundColor(draw::Color BackColor)
    {
        this->bgcolor = BackColor;
    }

    std::string Application::GetBackgroundImage()
    {
        return this->bgimage;
    }

    bool Application::HasBackgroundImage()
    {
        return this->hasimage;
    }

    void Application::SetBackgroundImage(std::string Path)
    {
        if(!Path.empty())
        {
            this->bgimage = Path;
            this->hasimage = true;
            this->ntex = render::LoadImage(Path);
        }
    }

    void Application::DeleteBackgroundImage()
    {
        if(this->hasimage)
        {
            this->bgimage = "";
            this->hasimage = false;
        }
    }

    void Application::AddThread(std::function<void()> Callback)
    {
        this->thds.push_back(Callback);
    }

    void Application::SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> Callback)
    {
        this->cbipt = Callback;
    }

    u32 Application::ShowDialog(Dialog *ToShow)
    {
        return ToShow->Show(this->rend, this);
    }

    int Application::CreateShowDialog(std::string Title, std::string Content, std::vector<std::string> Options, bool UseLastOptionAsCancel, std::string Icon)
    {
        Dialog *dlg = new Dialog(Title, Content);
        for(u32 i = 0; i < Options.size(); i++)
        {
            if(UseLastOptionAsCancel && (i == Options.size() - 1)) dlg->SetCancelOption(Options[i]);
            else dlg->AddOption(Options[i]);
        }
        if(!Icon.empty()) dlg->SetIcon(Icon);
        int opt = this->ShowDialog(dlg);
        if(dlg->UserCancelled()) opt = -1;
        else if(!dlg->IsOk()) opt = -2;
        delete dlg;
        return opt;
    }

    void Application::StartOverlay(overlay::Overlay *Ovl)
    {
        if(this->ovl == NULL) this->ovl = Ovl;
    }

    void Application::StartOverlayWithTimeout(overlay::Overlay *Ovl, u64 Milli)
    {
        if(this->ovl == NULL)
        {
            this->ovl = Ovl;
            this->tmillis = Milli;
            this->tclock = std::chrono::steady_clock::now();
        }
    }

    void Application::EndOverlay()
    {
        if(this->ovl != NULL)
        {
            this->ovl->NotifyEnding(false);
            this->tmillis = 0;
            this->ovl = NULL;
            this->fovl = false;
            this->ffovl = false;
        }
    }

    void Application::Show()
    {
        this->show = true;
        this->fact = 255;
        while(this->show) this->CallForRender();
    }

    bool Application::CallForRender()
    {
        bool c = true;
        this->rend->InitializeRender(this->bgcolor);
        this->OnRender();
        if(this->rover)
        {
            c = (this->rof)(this->rend);
            this->rover = false;
            this->rof = [](render::Renderer *Drawer){ return true; };
        }
        this->rend->FinalizeRender();
        return c;
    }

    bool Application::CallForRenderWithRenderOver(std::function<bool(render::Renderer *Drawer)> RenderFunc)
    {
        this->rover = true;
        this->rof = RenderFunc;
        return this->CallForRender();
    }

    void Application::OnRender()
    {
        hidScanInput();
        u64 d = hidKeysDown(CONTROLLER_P1_AUTO);
        u64 u = hidKeysUp(CONTROLLER_P1_AUTO);
        u64 h = hidKeysHeld(CONTROLLER_P1_AUTO);
        u64 th = hidKeysDown(CONTROLLER_HANDHELD);
        bool touch = (th & KEY_TOUCH);
        if(!this->thds.empty()) for(u32 i = 0; i < this->thds.size(); i++) (this->thds[i])();
        this->lyt->PreRender();
        std::vector<std::function<void()>> lyth = this->lyt->GetAllThreads();
        if(!lyth.empty()) for(u32 i = 0; i < lyth.size(); i++) (lyth[i])();
        if(!this->rover) (this->cbipt)(d, u, h, touch);
        if(this->hasimage) this->rend->RenderTexture(this->ntex, 0, 0);
        if(!this->rover) (this->lyt->GetOnInput())(d, u, h, touch);
        if(this->lyt->HasChilds()) for(u32 i = 0; i < this->lyt->GetCount(); i++)
        {
            element::Element *elm = this->lyt->At(i);
            if(elm->IsVisible())
            {
                elm->OnRender(this->rend);
                if(!this->rover) elm->ProcessInput((void*)this->lyt, d, u, h, touch);
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
        if(this->fact > 0)
        {
            this->rend->RenderRectangleFill(draw::Color(0, 0, 0, this->fact), 0, 0, 1280, 720);
            this->fact -= 20;
        }  
    }

    void Application::Close()
    {
        this->show = false;
    }
}