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
        this->hoverfact = 255;
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
        if(this->hover)
        {
            Drawer->DrawRectangleFill(this->clr, this->x, this->y, this->w, this->h);
            if(this->hoverfact < 255)
            {
                Drawer->DrawRectangleFill(draw::Color(nr, ng, nb, this->hoverfact), this->x, this->y, this->w, this->h);
                this->hoverfact += 48;
            }
            else Drawer->DrawRectangleFill(nclr, this->x, this->y, this->w, this->h);
        }
        else
        {
            Drawer->DrawRectangleFill(this->clr, this->x, this->y, this->w, this->h);
            if(this->hoverfact > 0)
            {
                Drawer->DrawRectangleFill(draw::Color(nr, ng, nb, this->hoverfact), this->x, this->y, this->w, this->h);
                this->hoverfact -= 48;
            }
            else Drawer->DrawRectangleFill(this->clr, this->x, this->y, this->w, this->h);
        }
        u32 xw = Drawer->GetTextWidth(draw::Font::Custom, this->cnt, 25);
        u32 xh = Drawer->GetTextHeight(draw::Font::Custom, this->cnt, 25);
        u32 tx = ((this->w - xw) / 2) + this->x;
        u32 ty = ((this->h - xh) / 2) + this->y;
        Drawer->DrawText(this->cnt, draw::Font::Custom, 25, tx, ty, { 0, 0, 0, 255 });
    }

    void Button::OnInput(u64 Input)
    {
        if(this->hover)
        {
            if(!(Input & KEY_TOUCH))
            {
                (this->clickcb)();
                this->hover = false;
                this->hoverfact = 255;
            }
            else
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                if(!(((this->x + this->w) > tch.px) && (tch.px > this->x) && ((this->y + this->h) > tch.py) && (tch.py > this->y)))
                {
                    this->hover = false;
                    this->hoverfact = 255;
                }
            }
        }
        else
        {
            if(Input & KEY_TOUCH)
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                if(((this->x + this->w) > tch.px) && (tch.px > this->x) && ((this->y + this->h) > tch.py) && (tch.py > this->y)) if(!this->hover)
                {
                    this->hover = true;
                    this->hoverfact = 0;
                }
            }
        }
    }
}