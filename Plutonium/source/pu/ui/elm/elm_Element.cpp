#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Layout.hpp>

namespace pu::ui::elm
{
    Element::Element()
    {
        this->visible = true;
        this->halign = HorizontalAlign::Left;
        this->valign = VerticalAlign::Up;
        this->parent = nullptr;
    }

    Element::~Element()
    {
    }

    bool Element::IsVisible()
    {
        return this->visible;
    }

    void Element::SetVisible(bool Visible)
    {
        this->visible = Visible;
    }

    void Element::SetParent(void *Base)
    {
        this->parent = Base;
    }

    void *Element::GetParent()
    {
        return this->parent;
    }

    void Element::SetHorizontalAlign(HorizontalAlign Align)
    {
        this->halign = Align;
    }

    HorizontalAlign Element::GetHorizontalAlign()
    {
        return this->halign;
    }

    void Element::SetVerticalAlign(VerticalAlign Align)
    {
        this->valign = Align;
    }

    VerticalAlign Element::GetVerticalAlign()
    {
        return this->valign;
    }

    bool Element::HasParent()
    {
        return (this->parent != nullptr);
    }

    i32 Element::GetProcessedX()
    {
        i32 rx = this->GetX();
        if(this->parent != nullptr)
        {
            Container *cont = (Container*)this->parent;
            rx += cont->GetX();
            switch(this->halign)
            {
                case HorizontalAlign::Center:
                    rx = cont->GetX() + ((cont->GetWidth() - this->GetWidth()) / 2);
                    break;
                case HorizontalAlign::Right:
                    rx = cont->GetX() + (cont->GetWidth() - this->GetWidth());
                    break;
                default:
                    break;
            }
        }
        return rx;
    }

    i32 Element::GetProcessedY()
    {
        i32 ry = this->GetY();
        if(this->parent != nullptr)
        {
            Container *cont = (Container*)this->parent;
            ry += cont->GetY();
            switch(this->valign)
            {
                case VerticalAlign::Center:
                    ry = cont->GetY() + ((cont->GetHeight() - this->GetHeight()) / 2);
                    break;
                case VerticalAlign::Down:
                    ry = cont->GetY() + (cont->GetHeight() - this->GetHeight());
                    break;
                default:
                    break;
            }
        }
        return ry;
    }
}