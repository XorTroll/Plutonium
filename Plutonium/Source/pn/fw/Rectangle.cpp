#include <pn/fw/Rectangle.hpp>

namespace pn::fw
{
    Rectangle::Rectangle(u32 X, u32 Y, u32 Width, u32 Height, draw::Color RecColor, u32 BorderRadius)
    {
        this->x = X;
        this->x = Y;
        this->w = Width;
        this->h = Height;
        this->clr = RecColor;
        this->borderr = BorderRadius;
    }

    u32 Rectangle::GetX()
    {
        return this->x;
    }

    void Rectangle::SetX(u32 X)
    {
        this->x = X;
    }

    u32 Rectangle::GetY()
    {
        return this->y;
    }

    void Rectangle::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 Rectangle::GetWidth()
    {
        return this->w;
    }

    void Rectangle::SetWidth(u32 Width)
    {
        this->w = Width;
    }

    u32 Rectangle::GetHeight()
    {
        return this->h;
    }

    void Rectangle::SetHeight(u32 Height)
    {
        this->h = Height;
    }

    u32 Rectangle::GetBorderRadius()
    {
        return this->h;
    }

    void Rectangle::SetBorderRadius(u32 Radius)
    {
        this->borderr = Radius;
    }

    draw::Color Rectangle::GetColor()
    {
        return this->clr;
    }

    void Rectangle::SetColor(draw::Color RecColor)
    {
        this->clr = RecColor;
    }

    void Rectangle::OnRender(render::Renderer *Drawer)
    {
        if(this->borderr > 0)
        {
            u32 diam = (2 * this->borderr);
            Drawer->DrawRectangleFill(this->clr, (this->x + this->borderr), (this->y + this->borderr), (this->w - diam), (this->h - diam));
            Drawer->DrawRectangleFill(this->clr, (this->x + this->borderr), this->y, (this->y + this->w - diam), this->borderr);
            Drawer->DrawRectangleFill(this->clr, (this->x + this->borderr), (this->y + (this->h - this->borderr)), (this->w - diam), this->borderr);
            Drawer->DrawRectangleFill(this->clr, this->x, (this->y + this->borderr), this->borderr, (this->h - diam));
            Drawer->DrawRectangleFill(this->clr, (this->x + (this->w - this->borderr)), (this->y + this->borderr), this->borderr, (this->h - diam));
            Drawer->DrawCircle(this->clr, this->x, this->y, this->borderr);
            Drawer->DrawCircle(this->clr, (this->x + this->w - diam), this->y, this->borderr);
            Drawer->DrawCircle(this->clr, this->x, (this->h - diam), this->borderr);
            Drawer->DrawCircle(this->clr, (this->x + this->w - diam), (this->h - diam), this->borderr);
        }
        else Drawer->DrawRectangleFill(this->clr, this->x, this->y, this->w, this->h);
    }

    void Rectangle::OnGlobalInput(u64 Input)
    {
    }

    void Rectangle::OnTouch(u32 TouchX, u32 TouchY)
    {
    }
}