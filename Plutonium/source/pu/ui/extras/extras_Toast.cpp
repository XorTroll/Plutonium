#include <pu/ui/extras/extras_Toast.hpp>

namespace pu::ui::extras {

    Toast::Toast(elm::TextBlock::Ref &text_block, const Color bg_clr) : Overlay(0, DefaultY, 0, 0, bg_clr) {
        this->height_and_text_height_factor = DefaulHeightAndTextHeightFactor;
        this->h_margin = DefaulHorizontalMargin;
        this->base_alpha = DefaulBaseAlpha;
        text_block->SetHorizontalAlign(elm::HorizontalAlign::Center);
        text_block->SetVerticalAlign(elm::VerticalAlign::Center);
        this->text = text_block;
        this->AdjustDimensions();
        this->Add(this->text);
    }

    void Toast::AdjustDimensions() {
        const auto text_width = this->text->GetWidth();
        const auto text_height = this->text->GetHeight();
        const auto toast_width = text_width + 2 * this->h_margin;
        const auto toast_height = text_height * this->height_and_text_height_factor;
        this->SetX((render::ScreenWidth - toast_width) / 2);
        this->SetWidth(toast_width);
        this->SetHeight(toast_height);
    }

    void Toast::SetText(const std::string &text) {
        this->text->SetText(text);
        this->AdjustDimensions();
    }

    void Toast::OnPreRender(render::Renderer::Ref &drawer) {
        drawer->SetBaseRenderAlpha(this->base_alpha);
    }

    void Toast::OnPostRender(render::Renderer::Ref &drawer) {
        drawer->ResetBaseRenderAlpha();
    }

}
