#include <pu/ui/elm/elm_Button.hpp>

namespace pu::ui::elm {

    Button::Button(const s32 x, const s32 y, const s32 width, const s32 height, const std::string &content, const Color content_clr, const Color bg_clr) : Element() {
        this->x = x;
        this->y = y;
        this->w = width;
        this->h = height;
        this->cnt = content;
        this->cnt_clr = content_clr;
        this->bg_clr = bg_clr;
        this->hover = false;
        this->hover_alpha = 0xFF;
        this->hover_alpha_incr = {};
        this->fnt_name = GetDefaultFont(DefaultContentFontSize);
        this->cnt_tex = nullptr;
        this->SetContent(content);
        this->on_click_cb = {};
        this->darker_color_factor = DefaultDarkerColorFactor;
        this->hover_alpha_incr_steps = DefaultHoverAlphaIncrementSteps;
    }

    Button::~Button() {
        render::DeleteTexture(this->cnt_tex);
    }

    void Button::SetContent(const std::string &content) {
        this->cnt = content;
        render::DeleteTexture(this->cnt_tex);
        this->cnt_tex = render::RenderText(this->fnt_name, content, this->cnt_clr);
    }

    void Button::SetContentColor(const Color content_clr) {
        this->cnt_clr = content_clr;
        this->SetContent(this->cnt);
    }

    void Button::SetContentFont(const std::string &font_name) {
        this->fnt_name = font_name;
        this->SetContent(this->cnt);
    }

    void Button::OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) {
        drawer->RenderRectangleFill(this->bg_clr, x, y, this->w, this->h);
        if(this->hover) {
            if(this->hover_alpha < 0xFF) {
                const auto hover_bg_clr = this->MakeHoverBackgroundColor(this->hover_alpha);
                drawer->RenderRectangleFill(hover_bg_clr, x, y, this->w, this->h);
                this->hover_alpha_incr.Increment(this->hover_alpha);
            }
            else {
                const auto darker_bg_clr = this->MakeHoverBackgroundColor(-1);
                drawer->RenderRectangleFill(darker_bg_clr, x, y, this->w, this->h);
            }
        }
        else {
            if(this->hover_alpha > 0) {
                const auto hover_bg_clr = this->MakeHoverBackgroundColor(this->hover_alpha);
                drawer->RenderRectangleFill(hover_bg_clr, x, y, this->w, this->h);
                this->hover_alpha_incr.Increment(this->hover_alpha);
            }
            else {
                drawer->RenderRectangleFill(this->bg_clr, x, y, this->w, this->h);
            }
        }

        const auto cnt_width = render::GetTextureWidth(this->cnt_tex);
        const auto cnt_height = render::GetTextureHeight(this->cnt_tex);
        const auto cnt_x = x + ((this->w - cnt_width) / 2);
        const auto cnt_y = y + ((this->h - cnt_height) / 2);
        drawer->RenderTexture(this->cnt_tex, cnt_x, cnt_y);
    }

    void Button::OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) {
        if(this->hover) {
            if(touch_pos.IsEmpty()) {
                if(this->on_click_cb) {
                    this->on_click_cb();
                }

                this->hover = false;
                this->hover_alpha = 0xFF;
                this->hover_alpha_incr.StartToZero(this->hover_alpha_incr_steps, 0xFF);
            }
        }
        else {
            if(touch_pos.HitsRegion(this->x, this->y, this->w, this->h)) {
                this->hover = true;
                this->hover_alpha = 0;
                this->hover_alpha_incr.StartFromZero(this->hover_alpha_incr_steps, 0xFF);
            }
        }
    }
}