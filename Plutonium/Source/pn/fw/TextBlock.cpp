#include <pn/fw/TextBlock.hpp>

namespace pn::fw
{
    TextBlock::TextBlock(u32 X, u32 Y, std::string Text)
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = { 0, 0, 0, 255 };
        this->fnt = draw::SystemFont::Standard;
        this->fsize = 25;
    }

    TextBlock::TextBlock(u32 X, u32 Y, std::string Text, draw::Color TextColor)
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = TextColor;
        this->fnt = draw::SystemFont::Standard;
        this->fsize = 25;
    }

    TextBlock::TextBlock(u32 X, u32 Y, std::string Text, draw::SystemFont Font)
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = { 0, 0, 0, 255 };
        this->fnt = Font;
        this->fsize = 25;
    }

    TextBlock::TextBlock(u32 X, u32 Y, std::string Text, draw::Color TextColor, draw::SystemFont Font)
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = TextColor;
        this->fnt = Font;
        this->fsize = 25;
    }

    TextBlock::TextBlock(u32 X, u32 Y, std::string Text, draw::Color TextColor, draw::SystemFont Font, u32 Size)
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = TextColor;
        this->fnt = Font;
        this->fsize = Size;
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
    }

    draw::SystemFont TextBlock::GetFont()
    {
        return this->fnt;
    }

    void TextBlock::SetFont(draw::SystemFont Font)
    {
        this->fnt = Font;
    }

    u32 TextBlock::GetFontSize()
    {
        return this->fsize;
    }

    void TextBlock::SetFontSize(u32 Size)
    {
        this->fsize = Size;
    }

    draw::Color TextBlock::GetColor()
    {
        return this->clr;
    }

    void TextBlock::SetColor(draw::Color TextColor)
    {
        this->clr = TextColor;
    }

    void TextBlock::OnRender(render::Renderer *Drawer)
    {
        Drawer->DrawText(this->text, this->fnt, this->fsize, this->x, this->y, this->clr);
    }

    void TextBlock::OnGlobalInput(u64 Input)
    {
    }

    void TextBlock::OnTouch(u32 TouchX, u32 TouchY)
    {
    }
}