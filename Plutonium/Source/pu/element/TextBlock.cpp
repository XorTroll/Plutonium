#include <pu/element/TextBlock.hpp>

namespace pu::element
{
    TextBlock::TextBlock(u32 X, u32 Y, std::string Text, u32 FontSize) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = { 0, 0, 0, 255 };
        this->fnt = render::LoadSharedFont(render::SharedFont::Standard, FontSize);
        this->fsize = FontSize;
        this->ntex = render::RenderText(this->fnt, Text, this->clr);
    }

    TextBlock::~TextBlock()
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

    u32 TextBlock::GetX()
    {
        return this->x;
    }

    void TextBlock::SetX(u32 X)
    {
        this->x = X;
    }

    u32 TextBlock::GetY()
    {
        return this->y;
    }

    void TextBlock::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 TextBlock::GetWidth()
    {
        return (this->text.length() * this->fsize);
    }

    u32 TextBlock::GetHeight()
    {
        return this->fsize;
    }

    std::string TextBlock::GetText()
    {
        return this->text;
    }

    void TextBlock::SetText(std::string Text)
    {
        this->text = Text;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, Text, this->clr);
    }

    void TextBlock::SetFont(render::NativeFont Font)
    {
        render::DeleteFont(this->fnt);
        this->fnt = Font;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(Font, this->text, this->clr);
    }

    draw::Color TextBlock::GetColor()
    {
        return this->clr;
    }

    void TextBlock::SetColor(draw::Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->text, Color);
    }

    void TextBlock::OnRender(render::Renderer *Drawer)
    {
        Drawer->RenderTexture(this->ntex, this->x, this->y);
    }

    void TextBlock::OnInput(u64 Down, u64 Up, u64 Held)
    {
    }
}