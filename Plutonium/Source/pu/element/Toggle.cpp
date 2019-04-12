#include <pu/element/Toggle.hpp>

namespace pu::element
{
    Toggle::Toggle(u32 X, u32 Y, std::string Content, u64 Key, draw::Color Color) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->key = Key;
        this->cnt = Content;
        this->clr = Color;
        this->fnt = render::LoadSharedFont(render::SharedFont::Standard, 25);
        this->fsize = 25;
        this->togfact = 255;
        this->checked = false;
        this->ntex = render::RenderText(this->fnt, Content, Color);
    }

    Toggle::~Toggle()
    {
        if(this->fnt != NULL)
        {
            render::DeleteFont(this->fnt);
            this->fnt = NULL;
        }
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
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
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, Content, this->clr);
    }

    void Toggle::SetFont(render::NativeFont Font)
    {
        render::DeleteFont(this->fnt);
        this->fnt = Font;
        this->ntex = render::RenderText(Font, this->cnt, this->clr);
    }

    draw::Color Toggle::GetColor()
    {
        return this->clr;
    }

    void Toggle::SetColor(draw::Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->cnt, Color);
    }

    u64 Toggle::GetKey()
    {
        return this->key;
    }

    void Toggle::SetKey(u64 Key)
    {
        this->key = Key;
    }

    bool Toggle::IsChecked()
    {
        return this->checked;
    }

    void Toggle::OnRender(render::Renderer *Drawer)
    {
        u32 tw = render::GetTextWidth(this->fnt, this->cnt);
        u32 th = render::GetTextHeight(this->fnt, this->cnt);
        u32 rw = th;
        u32 rh = (2 * th);
        u32 rx = this->GetProcessedX();
        u32 ry = this->GetProcessedY();
        u32 tx = rx + rw + (th / 2);
        u32 ty = ry + (th / 2);
        if(this->checked)
        {
            Drawer->RenderRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
            if(this->togfact < 255)
            {
                Drawer->RenderRectangleFill({ this->clr.R, this->clr.G, this->clr.B, (255 - this->togfact) }, rx, ry, rw, rh);
                this->togfact += 48;
            }
            else Drawer->RenderRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
        }
        else
        {
            Drawer->RenderRectangleFill(this->clr, rx, ry, rw, rh);
            if(this->togfact > 0)
            {
                Drawer->RenderRectangleFill({ 130, 130, 130, this->togfact }, rx, ry, rw, rh);
                this->togfact -= 48;
            }
            else Drawer->RenderRectangleFill(this->clr, rx, ry, rw, rh);
        }
        Drawer->RenderTexture(this->ntex, tx, ty);
    }

    void Toggle::OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus)
    {
        if((Down & this->key) || ((this->key == KEY_TOUCH) && Touch)) this->checked = !this->checked;
    }
}