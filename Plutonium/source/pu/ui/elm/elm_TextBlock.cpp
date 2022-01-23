#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::elm {

    TextBlock::TextBlock(const i32 x, const i32 y, const std::string &text) : Element::Element() {
        this->x = x;
        this->y = y;
        this->clr = DefaultColor;
        this->text_tex = nullptr;
        this->fnt_name = GetDefaultFont(DefaultFontSize::MediumLarge);
        this->SetText(text);
    }

    TextBlock::~TextBlock() {
        render::DeleteTexture(this->text_tex);
    }

    i32 TextBlock::GetWidth() {
        return render::GetTextureWidth(this->text_tex);
    }

    i32 TextBlock::GetHeight() {
        return render::GetTextureHeight(this->text_tex);
    }

    void TextBlock::SetText(const std::string &text) {
        this->text = text;
        render::DeleteTexture(this->text_tex);
        this->text_tex = render::RenderText(this->fnt_name, text, this->clr);
    }

    void TextBlock::SetFont(const std::string &font_name) {
        this->fnt_name = font_name;
        this->SetText(this->text);
    }

    void TextBlock::SetColor(const Color clr) {
        this->clr = clr;
        this->SetText(this->text);
    }

    void TextBlock::OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) {
        drawer->RenderTexture(this->text_tex, x, y);
    }

}