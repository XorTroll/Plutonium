#include <pu/ui/extras/extras_Toast.hpp>

namespace pu::ui::extras {

    Toast::Toast(const std::string &text, const std::string &font_name, const Color text_clr, const Color bg_clr) : Overlay(0, DefaultY, 0, 0, bg_clr) {
        this->text = elm::TextBlock::New(0, 0, text);
        this->text->SetFont(font_name);
        this->text->SetColor(text_clr);
        this->text->SetHorizontalAlign(elm::HorizontalAlign::Center);
        this->text->SetVerticalAlign(elm::VerticalAlign::Center);
        this->AdjustDimensions();
        this->Add(this->text);
    }

    void Toast::AdjustDimensions() {
        const auto text_width = this->text->GetWidth();
        const auto text_height = this->text->GetHeight();
        const auto toast_width = text_width + 2 * HorizontalMargin;
        const auto toast_height = text_height * HeightAndTextHeightFactor;
        this->SetX((render::ScreenWidth - toast_width) / 2);
        this->SetWidth(toast_width);
        this->SetHeight(toast_height);
    }

    void Toast::SetText(const std::string &text) {
        this->text->SetText(text);
        this->AdjustDimensions();
    }

    void Toast::OnPreRender(render::Renderer::Ref &drawer) {
        drawer->SetBaseRenderAlpha(BaseAlpha);
    }

    void Toast::OnPostRender(render::Renderer::Ref &drawer) {
        drawer->ResetBaseRenderAlpha();
    }

}