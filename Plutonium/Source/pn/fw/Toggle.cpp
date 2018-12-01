#include <pn/fw/Toggle.hpp>

namespace pn::fw
{
    Toggle::Toggle(u32 X, u32 Y, std::string Content, u64 Key, draw::Color Checked)
    {
        this->x = X;
        this->y = Y;
        this->key = Key;
        this->cnt = Content;
        this->clr = Checked;
        this->fnt = draw::Font::NintendoStandard;
        this->fsize = 25;
        this->togfact = 255;
    }

    u32 Toggle::GetX()
    {
        return this->x;
    }

    void Toggle::SetX(u32 X)
    {
        this->x = X;
    }

    u32 Toggle::GetY()
    {
        return this->y;
    }

    void Toggle::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 Toggle::GetWidth()
    {
        return 0;
    }

    u32 Toggle::GetHeight()
    {
        return 0;
    }

    std::string Toggle::GetContent()
    {
        return this->cnt;
    }

    void Toggle::SetContent(std::string Content)
    {
        this->cnt = Content;
    }

    draw::Font Toggle::GetFont()
    {
        return this->fnt;
    }

    void Toggle::SetFont(draw::Font Font)
    {
        this->fnt = Font;
    }

    u32 Toggle::GetFontSize()
    {
        return this->fsize;
    }

    void Toggle::SetFontSize(u32 Size)
    {
        this->fsize = Size;
    }

    draw::Color Toggle::GetColor()
    {
        return this->clr;
    }

    void Toggle::SetColor(draw::Color Color)
    {
        this->clr = Color;
    }

    u64 Toggle::GetKey()
    {
        return this->key;
    }

    void Toggle::SetKey(u64 Key)
    {
        this->key = Key;
    }

    void Toggle::OnRender(render::Renderer *Drawer)
    {
        u32 tw = Drawer->GetTextWidth(this->fnt, this->cnt, this->fsize);
        u32 th = Drawer->GetTextHeight(this->fnt, this->cnt, this->fsize);
        u32 rw = th;
        u32 rh = (2 * th);
        u32 rx = this->x;
        u32 ry = this->y;
        u32 tx = this->x + rw + (th / 2);
        u32 ty = this->y + (th / 2);
        if(this->checked)
        {
            Drawer->DrawRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
            if(this->togfact < 255)
            {
                Drawer->DrawRectangleFill({ this->clr.R, this->clr.G, this->clr.B, (255 - this->togfact) }, rx, ry, rw, rh);
                this->togfact += 48;
            }
            else Drawer->DrawRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
        }
        else
        {
            Drawer->DrawRectangleFill(this->clr, rx, ry, rw, rh);
            if(this->togfact > 0)
            {
                Drawer->DrawRectangleFill({ 130, 130, 130, this->togfact }, rx, ry, rw, rh);
                this->togfact -= 48;
            }
            else Drawer->DrawRectangleFill(this->clr, rx, ry, rw, rh);
        }
        Drawer->DrawText(this->cnt, this->fnt, this->fsize, tx, ty, { 0, 0, 0, 255 });
    }

    void Toggle::OnInput(u64 Input)
    {
        if(Input & this->key) this->checked = !this->checked;
    }
}