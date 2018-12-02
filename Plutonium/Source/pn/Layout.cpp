#include <pn/Layout.hpp>

namespace pn
{
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
}