#include <pu/ui/ly/ly_Toast.hpp>

namespace pu::ui::ly {

    void Toast::OnStart() {
        this->fade_alpha = 0;
        this->is_ending = false;
        this->fade_alpha_incr.StartFromZero(this->fade_alpha_incr_steps, this->base_alpha);
        this->start_time = std::chrono::steady_clock::now();

        // Pre-calculate dimensions
        const auto text_width = this->text->GetWidth();
        const auto text_height = this->text->GetHeight();
        const auto toast_width = text_width + 2 * this->h_margin;
        this->x = (render::ScreenWidth - toast_width) / 2;
        this->width = toast_width;
        this->text_x = this->x + this->h_margin;
        this->text_y = this->y + (this->height - text_height) / 2;
    }

    void Toast::OnRender(render::Renderer::Ref &drawer) {
        drawer->SetBaseRenderAlpha(this->fade_alpha);

        if(this->radius > 0) {
            drawer->RenderRoundedRectangleFill(this->bg_clr, this->x, this->y, this->width, this->height, this->radius);
        }
        else {
            drawer->RenderRectangleFill(this->bg_clr, this->x, this->y, this->width, this->height);
        }

        drawer->RenderTexture(this->text->GetTexture(), this->text_x, this->text_y);

        if(this->is_ending) {
            if(this->fade_alpha_incr.Increment(this->fade_alpha)) {
                this->SetActive(false);
            }
        }
        else {
            this->fade_alpha_incr.Increment(this->fade_alpha);

            const auto elapsed_time = std::chrono::steady_clock::now() - this->start_time;
            const auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();
            if(elapsed_time_ms >= this->duration_ms) {
                this->is_ending = true;
                this->fade_alpha_incr.StartToZero(this->fade_alpha_incr_steps, this->base_alpha);
            }
        }

        drawer->ResetBaseRenderAlpha();
    }

}
