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
        s32 fact = 255;
        while(this->show)
        {
            hidScanInput();
            u64 k = hidKeysHeld(CONTROLLER_P1_AUTO);
            this->rend->Clear(this->bgcolor);
            if(this->hasimage) this->rend->DrawImage(this->bgimage, 0, 0);
            if(!this->elems.empty()) for(u32 i = 0; i < this->elems.size(); i++)
            {
                this->elems[i]->OnInput(k);
                this->elems[i]->OnRender(this->rend);
            }
            if(fact > 0)
            {
                this->rend->DrawRectangleFill(draw::Color(0, 0, 0, fact), 0, 0, 1280, 720);
                fact -= 8;
            }
            this->rend->Render();
        }
    }

    void Application::Close()
    {
        this->show = false;
    }

    LayoutApplication::LayoutApplication() : Application()
    {
        this->layidx = 0;
    }

    void LayoutApplication::AddLayout(fw::Layout *NewLayout)
    {
        this->elems.push_back(NewLayout);
    }

    void LayoutApplication::NavigateTo(fw::Layout *Source)
    {
        if(!this->elems.empty()) for(u32 i = 0; i < this->elems.size(); i++) if(this->elems[i] == Source)
        {
            this->layidx = i;
            break;
        }
    }

    void LayoutApplication::ClearLayouts()
    {
        this->elems.clear();
    }

    void LayoutApplication::Show()
    {
        this->show = true;
        s32 fact = 255;
        while(this->show)
        {
            hidScanInput();
            u64 k = hidKeysHeld(CONTROLLER_P1_AUTO);
            this->rend->Clear(this->bgcolor);
            if(this->hasimage) this->rend->DrawImage(this->bgimage, 0, 0);
            if(!this->elems.empty())
            {
                fw::Element *elm = this->elems[this->layidx];
                elm->OnInput(k);
                elm->OnRender(this->rend);
            }
            if(fact > 0)
            {
                this->rend->DrawRectangleFill(draw::Color(0, 0, 0, fact), 0, 0, 1280, 720);
                fact -= 8;
            }
            this->rend->Render();
        }
    }
}