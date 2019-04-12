#include <pu/Container.hpp>

namespace pu
{
    Container::Container(u32 X, u32 Y, u32 Width, u32 Height)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
    }

    void Container::Add(element::Element *Elm)
    {
        this->elms.push_back(Elm);
    }

    element::Element *Container::At(u32 Index)
    {
        if(Index < this->elms.size()) return this->elms[Index];
        return NULL;
    }

    bool Container::Has(element::Element *Elm)
    {
        if(!this->elms.empty()) for(u32 i = 0; i < this->elms.size(); i++)
        {
            if(this->elms[i] == Elm) return true;
        }
        return false;
    }

    void Container::Clear()
    {
        if(!this->elms.empty()) for(u32 i = 0; i < this->elms.size(); i++) delete this->elms[i];
        this->elms.clear();
    }

    u32 Container::GetCount()
    {
        return this->elms.size();
    }

    void Container::SetX(u32 X)
    {
        this->x = X;
    }

    u32 Container::GetX()
    {
        return this->x;
    }

    void Container::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 Container::GetY()
    {
        return this->y;
    }

    void Container::SetWidth(u32 Width)
    {
        this->w = Width;
    }

    u32 Container::GetWidth()
    {
        return this->w;
    }

    void Container::SetHeight(u32 Height)
    {
        this->h = Height;
    }

    u32 Container::GetHeight()
    {
        return this->h;
    }

    void Container::PreRender()
    {
        if(!this->elms.empty()) for(u32 i = 0; i < this->elms.size(); i++)
        {
            this->elms[i]->SetParent(this);
        }
    }
}