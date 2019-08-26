#include <pu/ui/ui_Container.hpp>
#include <algorithm>

namespace pu::ui
{
    Container::Container(s32 X, s32 Y, s32 Width, s32 Height)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
    }

    elm::Element::Ref &Container::At(s32 Index)
    {
        return this->elms.at(Index);
    }

    bool Container::Has(elm::Element::Ref &Elm)
    {
        auto it = std::find(this->elms.begin(), this->elms.end(), Elm);
        return (it != this->elms.end());
    }

    void Container::Clear()
    {
        this->elms.clear();
    }

    s32 Container::GetCount()
    {
        return this->elms.size();
    }

    void Container::SetX(s32 X)
    {
        this->x = X;
    }

    s32 Container::GetX()
    {
        return this->x;
    }

    void Container::SetY(s32 Y)
    {
        this->y = Y;
    }

    s32 Container::GetY()
    {
        return this->y;
    }

    void Container::SetWidth(s32 Width)
    {
        this->w = Width;
    }

    s32 Container::GetWidth()
    {
        return this->w;
    }

    void Container::SetHeight(s32 Height)
    {
        this->h = Height;
    }

    s32 Container::GetHeight()
    {
        return this->h;
    }

    void Container::PreRender()
    {
        for(auto &elm : this->elms)
        {
            elm->SetParent(this);
        }
    }
}