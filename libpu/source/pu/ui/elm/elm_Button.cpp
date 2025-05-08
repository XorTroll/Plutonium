#include <pu/ui/elm/elm_Button.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui::elm {

    void Button::HandleClick() {
        GetStyle()->OnButtonClickUp(this->shared_from_this());
        if(this->on_click_cb) {
            this->on_click_cb();
        }
    }

    void Button::OnRender(render::Renderer::Ref &drawer) {
        auto actual_bg_clr = this->bg_clr;
        if(this->touch_detector.IsHeld()) {
            actual_bg_clr = this->bg_held_clr;
        }

        // TODO: tuneable parameters?
        // drawer->RenderBackgroundShadow(PU_UI_RENDER_XYWH, this->radius, 90, 200, 4);
        drawer->RenderRoundedRectangleFill(actual_bg_clr, PU_UI_RENDER_XYWH, this->radius);

        const auto text_y = this->GetRenderY() + (abs(this->GetRenderHeight() - this->text->GetHeight()) / 2);
        s32 text_x;
        switch(this->text_placement) {
            case TextPlacement::Left: {
                text_x = this->GetRenderX() + this->text_margin_left;
                break;
            }
            case TextPlacement::Right: {
                text_x = this->GetRenderX() + this->GetRenderWidth() - this->text_margin_right - this->text->GetWidth();
                break;
            }
            default: {
                text_x = this->GetRenderX() + (abs(this->GetRenderWidth() - this->text->GetWidth()) / 2);
                break;
            }
        }

        drawer->RenderTexture(this->text->GetTexture(), text_x, text_y);

        if(this->border_thickness > 0) {
            drawer->RenderRoundedRectangleBorder(this->border_clr, PU_UI_RENDER_XYWH, this->radius, this->border_thickness);
        }
    }

    bool Button::OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) {
        this->touch_detector.Update(touch_pos, PU_UI_RENDER_XYWH);
        if(touch_pos.HitsRegion(PU_UI_RENDER_XYWH)) {
            this->RequestFocus();
            return true;
        }

        if(this->touch_detector.ConsumeClicked() || (keys_down & this->touch_key)) {
            this->RequestFocus();
            this->HandleClick();
            return true;
        }

        if(this->IsFocused()) {
            if(keys_up & HidNpadButton_A) {
                this->HandleClick();
            }
        }

        return false;
    }

}
