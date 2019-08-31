#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::elm
{
    TextBlock::TextBlock(s32 X, s32 Y, String Text, s32 FontSize) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->clr = { 0, 0, 0, 255 };
        this->fnt = render::LoadDefaultFont(FontSize);
        this->fsize = FontSize;
        this->ntex = render::RenderText(this->fnt, Text, this->clr);
    }

    TextBlock::~TextBlock()
    {
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
    }

    s32 TextBlock::GetX()
    {
        return this->x;
    }

    void TextBlock::SetX(s32 X)
    {
        this->x = X;
    }

    s32 TextBlock::GetY()
    {
        return this->y;
    }

    void TextBlock::SetY(s32 Y)
    {
        this->y = Y;
    }

    s32 TextBlock::GetWidth()
    {
        return this->GetTextWidth();
    }

    s32 TextBlock::GetHeight()
    {
        return this->GetTextHeight();
    }

    s32 TextBlock::GetTextWidth()
    {
        return render::GetTextWidth(this->fnt, this->text);
    }

    s32 TextBlock::GetTextHeight()
    {
        return render::GetTextHeight(this->fnt, this->text);
    }

    String TextBlock::GetText()
    {
        return this->text;
    }

    void TextBlock::SetText(String Text)
    {
        this->text = Text;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, Text, this->clr);
    }

    void TextBlock::SetFont(render::NativeFont Font)
    {
        this->fnt = Font;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(Font, this->text, this->clr);
    }

    Color TextBlock::GetColor()
    {
        return this->clr;
    }

    void TextBlock::SetColor(Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt, this->text, Color);
    }

    void TextBlock::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
    {
        s32 rdx = X;
        s32 rdy = Y;
        Drawer->RenderTexture(this->ntex, rdx, rdy);
    }

    void TextBlock::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
    {
    }
}