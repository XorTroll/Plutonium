#include <pu/Layout.hpp>

namespace pu
{
    Layout::Layout()
    {
        this->onipt = [&](u64 Down, u64 Up, u64 Held){};
    }

    void Layout::AddChild(element::Element *Child)
    {
        this->chld.push_back(Child);
    }

    void Layout::ClearChildren()
    {
        this->chld.clear();
    }

    element::Element *Layout::GetChildAt(u32 Index)
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

    void Layout::SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held)> Callback)
    {
        this->onipt = Callback;
    }

    std::function<void(u64 Down, u64 Up, u64 Held)> Layout::GetOnInput()
    {
        return this->onipt;
    }
}