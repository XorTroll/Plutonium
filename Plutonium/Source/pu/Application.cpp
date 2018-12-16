#include <pu/Application.hpp>

namespace pu
{
    Application::Application()
    {
        this->rend = new render::Renderer();
        this->rend->Initialize();
        this->show = false;
        this->bgcolor = { 255, 255, 255, 255 };
        this->bgimage = "";
        this->hasimage = false;
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

    void Application::SetCustomFont(std::string FontPath)
    {
        this->rend->SetCustomFont(FontPath);
    }

    bool Application::UsesCustomFont()
    {
        return this->rend->UsesCustomFont();
    }

    std::string Application::GetCustomFont()
    {
        return this->rend->GetCustomFont();
    }

    void Application::AddThread(std::function<void()> Callback)
    {
        this->thds.push_back(Callback);
    }

    void Application::ShowDialog(Dialog *ToShow)
    {
        ToShow->Show(this->rend);
    }

    void Application::Show()
    {
        this->show = true;
        this->fact = 255;
        while(this->show) this->CallForRender();
    }

    void Application::CallForRender()
    {
        hidScanInput();
        u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(!this->thds.empty()) for(u32 i = 0; i < this->thds.size(); i++) (this->thds[i])();
        this->rend->Clear(this->bgcolor);
        if(this->hasimage) this->rend->DrawImage(this->bgimage, 0, 0);
        (this->lyt->GetOnInput())(k);
        if(this->lyt->HasChilds()) for(u32 i = 0; i < this->lyt->GetChildCount(); i++)
        {
            element::Element *elm = this->lyt->GetChildAt(i);
            if(elm->IsVisible())
            {
                elm->OnRender(this->rend);
                elm->OnInput(k);
            }
        }
        if(this->fact > 0)
        {
            this->rend->DrawRectangleFill(draw::Color(0, 0, 0, this->fact), 0, 0, 1280, 720);
            this->fact -= 20;
        }
        this->rend->Render();
    }

    void Application::Close()
    {
        this->show = false;
    }
}