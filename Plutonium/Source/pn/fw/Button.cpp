#include <pn/fw/Button.hpp>

namespace pn::fw
{
    Button::Button(u32 X, u32 Y, u32 Width, u32 Height, std::string Content, draw::Color ButtonColor)
    {
        this->x = X;
        this->x = Y;
        this->w = Width;
        this->h = Height;
        this->cnt = Content;
        this->clr = ButtonColor;
        this->hover = false;
    }

    u32 Button::GetX()
    {
        return this->x;
    }

    void Button::SetX(u32 X)
    {
        this->x = X;
    }

    u32 Button::GetY()
    {
        return this->y;
    }

    void Button::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 Button::GetWidth()
    {
        return this->w;
    }

    void Button::SetWidth(u32 Width)
    {
        this->w = Width;
    }

    u32 Button::GetHeight()
    {
        return this->h;
    }

    void Button::SetHeight(u32 Height)
    {
        this->h = Height;
    }

    std::string Button::GetContent()
    {
        return this->cnt;
    }

    void Button::SetContent(std::string Content)
    {
        this->cnt = Content;
    }

    draw::Color Button::GetColor()
    {
        return this->clr;
    }

    void Button::SetColor(draw::Color ButtonColor)
    {
        this->clr = ButtonColor;
    }

    void Button::SetOnClick(std::function<void()> ClickCallback)
    {
        this->clickcb = ClickCallback;
    }

    void Button::OnRender(render::Renderer *Drawer)
    {
        u32 textsize = (this->cnt.length() * 25);
        u32 borderr = 25;
        u32 diam = (2 * borderr);
        if(this->hover)
        {
            s32 clrr = this->clr.R;
            s32 clrg = this->clr.G;
            s32 clrb = this->clr.B;
            s32 nr = clrr - 70;
            if(nr < 0) nr = 0;
            s32 ng = clrg - 70;
            if(ng < 0) ng = 0;
            s32 nb = clrb - 70;
            if(nb < 0) nb = 0;
            draw::Color nclr(nr, ng, nb, this->clr.A);
            Drawer->DrawRectangleFill(nclr, (this->x + borderr), (this->y + borderr), (this->w - diam), (this->h - diam));
            Drawer->DrawRectangleFill(nclr, (this->x + borderr), this->y, (this->y + this->w - diam), borderr);
            Drawer->DrawRectangleFill(nclr, (this->x + borderr), (this->y + (this->h - borderr)), (this->w - diam), borderr);
            Drawer->DrawRectangleFill(nclr, this->x, (this->y + borderr), borderr, (this->h - diam));
            Drawer->DrawRectangleFill(nclr, (this->x + (this->w - borderr)), (this->y + borderr), borderr, (this->h - diam));
            Drawer->DrawCircle(nclr, this->x, this->y, borderr);
            Drawer->DrawCircle(nclr, (this->x + this->w - diam), this->y, borderr);
            Drawer->DrawCircle(nclr, this->x, (this->y + this->h - diam), borderr);
            Drawer->DrawCircle(nclr, (this->x + this->w - diam), (this->y + this->h - diam), borderr);
        }
        else
        {
            Drawer->DrawRectangleFill(this->clr, (this->x + borderr), (this->y + borderr), (this->w - diam), (this->h - diam));
            Drawer->DrawRectangleFill(this->clr, (this->x + borderr), this->y, (this->y + this->w - diam), borderr);
            Drawer->DrawRectangleFill(this->clr, (this->x + borderr), (this->y + (this->h - borderr)), (this->w - diam), borderr);
            Drawer->DrawRectangleFill(this->clr, this->x, (this->y + borderr), borderr, (this->h - diam));
            Drawer->DrawRectangleFill(this->clr, (this->x + (this->w - borderr)), (this->y + borderr), borderr, (this->h - diam));
            Drawer->DrawCircle(this->clr, this->x, this->y, borderr);
            Drawer->DrawCircle(this->clr, (this->x + this->w - diam), this->y, borderr);
            Drawer->DrawCircle(this->clr, this->x, (this->y + this->h - diam), borderr);
            Drawer->DrawCircle(this->clr, (this->x + this->w - diam), (this->y + this->h - diam), borderr);
        }
        Drawer->DrawText(this->cnt, draw::SystemFont::Standard, 25, (this->x + ((this->w - textsize) / 2)), (this->y + ((this->h - 25) / 2)), { 0, 0, 0, 255 });
    }

    void Button::OnInput(u64 Input)
    {
        if(this->hover)
        {
            if(!(Input & KEY_TOUCH))
            {
                (this->clickcb)();
                this->hover = false;
            }
            else
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                if(!(((this->x + this->w) > tch.px) && (tch.px > this->x) && ((this->y + this->h) > tch.py) && (tch.py > this->y))) this->hover = false;
            }
        }
        else
        {
            if(Input & KEY_TOUCH)
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                if(((this->x + this->w) > tch.px) && (tch.px > this->x) && ((this->y + this->h) > tch.py) && (tch.py > this->y)) this->hover = true;
            }
        }
    }
}