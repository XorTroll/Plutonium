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
        this->halign = false;
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

    void TextBlock::SetTextAlign(TextAlign Align)
    {
        this->halign = true;
        this->talign = Align;
    }

    void TextBlock::RemoveTextAlign()
    {
        this->halign = false;
    }

    bool TextBlock::HasTextAlign()
    {
        return this->halign;
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
        u32 tx = this->x;
        u32 ty = this->y;
        if(this->halign) switch(this->talign)
        {
            case TextAlign::CenterHorizontal:
                tx = ((1280 - render::GetTextureWidth(this->ntex)) / 2);
                break;
            case TextAlign::CenterVertical:
                ty = ((720 - render::GetTextureHeight(this->ntex)) / 2);
                break;
            case TextAlign::CenterAll:
                tx = ((1280 - render::GetTextureWidth(this->ntex)) / 2);
                ty = ((720 - render::GetTextureHeight(this->ntex)) / 2);
                break;
        }
        Drawer->RenderTexture(this->ntex, tx, ty);
    }

    void TextBlock::OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus)
    {
    }

    void TextBlock::OnDirectionPress(DirectionController Controller)
    {

    }
}