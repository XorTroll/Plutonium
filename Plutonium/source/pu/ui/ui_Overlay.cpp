#include <pu/ui/ui_Overlay.hpp>

namespace pu::ui {

    bool Overlay::Render(render::Renderer::Ref &drawer) {
        this->OnPreRender(drawer);
        drawer->SetBaseRenderAlpha(static_cast<u8>(this->fade_a));
        if(this->round) {
            drawer->RenderRoundedRectangleFill(this->bg_clr, this->x, this->y, this->w, this->h, this->rad);
        }
        else {
            drawer->RenderRectangleFill(this->bg_clr, this->x, this->y, this->w, this->h);
        }

        this->PreRender();
        for(auto &elem: this->elems) {
            if(elem->IsVisible()) {
                elem->OnRender(drawer, elem->GetProcessedX(), elem->GetProcessedY());
            }
        }
        drawer->ResetBaseRenderAlpha();
        if(this->is_ending) {
            if(this->fade_a > 0) {
                this->fade_a -= FadeAlphaVariation;
            }
            else {
                this->fade_a = 0;
            }
        }
        else {
            if(this->fade_a < MaxFadeAlpha) {
                this->fade_a += FadeAlphaVariation;
            }
            else {
                this->fade_a = MaxFadeAlpha;
            }
        }
        this->OnPostRender(drawer);
        const auto is_finished = this->is_ending && (this->fade_a == 0);
        if(is_finished) {
            this->is_ending = false;
        }
        return !is_finished;
    }

}