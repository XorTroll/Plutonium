#include <pn/horizon/Page.hpp>

namespace pn::horizon
{
    void PageControls::Add(std::string Button, std::string Description)
    {
        this->ctrls.insert(std::pair<std::string, std::string>(Button, Description));
    }

    void PageControls::Clear()
    {
        this->ctrls.clear();
    }

    std::map<std::string, std::string> PageControls::GetControls()
    {
        return this->ctrls;
    }

    Page::Page(std::string Name)
    {
        this->SetName(Name);
    }

    std::string Page::GetName()
    {
        return this->name;
    }

    void Page::SetName(std::string Name)
    {
        this->name = Name;
    }

    PageControls *Page::GetControls()
    {
        return this->ctrls;
    }

    void Page::SetControls(PageControls *Controls)
    {
        this->ctrls = Controls;
    }

    u32 Page::GetX()
    {
        return 0;
    }

    u32 Page::GetY()
    {
        return 0;
    }

    u32 Page::GetWidth()
    {
        return 1280;
    }

    u32 Page::GetHeight()
    {
        return 720;
    }

    void Page::AddChild(fw::Element *Child)
    {
        this->pelems.push_back(Child);
    }

    void Page::ClearChildren()
    {
        this->pelems.clear();
    }

    void Page::OnRender(render::Renderer *Drawer)
    {
        Drawer->DrawText(this->name, draw::Font::NintendoStandard, 30, 30, 30, draw::Color(0, 0, 0, 255));
        u32 basey = 50;
        std::map<std::string, std::string> ctrlss = this->ctrls->GetControls();
        if(!ctrlss.empty()) for(auto const& ctrl : ctrlss)
        {
            Drawer->DrawText(ctrl.first, draw::Font::NintendoExtended, 20, 50, basey, draw::Color(0, 0, 0, 255));
            Drawer->DrawText(ctrl.second, draw::Font::NintendoStandard, 20, 80, basey, draw::Color(0, 0, 0, 255));
            basey += 25;
        }
        if(!this->pelems.empty()) for(u32 i = 0; i < this->pelems.size(); i++) this->pelems[i]->OnRender(Drawer);
    }

    void Page::OnGlobalInput(u64 Input)
    {
    }
    
    void Page::OnTouch(u32 TouchX, u32 TouchY)
    {
    }
}