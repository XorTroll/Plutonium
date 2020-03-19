#include <pu/ui/elm/elm_Button.hpp>

namespace pu::ui::elm
{
    Button::Button(i32 X, i32 Y, i32 Width, i32 Height, String Content, Color TextColor, Color Color) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->cnt = Content;
        this->clr = Color;
        this->hover = false;
        this->hoverfact = 255;
        this->fnt_name = "DefaultFont@25";
        this->ntex = render::RenderText(this->fnt_name, Content, TextColor);
        this->clickcb = [](){};
    }

    Button::~Button()
    {
        if(this->ntex != nullptr)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = nullptr;
        }
    }

    i32 Button::GetX()
    {
        return this->x;
    }

    void Button::SetX(i32 X)
    {
        this->x = X;
    }

    i32 Button::GetY()
    {
        return this->y;
    }

    void Button::SetY(i32 Y)
    {
        this->y = Y;
    }

    i32 Button::GetWidth()
    {
        return this->w;
    }

    void Button::SetWidth(i32 Width)
    {
        this->w = Width;
    }

    i32 Button::GetHeight()
    {
        return this->h;
    }

    void Button::SetHeight(i32 Height)
    {
        this->h = Height;
    }

    String Button::GetContent()
    {
        return this->cnt;
    }

    void Button::SetContent(String Content)
    {
        this->cnt = Content;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, Content, this->clr);
    }

    Color Button::GetColor()
    {
        return this->clr;
    }

    void Button::SetColor(Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, this->cnt, Color);
    }

    void Button::SetContentFont(String font_name)
    {
        this->fnt_name = font_name;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, this->cnt, this->clr);
    }

    void Button::SetOnClick(std::function<void()> ClickCallback)
    {
        this->clickcb = ClickCallback;
    }

    void Button::OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y)
    {
        i32 rdx = X;
        i32 rdy = Y;
        i32 clrr = this->clr.R;
        i32 clrg = this->clr.G;
        i32 clrb = this->clr.B;
        i32 nr = clrr - 70;
        if(nr < 0) nr = 0;
        i32 ng = clrg - 70;
        if(ng < 0) ng = 0;
        i32 nb = clrb - 70;
        if(nb < 0) nb = 0;
        Color nclr(nr, ng, nb, this->clr.A);
        if(this->hover)
        {
            Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
            if(this->hoverfact < 255)
            {
                Drawer->RenderRectangleFill({ nr, ng, nb, this->hoverfact }, rdx, rdy, this->w, this->h);
                this->hoverfact += 48;
            }
            else Drawer->RenderRectangleFill(nclr, rdx, rdy, this->w, this->h);
        }
        else
        {
            Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
            if(this->hoverfact > 0)
            {
                Drawer->RenderRectangleFill({ nr, ng, nb, this->hoverfact }, rdx, rdy, this->w, this->h);
                this->hoverfact -= 48;
            }
            else Drawer->RenderRectangleFill(this->clr, rdx, rdy, this->w, this->h);
        }
        i32 xw = render::GetTextWidth(this->fnt_name, this->cnt);
        i32 xh = render::GetTextHeight(this->fnt_name, this->cnt);
        i32 tx = ((this->w - xw) / 2) + rdx;
        i32 ty = ((this->h - xh) / 2) + rdy;
        Drawer->RenderTexture(this->ntex, tx, ty);
    }

    void Button::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
        if(this->hover)
        {
            if(Pos.IsEmpty())
            {
                (this->clickcb)();
                this->hover = false;
                this->hoverfact = 255;
            }
        }
        else
        {
            if(!Pos.IsEmpty())
            {
                if((Pos.X >= x) && (Pos.X < (x + w)) && (Pos.Y >= y) && (Pos.Y < (y + h)))
                {
                    this->hover = true;
                    this->hoverfact = 0;
                }
            }
        }
    }
}