#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::elm {

    TextBlock::TextBlock(const s32 x, const s32 y, const std::string &text) : Element() {
        this->x = x;
        this->y = y;
        this->clr = DefaultColor;
        this->text_tex = nullptr;
        this->fnt_name = GetDefaultFont(DefaultFontSize::MediumLarge);
        this->clamp_w = NoClamp;
        this->clamp_speed = DefaultClampSpeedSteps;
        this->clamp_delay = DefaultClampStaticDelaySteps;
        this->clamp_cur_x = 0;
        this->clamp_cur_delay = 0;
        this->SetText(text);
    }

    TextBlock::~TextBlock() {
        render::DeleteTexture(this->text_tex);
    }

    s32 TextBlock::GetWidth() {
        const auto base_width = render::GetTextureWidth(this->text_tex);
        const auto do_clamp = (this->clamp_w != NoClamp) && (base_width > this->clamp_w);
        if(do_clamp) {
            return this->clamp_w;
        }
        else {
            return base_width;
        }
    }

    s32 TextBlock::GetHeight() {
        return render::GetTextureHeight(this->text_tex);
    }

    void TextBlock::SetText(const std::string &text) {
        this->text = text;
        render::DeleteTexture(this->text_tex);
        this->text_tex = render::RenderText(this->fnt_name, text, this->clr);
        this->ResetClamp();
    }

    void TextBlock::SetFont(const std::string &font_name) {
        this->fnt_name = font_name;
        this->SetText(this->text);
    }

    void TextBlock::SetColor(const Color clr) {
        this->clr = clr;
        this->SetText(this->text);
    }

    void TextBlock::OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) {
        const auto base_width = render::GetTextureWidth(this->text_tex);
        const auto do_clamp = (this->clamp_w != NoClamp) && (base_width > this->clamp_w);
        if(do_clamp) {
            drawer->RenderTexture(this->text_tex, x, y, render::TextureRenderOptions({}, this->clamp_w, {}, {}, this->clamp_cur_x, 0));

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
            drawer->RenderTexture(this->text_tex, x, y, render::TextureRenderOptions());
        }
    }

}
