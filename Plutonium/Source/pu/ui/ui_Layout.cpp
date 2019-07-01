#include <pu/ui/ui_Layout.hpp>

namespace pu::ui
{
    Layout::Layout(bool UseFocus) : Container(0, 0, 1280, 720)
    {
        this->onipt = [&](u64 Down, u64 Up, u64 Held, bool Touch){};
        this->efocus = NULL;
        this->ufocus = UseFocus;
        this->hasimage = false;
        this->overbgtex = NULL;
        this->overbgcolor = { 225, 225, 225, 255 };
    }

    bool Layout::HasChilds()
    {
        return !this->elms.empty();
    }

    void Layout::SetElementOnFocus(elm::Element *OnFocus)
    {
        this->efocus = OnFocus;
    }

    elm::Element *Layout::GetElementOnFocus()
    {
        return this->efocus;
    }

    void Layout::SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> Callback)
    {
        this->onipt = Callback;
    }

    std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> Layout::GetOnInput()
    {
        return this->onipt;
    }

    void Layout::AddThread(std::function<void()> Callback)
    {
        this->thds.push_back(Callback);
    }

    std::vector<std::function<void()>> Layout::GetAllThreads()
    {
        return this->thds;
    }

    bool Layout::UsesFocus()
    {
        return this->ufocus;
    }

    void Layout::SetUseFocus(bool Focus)
    {
        this->ufocus = Focus;
    }

    void Layout::SetBackgroundImage(std::string Path)
    {
        if(this->overbgtex != NULL) render::DeleteTexture(this->overbgtex);
        this->hasimage = true;
        this->overbgtex = render::LoadImage(Path);
    }

    void Layout::SetBackgroundColor(Color Color)
    {
        if(this->overbgtex != NULL) render::DeleteTexture(this->overbgtex);
        this->hasimage = false;
        this->overbgcolor = Color;
    }

    render::NativeTexture Layout::GetBackgroundImageTexture()
    {
        return this->overbgtex;
    }

    Color Layout::GetBackgroundColor()
    {
        return this->overbgcolor;
    }

    bool Layout::HasBackgroundImage()
    {
        return this->hasimage;
    }
}