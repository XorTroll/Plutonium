#include <pu/element/IconButton.hpp>

namespace pu::element
{
    IconButton::IconButton(u32 X, u32 Y, u32 Radius, std::string Icon) : Element::Element()
    {
        this->x = X + Radius;
        this->y = Y + Radius;
        this->rad = Radius;
        this->icon = Icon;
        this->clr = { 128, 255, 128, 255 };
        this->hover = false;
        this->hoverfact = 255;
        this->clickcb = [](){};
        this->ntex = render::LoadImage(this->icon);
    }

    IconButton::~IconButton()
    {
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
    }

    u32 IconButton::GetX()
    {
        return this->x;
    }

    void IconButton::SetX(u32 X)
    {
        this->x = X;
    }

    u32 IconButton::GetY()
    {
        return this->y;
    }

    void IconButton::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 IconButton::GetWidth()
    {
        return this->rad * 2;
    }

    u32 IconButton::GetHeight()
    {
        return this->rad * 2;
    }

    u32 IconButton::GetRadius()
    {
        return this->rad;
    }

    void IconButton::SetRadius(u32 Radius)
    {
        this->rad = Radius;
    }

    std::string IconButton::GetIconPath()
    {
        return this->icon;
    }

    void IconButton::SetIconPath(std::string Icon)
    {
        this->icon = Icon;
        render::DeleteTexture(this->ntex);
        this->ntex = render::LoadImage(this->icon);
    }

    draw::Color IconButton::GetColor()
    {
        return this->clr;
    }

    void IconButton::SetColor(draw::Color Color)
    {
        this->clr = Color;
    }

    void IconButton::SetOnClick(std::function<void()> ClickCallback)
    {
        this->clickcb = ClickCallback;
    }

    void IconButton::OnRender(render::Renderer *Drawer)
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
            Drawer->RenderCircleFill(this->clr, (this->x + this->rad), (this->y + this->rad), this->rad);
            if(this->hoverfact < 255)
            {
                Drawer->RenderCircleFill({ nr, ng, nb, this->hoverfact }, (this->x + this->rad), (this->y + this->rad), this->rad);
                this->hoverfact += 48;
            }
            else Drawer->RenderCircleFill(nclr, (this->x + this->rad), (this->y + this->rad), this->rad);
        }
        else
        {
            Drawer->RenderCircleFill(this->clr, (this->x + this->rad), (this->y + this->rad), this->rad);
            if(this->hoverfact > 0)
            {
                Drawer->RenderCircleFill({ nr, ng, nb, this->hoverfact }, (this->x + this->rad), (this->y + this->rad), this->rad);
                this->hoverfact -= 48;
            }
            else Drawer->RenderCircleFill(this->clr, (this->x + this->rad), (this->y + this->rad), this->rad);
        }
        u32 f = this->GetWidth();
        u32 sf = (f * 0.6);
        u32 dfx = (this->x + ((f - sf) / 2));
        u32 dfy = (this->y + ((f - sf) / 2));
        Drawer->RenderTextureScaled(this->ntex, dfx, dfy, sf, sf);
    }

    void IconButton::OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus)
    {
        u32 w = this->rad * 2;
        u32 h = w;
        if(this->hover)
        {
            if(Touch)
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                if(!(((this->x + w) > tch.px) && (tch.px > this->x) && ((this->y + h) > tch.py) && (tch.py > this->y)))
                {
                    this->hover = false;
                    this->hoverfact = 255;
                }
            }
            else
            {
                (this->clickcb)();
                this->hover = false;
                this->hoverfact = 255;
            }
        }
        else
        {
            if(Touch)
            {
                touchPosition tch;
                hidTouchRead(&tch, 0);
                if(((this->x + w) > tch.px) && (tch.px > this->x) && ((this->y + h) > tch.py) && (tch.py > this->y))
                {
                    this->hover = true;
                    this->hoverfact = 0;
                }
            }
        }
    }

    void IconButton::OnDirectionPress(DirectionController Controller)
    {

    }
}