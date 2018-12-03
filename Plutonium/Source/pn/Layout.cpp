#include <pn/Layout.hpp>

namespace pn
{
    Layout::Layout()
    {
        this->onipt = [&](u64 Input){};
    }

    void Layout::AddChild(fw::Element *Child)
    {
        this->chld.push_back(Child);
    }

    void Layout::ClearChildren()
    {
        this->chld.clear();
    }

    fw::Element *Layout::GetChildAt(u32 Index)
    {
        return this->chld[Index];
    }

    u32 Layout::GetChildCount()
    {
        return this->chld.size();
    }

    bool Layout::HasChilds()
    {
        return !(this->chld.empty());
    }

    void Layout::SetOnInput(std::function<void(u64 Input)> Callback)
    {
        this->onipt = Callback;
    }

    std::function<void(u64 Input)> Layout::GetOnInput()
    {
        return this->onipt;
    }
}