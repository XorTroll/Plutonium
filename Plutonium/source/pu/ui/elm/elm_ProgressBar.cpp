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

    void ProgressBar::OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) {
        const auto progress_width = (i32)((this->val / this->max_val) * (double)this->w);
        // TODO: set radius?
        const auto radius = (this->h / 3);
        drawer->RenderRoundedRectangleFill(this->bg_clr, x, y, this->w, this->h, radius);
        drawer->RenderRoundedRectangleFill(this->progress_clr, x, y, progress_width, this->h, radius);
    }

}