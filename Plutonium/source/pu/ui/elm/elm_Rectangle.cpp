#include <pu/ui/elm/elm_Rectangle.hpp>

namespace pu::ui::elm
{
    Rectangle::Rectangle(i32 X, i32 Y, i32 Width, i32 Height, Color RecColor, i32 BorderRadius) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->clr = RecColor;
        this->borderr = BorderRadius;
    }

    i32 Rectangle::GetX()
    {
        return this->x;
    }

    void Rectangle::SetX(i32 X)
    {
        this->x = X;
    }

    i32 Rectangle::GetY()
    {
        return this->y;
    }

    void Rectangle::SetY(i32 Y)
    {
        this->y = Y;
    }

    i32 Rectangle::GetWidth()
    {
        return this->w;
    }

    void Rectangle::SetWidth(i32 Width)
    {
        this->w = Width;
    }

    i32 Rectangle::GetHeight()
    {
        return this->h;
    }

    void Rectangle::SetHeight(i32 Height)
    {
        this->h = Height;
    }

    i32 Rectangle::GetBorderRadius()
    {
        return this->h;
    }

    void Rectangle::SetBorderRadius(i32 Radius)
    {
        this->borderr = Radius;
    }

    Color Rectangle::GetColor()
    {
        return this->clr;
    }

    void Rectangle::SetColor(Color RecColor)
    {
        this->clr = RecColor;
    }

    void Rectangle::OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y)
    {
        i32 rdx = X;
        i32 rdy = Y;
        Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
    }

    void Rectangle::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
    }
}