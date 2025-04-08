#include <pu/ui/elm/elm_ProgressBar.hpp>

namespace pu::ui::elm {

    ProgressBar::ProgressBar(const s32 x, const s32 y, const s32 width, const s32 height, const double max_val) : Element(), x(x), y(y), w(width), h(height), val(0), max_val(max_val), progress_clr(DefaultProgressColor), bg_clr(DefaultBackgroundColor) {
        this->radius = (u32)((double)height * DefaultHeightRadiusFactor);
    }

    void ProgressBar::SetProgress(const double progress) {
        if(progress >= this->max_val) {
            this->val = this->max_val;
        }
        else {
            this->val = progress;
        }
    }

    void ProgressBar::OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) {
        const auto progress_width = (s32)((this->val / this->max_val) * (double)this->w);
        drawer->RenderRoundedRectangleFill(this->bg_clr, x, y, this->w, this->h, this->radius);
        drawer->RenderRoundedRectangleFill(this->progress_clr, x, y, progress_width, this->h, radius);
    }

}