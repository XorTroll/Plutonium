#include <pu/ui/ui_Text.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

    void Text::UpdateTexture() {
        render::DeleteTexture(this->text_tex);
        this->text_tex = render::RenderText(this->font_name, this->text, this->clr);
    }

    Text::Text(const std::string &text, const std::string &font_name, const u32 flavor) : text(text), font_name(font_name), clr(GetStyle()->GetTextColor(flavor)), text_tex(nullptr) {
        this->UpdateTexture();
    }

    Text::~Text() {
        render::DeleteTexture(this->text_tex);
    }

    s32 Text::GetWidth() {
        return render::GetTextureWidth(this->text_tex);
    }

    s32 Text::GetHeight() {
        return render::GetTextureHeight(this->text_tex);
    }

    void Text::SetText(const std::string &text) {
        this->text = text;
        this->UpdateTexture();
    }

    void Text::SetFont(const std::string &font_name) {
        this->font_name = font_name;
        this->UpdateTexture();
    }

    void Text::SetColor(const Color &clr) {
        this->clr = clr;
        this->UpdateTexture();
    }

}
