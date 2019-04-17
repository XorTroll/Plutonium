#include <pu/Layout.hpp>

namespace pu
{
    Layout::Layout(bool UseFocus) : Container(0, 0, 1280, 720)
    {
        this->onipt = [&](u64 Down, u64 Up, u64 Held, bool Touch){};
        this->efocus = NULL;
        this->ufocus = UseFocus;
    }

    bool Layout::HasChilds()
    {
        return !this->elms.empty();
    }

    void Layout::SetElementOnFocus(element::Element *OnFocus)
    {
        this->efocus = OnFocus;
    }

    element::Element *Layout::GetElementOnFocus()
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
}