#include <pu/ui/ui_Container.hpp>
#include <algorithm>

namespace pu::ui
{
    Container::Container(i32 X, i32 Y, i32 Width, i32 Height)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
    }

    elm::Element::Ref &Container::At(i32 Index)
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

    i32 Container::GetCount()
    {
        return this->elms.size();
    }

    void Container::SetX(i32 X)
    {
        this->x = X;
    }

    i32 Container::GetX()
    {
        return this->x;
    }

    void Container::SetY(i32 Y)
    {
        this->y = Y;
    }

    i32 Container::GetY()
    {
        return this->y;
    }

    void Container::SetWidth(i32 Width)
    {
        this->w = Width;
    }

    i32 Container::GetWidth()
    {
        return this->w;
    }

    void Container::SetHeight(i32 Height)
    {
        this->h = Height;
    }

    i32 Container::GetHeight()
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