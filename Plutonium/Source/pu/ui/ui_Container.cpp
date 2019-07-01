#include <pu/ui/ui_Container.hpp>

namespace pu::ui
{
    Container::Container(s32 X, s32 Y, s32 Width, s32 Height)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
    }

    void Container::Add(elm::Element *Elm)
    {
        this->elms.push_back(Elm);
    }

    elm::Element *Container::At(s32 Index)
    {
        if(Index < this->elms.size()) return this->elms[Index];
        return NULL;
    }

    bool Container::Has(elm::Element *Elm)
    {
        if(!this->elms.empty()) for(s32 i = 0; i < this->elms.size(); i++)
        {
            if(this->elms[i] == Elm) return true;
        }
        return false;
    }

    void Container::Clear()
    {
        if(!this->elms.empty()) for(s32 i = 0; i < this->elms.size(); i++) delete this->elms[i];
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
        if(!this->elms.empty()) for(s32 i = 0; i < this->elms.size(); i++)
        {
            this->elms[i]->SetParent(this);
        }
    }
}