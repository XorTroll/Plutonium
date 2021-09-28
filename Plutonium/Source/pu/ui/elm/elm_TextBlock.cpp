#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::elm
{
    TextBlock::TextBlock(i32 X, i32 Y, String Text) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->text = Text;
        this->fnt_name = "DefaultFont@25";
        this->ntex = render::RenderText(this->fnt_name, Text, this->clr);
    }

    TextBlock::~TextBlock()
    {
        if(this->ntex != nullptr)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = nullptr;
        }
    }

    i32 TextBlock::GetX()
    {
        return this->x;
    }

    void TextBlock::SetX(i32 X)
    {
        this->x = X;
    }

    i32 TextBlock::GetY()
    {
        return this->y;
    }

    void TextBlock::SetY(i32 Y)
    {
        this->y = Y;
    }

    i32 TextBlock::GetWidth()
    {
        return this->GetTextWidth();
    }

    i32 TextBlock::GetHeight()
    {
        return this->GetTextHeight();
    }

    i32 TextBlock::GetTextWidth()
    {
        return render::GetTextWidth(this->fnt_name, this->text);
    }

    i32 TextBlock::GetTextHeight()
    {
        return render::GetTextHeight(this->fnt_name, this->text);
    }

    String TextBlock::GetText()
    {
        return this->text;
    }

    void TextBlock::SetText(String Text)
    {
        this->text = Text;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, Text, this->clr);
    }

    void TextBlock::SetFont(String font_name)
    {
        this->fnt_name = font_name;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, this->text, this->clr);
    }

    Color TextBlock::GetColor()
    {
        return this->clr;
    }

    void TextBlock::SetColor(Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, this->text, Color);
    }

    void TextBlock::OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y)
    {
        i32 rdx = X;
        i32 rdy = Y;
        Drawer->RenderTexture(this->ntex, rdx, rdy);
    }

    void TextBlock::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
    }
}