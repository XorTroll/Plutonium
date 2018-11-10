#include <pn/Application.hpp>

namespace pn
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
        this->elems.clear();
    }

    void Application::AddChild(fw::Element *Child)
    {
        this->elems.push_back(Child);
    }

    void Application::ClearChildren()
    {
        this->elems.clear();
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

    void Application::Show()
    {
        this->show = true;
        while(this->show)
        {
            hidScanInput();
            u64 k = hidKeysHeld(CONTROLLER_P1_AUTO);
            touchPosition tch;
            bool touched = false;
            if(k & KEY_TOUCH)
            {
                hidTouchRead(&tch, 0);
                touched = true;
            }
            this->rend->Clear(this->bgcolor);
            if(this->hasimage) this->rend->DrawImage(this->bgimage, 0, 0);
            if(!this->elems.empty()) for(u32 i = 0; i < this->elems.size(); i++)
            {
                this->elems[i]->OnGlobalInput(k);
                if(touched)
                {
                    u32 bx = this->elems[i]->GetX();
                    u32 x = (this->elems[i]->GetX() + this->elems[i]->GetWidth());
                    u32 by = this->elems[i]->GetY();
                    u32 y = (this->elems[i]->GetY() + this->elems[i]->GetHeight());
                    if((tch.px >= bx) && (tch.px <= x) && (tch.py >= by) && (tch.py <= y)) this->elems[i]->OnTouch(tch.px, tch.py);
                }
                this->elems[i]->OnRender(this->rend);
            }
            this->rend->Render();
        }
    }

    void Application::Close()
    {
        this->show = false;
    }
}