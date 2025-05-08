#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::elm {

    s32 TextBlock::GetWidth() {
        const auto base_width = this->text->GetWidth();
        const auto do_clamp = (this->clamp_w != NoClamp) && (base_width > this->clamp_w);
        if(do_clamp) {
            return this->clamp_w;
        }
        else {
            return base_width;
        }
    }

    s32 TextBlock::GetHeight() {
        return this->text->GetHeight();
    }

    void TextBlock::OnRender(render::Renderer::Ref &drawer) {
        const auto base_width = this->text->GetWidth();
        const auto do_clamp = (this->clamp_w != NoClamp) && (base_width > this->clamp_w);
        if(do_clamp) {
            drawer->RenderTexture(this->text->GetTexture(), PU_UI_RENDER_XY, render::TextureRenderOptions({}, this->GetRenderWidth(), {}, {}, this->clamp_cur_x, 0));

            if(this->clamp_cur_x >= (base_width - this->clamp_w)) {
                this->clamp_cur_delay++;
                if(this->clamp_cur_delay >= this->clamp_delay) {
                    this->clamp_cur_x = 0;
                    this->clamp_cur_delay = 0;
                }
            }
            else if(this->clamp_cur_x == 0) {
                this->clamp_cur_delay++;
                if(this->clamp_cur_delay >= this->clamp_delay) {
                    this->clamp_cur_x++;
                    this->clamp_cur_delay = 0;
                }
            }
            else {
                this->clamp_cur_x += this->clamp_speed;
            }
        }
        else {
            drawer->RenderTexture(this->text->GetTexture(), PU_UI_RENDER_XY, render::TextureRenderOptions());
        }
    }

}
