#include <pu/ui/elm/elm_Rectangle.hpp>

namespace pu::ui::elm
{
    Rectangle::Rectangle(s32 X, s32 Y, s32 Width, s32 Height, Color RecColor, s32 BorderRadius) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->clr = RecColor;
        this->borderr = BorderRadius;
    }

    s32 Rectangle::GetX()
    {
        return this->x;
    }

    void Rectangle::SetX(s32 X)
    {
        this->x = X;
    }

    s32 Rectangle::GetY()
    {
        return this->y;
    }

    void Rectangle::SetY(s32 Y)
    {
        this->y = Y;
    }

    s32 Rectangle::GetWidth()
    {
        return this->w;
    }

    void Rectangle::SetWidth(s32 Width)
    {
        this->w = Width;
    }

    s32 Rectangle::GetHeight()
    {
        return this->h;
    }

    void Rectangle::SetHeight(s32 Height)
    {
        this->h = Height;
    }

    s32 Rectangle::GetBorderRadius()
    {
        return this->h;
    }

    void Rectangle::SetBorderRadius(s32 Radius)
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

    void Rectangle::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
    {
        s32 rdx = X;
        s32 rdy = Y;
        Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
    }

    void Rectangle::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
    {
    }
}