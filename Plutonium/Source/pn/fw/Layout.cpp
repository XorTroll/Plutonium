#include <pn/fw/Layout.hpp>

namespace pn::fw
{
    Layout::Layout()
    {
        this->bg = draw::Color(0, 0, 0, 0);
    }

    Layout::Layout(draw::Color Background)
    {
        this->bg = Background;
    }

    u32 Layout::GetX()
    {
        return 0;
    }

    u32 Layout::GetY()
    {
        return 0;
    }

    u32 Layout::GetWidth()
    {
        return 1280;
    }

    u32 Layout::GetHeight()
    {
        return 720;
    }

    void Layout::AddChild(Element *Child)
    {
        this->elms.push_back(Child);
    }

    void Layout::ClearChildren()
    {
        this->elms.clear();
    }

    void Layout::OnRender(render::Renderer *Drawer)
    {
        Drawer->DrawRectangleFill(this->bg, 0, 0, 1280, 720);
        if(!this->elms.empty()) for(u32 i = 0; i < this->elms.size(); i++) if(this->elms[i]->IsVisible()) this->elms[i]->OnRender(Drawer);
    }

    void Layout::OnInput(u64 Input)
    {
        if(!this->elms.empty()) for(u32 i = 0; i < this->elms.size(); i++) if(this->elms[i]->IsVisible()) this->elms[i]->OnInput(Input);
    }
}