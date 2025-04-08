#include <pu/ui/elm/elm_Toggle.hpp>

namespace pu::ui::elm {

    Toggle::Toggle(const s32 x, const s32 y, const std::string &content, const u64 toggle_key, const Color clr) : Element() {
        this->x = x;
        this->y = y;
        this->key = toggle_key;
        this->clr = clr;
        this->cnt_tex = nullptr;
        this->fnt_name = GetDefaultFont(DefaultContentFontSize);
        this->toggle_alpha = 0xFF;
        this->checked = false;
        this->SetContent(content);
        this->cnt_h_margin = DefaultContentHorizontalMargin;
        this->cnt_v_margin = DefaultContentVerticalMargin;
        this->toggle_alpha_incr = DefaultToggleAlphaIncrement;
    }

    Toggle::~Toggle() {
        render::DeleteTexture(this->cnt_tex);
    }

    s32 Toggle::GetWidth() {
        return render::GetTextureWidth(this->cnt_tex) + 2 * this->cnt_h_margin;
    }

    s32 Toggle::GetHeight() {
        return render::GetTextureHeight(this->cnt_tex) + 2 * this->cnt_v_margin;
    }

    void Toggle::SetContent(const std::string &content) {
        this->cnt = content;
        render::DeleteTexture(this->cnt_tex);
        this->cnt_tex = render::RenderText(this->fnt_name, content, this->clr);
    }

    void Toggle::SetFont(const std::string &font_name) {
        this->fnt_name = font_name;
        this->SetContent(this->cnt);
    }

    void Toggle::SetColor(const Color clr) {
        this->clr = clr;
        this->SetContent(this->cnt);
    }

    void Toggle::OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) {
        const auto bg_width = this->GetWidth();
        const auto bg_height = this->GetHeight();
        const auto cnt_x = x + this->cnt_h_margin;
        const auto cnt_y = y + this->cnt_v_margin;
        if(this->checked) {
            drawer->RenderRectangleFill(MakeBackgroundColor(0xFF), x, y, bg_width, bg_height);
            if(this->toggle_alpha < 0xFF) {
                drawer->RenderRectangleFill(MakeBackgroundColor(0xFF - this->toggle_alpha), x, y, bg_width, bg_height);
                this->toggle_alpha += this->toggle_alpha_incr;
            }
            else {
                drawer->RenderRectangleFill(MakeBackgroundColor(0xFF), x, y, bg_width, bg_height);
            }
        }
        else {
            drawer->RenderRectangleFill(this->clr, x, y, bg_width, bg_height);
            if(this->toggle_alpha > 0)
            {
                drawer->RenderRectangleFill(MakeBackgroundColor(this->toggle_alpha), x, y, bg_width, bg_height);
                this->toggle_alpha -= this->toggle_alpha_incr;
            }
            else {
                drawer->RenderRectangleFill(this->clr, x, y, bg_width, bg_height);
            }
        }
        drawer->RenderTexture(this->cnt_tex, cnt_x, cnt_y);
    }

    void Toggle::OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) {
        if((keys_down & this->key) || ((this->key == TouchPseudoKey) && touch_pos.HitsRegion(this->x, this->y, this->GetWidth(), this->GetHeight()))) {
            this->checked = !this->checked;
        }
    }

}
