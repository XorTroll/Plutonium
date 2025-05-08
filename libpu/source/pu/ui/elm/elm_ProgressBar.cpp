#include <pu/ui/elm/elm_ProgressBar.hpp>

namespace pu::ui::elm {

    void ProgressBar::SetProgress(const double progress) {
        if(progress >= this->max_val) {
            this->val = this->max_val;
        }
        else {
            this->val = progress;
        }
    }

    void ProgressBar::OnRender(render::Renderer::Ref &drawer) {
        const auto progress_width = (s32)((this->val / this->max_val) * (double)this->GetRenderWidth());

        // drawer->RenderBackgroundShadow(PU_UI_RENDER_XYWH, this->radius, 50, 140, 4);
        drawer->RenderRoundedRectangleFill(this->bg_clr, PU_UI_RENDER_XYWH, this->radius);
        drawer->RenderRoundedRectangleFill(this->progress_clr, PU_UI_RENDER_XY, progress_width, this->GetRenderHeight(), radius);
    }

    bool ProgressBar::OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) {
        if(this->movable) {
            if(this->IsFocused()) {
                const auto progress_diff = this->max_val / (double)this->GetRenderWidth();
                if(((keys_held & HidNpadButton_StickLLeft) || (keys_held & HidNpadButton_StickRLeft)) && (this->val > 0)) {
                    this->DecrementProgress(progress_diff);
                }
                else if(((keys_held & HidNpadButton_StickLRight) || (keys_held & HidNpadButton_StickRRight)) && (this->val < this->max_val)) {
                    this->IncrementProgress(progress_diff);
                }

                return true;
            }

            if(touch_pos.HitsRegion(PU_UI_RENDER_XYWH) && !touch_pos.is_scrolling) {
                this->RequestFocus();

                const auto new_prog_val = ((double)(touch_pos.x - this->GetRenderX()) / (double)this->GetRenderWidth()) * this->max_val;
                this->SetProgress(new_prog_val);

                return true;
            }
        }

        return false;
    }

}
