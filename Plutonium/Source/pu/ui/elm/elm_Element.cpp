#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Layout.hpp>

namespace pu::ui::elm
{
    Element::Element()
    {
        this->visible = true;
        this->afocus = true;
        this->fup = NULL;
        this->fdown = NULL;
        this->fleft = NULL;
        this->fright = NULL;
        this->parent = NULL;
        this->halign = HorizontalAlign::Left;
        this->valign = VerticalAlign::Up;
    }

    Element::~Element()
    {
    }

    void Element::ProcessInput(void *Lyt, u64 Down, u64 Up, u64 Held, bool Touch)
    {
        Layout *lyt = (Layout*)Lyt;
        if(lyt->UsesFocus() && this->afocus)
        {
            u64 KEY_DPAD = (KEY_DUP | KEY_DDOWN | KEY_DLEFT | KEY_DRIGHT);
            u64 KEY_PLSTICK = (KEY_LSTICK_UP | KEY_LSTICK_DOWN | KEY_LSTICK_LEFT | KEY_LSTICK_RIGHT);
            u64 KEY_PRSTICK = (KEY_RSTICK_UP | KEY_RSTICK_DOWN | KEY_RSTICK_LEFT | KEY_RSTICK_RIGHT);
            bool onfocus = (lyt->GetElementOnFocus() == this);
            bool thistouch = false;
            if(Touch)
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                thistouch = (((this->GetX() + this->GetWidth()) > tch.px) && (tch.px > this->GetX()) && ((this->GetY() + this->GetHeight()) > tch.py) && (tch.py > this->GetY()));
                if(thistouch)
                {
                    lyt->SetElementOnFocus(this);
                    this->OnInput(Down, Up, Held, thistouch, onfocus);
                }
            }
            else if((Down & KEY_PRSTICK) && onfocus)
            {
                if(Down & KEY_RSTICK_UP)
                {
                    if(this->fup != NULL) lyt->SetElementOnFocus(this->fup);
                }
                else if(Down & KEY_RSTICK_DOWN)
                {
                    if(this->fdown != NULL) lyt->SetElementOnFocus(this->fdown);
                }
                else if(Down & KEY_RSTICK_LEFT)
                {
                    if(this->fleft != NULL) lyt->SetElementOnFocus(this->fleft);
                }
                else if(Down & KEY_RSTICK_RIGHT)
                {
                    if(this->fright != NULL) lyt->SetElementOnFocus(this->fright);
                }
            }
            else if(onfocus) this->OnInput(Down, Up, Held, thistouch, onfocus);
        }
        else this->OnInput(Down, Up, Held, Touch, false);
    }

    bool Element::IsVisible()
    {
        return this->visible;
    }

    void Element::SetVisible(bool Visible)
    {
        this->visible = Visible;
    }

    bool Element::IsAffectedByFocus()
    {
        return this->afocus;
    }

    void Element::SetAffectedByFocus(bool Affected)
    {
        this->afocus = Affected;
    }

    Element *Element::GetFocusChangeElement(FocusChangeDirection Direction)
    {
        Element *elem = NULL;
        switch(Direction)
        {
            case FocusChangeDirection::Up:
                elem = this->fup;
                break;
            case FocusChangeDirection::Down:
                elem = this->fdown;
                break;
            case FocusChangeDirection::Left:
                elem = this->fleft;
                break;
            case FocusChangeDirection::Right:
                elem = this->fright;
                break;
        }
        return elem;
    }

    void Element::SetFocusChangeElement(FocusChangeDirection Direction, Element *ToChange)
    {
        switch(Direction)
        {
            case FocusChangeDirection::Up:
                this->fup = ToChange;
                break;
            case FocusChangeDirection::Down:
                this->fdown = ToChange;
                break;
            case FocusChangeDirection::Left:
                this->fleft = ToChange;
                break;
            case FocusChangeDirection::Right:
                this->fright = ToChange;
                break;
        }
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
        return (this->parent != NULL);
    }

    s32 Element::GetProcessedX()
    {
        s32 rx = this->GetX();
        if(this->parent != NULL)
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

    s32 Element::GetProcessedY()
    {
        s32 ry = this->GetY();
        if(this->parent != NULL)
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