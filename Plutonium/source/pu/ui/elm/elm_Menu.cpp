#include <pu/ui/elm/elm_Menu.hpp>
#include <sys/stat.h>

namespace pu::ui::elm {

    void MenuItem::AddOnKey(OnKeyCallback on_key_cb, const u64 key) {
        this->on_key_cbs.push_back(on_key_cb);
        this->on_key_cb_keys.push_back(key);
    }

    void MenuItem::SetIcon(sdl2::TextureHandle::Ref icon) {
        this->icon = icon;
    }

    void Menu::ReloadItemRenders() {
        for(auto &name_tex : this->loaded_name_texs) {
            render::DeleteTexture(name_tex);
        }
        this->loaded_name_texs.clear();
    
        const auto item_count = this->GetItemCount();
        for(u32 i = this->advanced_item_count; i < (this->advanced_item_count + item_count); i++) {
            auto &item = this->items.at(i);
            auto name_tex = render::RenderText(this->font_name, item->GetName(), item->GetColor());
            this->loaded_name_texs.push_back(name_tex);
        }
    }

    void Menu::MoveUp() {
        if(this->selected_item_idx > 0) {
            if(this->selected_item_idx == this->advanced_item_count) {
                this->advanced_item_count--;
                this->selected_item_idx--;
                this->HandleOnSelectionChanged();
                this->ReloadItemRenders();
            }
            else {
                this->prev_selected_item_idx = this->selected_item_idx;
                this->selected_item_idx--;
                this->HandleOnSelectionChanged();

                this->selected_item_alpha = 0;
                this->selected_item_alpha_incr.StartFromZero(this->item_alpha_incr_steps, 0xFF);
                this->prev_selected_item_alpha = 0xFF;
                this->prev_selected_item_alpha_incr.StartToZero(this->item_alpha_incr_steps, 0xFF);
            }
        }
        else {
            this->selected_item_idx = this->items.size() - 1;
            this->advanced_item_count = 0;
            if(this->items.size() >= this->items_to_show) {
                this->advanced_item_count = this->items.size() - this->items_to_show;
                this->ReloadItemRenders();
            }
        }
    }

    void Menu::MoveDown() {
        if(!this->items.empty() && (this->selected_item_idx < (this->items.size() - 1))) {
            if((this->selected_item_idx - this->advanced_item_count) == (this->items_to_show - 1)) {
                this->advanced_item_count++;
                this->selected_item_idx++;
                this->HandleOnSelectionChanged();
                this->ReloadItemRenders();
            }
            else {
                this->prev_selected_item_idx = this->selected_item_idx;
                this->selected_item_idx++;
                this->HandleOnSelectionChanged();

                this->selected_item_alpha = 0;
                this->selected_item_alpha_incr.StartFromZero(this->item_alpha_incr_steps, 0xFF);
                this->prev_selected_item_alpha = 0xFF;
                this->prev_selected_item_alpha_incr.StartToZero(this->item_alpha_incr_steps, 0xFF);
            }
        }
        else {
            this->selected_item_idx = 0;
            this->advanced_item_count = 0;
            if(this->items.size() >= this->items_to_show) {
                this->ReloadItemRenders();
            }
        }
    }

    Menu::Menu(const i32 x, const i32 y, const i32 width, const Color items_clr, const Color items_focus_clr, const i32 items_height, const u32 items_to_show) : Element() {
        this->x = x;
        this->y = y;
        this->w = width;
        this->items_clr = items_clr;
        this->scrollbar_clr = DefaultScrollbarColor;
        this->items_h = items_height;
        this->items_to_show = items_to_show;
        this->prev_selected_item_idx = 0;
        this->selected_item_idx = 0;
        this->advanced_item_count = 0;
        this->selected_item_alpha = 0xFF;
        this->selected_item_alpha_incr = {};
        this->prev_selected_item_alpha = 0;
        this->prev_selected_item_alpha_incr = {};
        this->on_selection_changed_cb = {};
        this->cooldown_enabled = false;
        this->item_touched = false;
        this->items_focus_clr = items_focus_clr;
        this->move_status = MoveStatus::None;
        this->font_name = GetDefaultFont(DefaultFontSize::MediumLarge);
        this->item_alpha_incr_steps = DefaultItemAlphaIncrementSteps;
        this->icon_item_sizes_factor = DefaultIconItemSizesFactor;
        this->icon_margin = DefaultIconMargin;
        this->text_margin = DefaultTextMargin;
        this->light_scrollbar_color_factor = DefaultLightScrollbarColorFactor;
        this->scrollbar_width = DefaultScrollbarWidth;
        this->shadow_height = DefaultShadowHeight;
        this->shadow_base_alpha = DefaultShadowBaseAlpha;
        this->move_wait_time_ms = DefaultMoveWaitTimeMs;
    }

    void Menu::ClearItems() {
        this->items.clear();

        for(auto &name_tex : this->loaded_name_texs) {
            render::DeleteTexture(name_tex);
        }
        this->loaded_name_texs.clear();

        this->selected_item_idx = 0;
        this->prev_selected_item_idx = 0;
        this->advanced_item_count = 0;
    }

    void Menu::SetSelectedIndex(const u32 idx) {
        if(idx < this->items.size()) {
            this->selected_item_idx = idx;
            this->advanced_item_count = 0;
            if(this->selected_item_idx >= (this->items.size() - this->items_to_show)) {
                this->advanced_item_count = this->items.size() - this->items_to_show;
            }
            else if(this->selected_item_idx < this->items_to_show) {
                this->advanced_item_count = 0;
            }
            else {
                this->advanced_item_count = this->selected_item_idx;
            }

            this->ReloadItemRenders();
            this->selected_item_alpha = 0xFF;
            this->prev_selected_item_alpha = 0;
        }
    }

    void Menu::OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) {
        if(!this->items.empty()) {
            const auto item_count = this->GetItemCount();

            if(this->loaded_name_texs.empty()) {
                this->ReloadItemRenders();
            }

            auto cur_item_y = y;
            for(u32 i = this->advanced_item_count; i < (this->advanced_item_count + item_count); i++) {
                const auto loaded_tex_idx = i - this->advanced_item_count;
                auto name_tex = this->loaded_name_texs.at(loaded_tex_idx);
                if(this->selected_item_idx == i) {
                    drawer->RenderRectangleFill(this->items_clr, x, cur_item_y, this->w, this->items_h);
                    if(this->selected_item_alpha < 0xFF) {
                        const auto focus_clr = this->MakeItemsFocusColor(this->selected_item_alpha);
                        drawer->RenderRectangleFill(focus_clr, x, cur_item_y, this->w, this->items_h);
                        this->selected_item_alpha_incr.Increment(this->selected_item_alpha);
                    }
                    else {
                        drawer->RenderRectangleFill(this->items_focus_clr, x, cur_item_y, this->w, this->items_h);
                    }
                }
                else if(this->prev_selected_item_idx == static_cast<i32>(i)) {
                    drawer->RenderRectangleFill(this->items_clr, x, cur_item_y, this->w, this->items_h);
                    if(this->prev_selected_item_alpha > 0) {
                        const auto focus_clr = this->MakeItemsFocusColor(this->prev_selected_item_alpha);
                        drawer->RenderRectangleFill(focus_clr, x, cur_item_y, this->w, this->items_h);
                        this->prev_selected_item_alpha_incr.Increment(this->prev_selected_item_alpha);
                    }
                    else {
                        drawer->RenderRectangleFill(this->items_clr, x, cur_item_y, this->w, this->items_h);
                    }
                }
                else {
                    drawer->RenderRectangleFill(this->items_clr, x, cur_item_y, this->w, this->items_h);
                }

                auto &item = this->items.at(i);
                const auto name_height = render::GetTextureHeight(name_tex);
                auto name_x = x + this->text_margin;
                const auto name_y = cur_item_y + ((this->items_h - name_height) / 2);
                if(item->HasIcon()) {
                    auto icon_tex = this->items.at(i)->GetIconTexture();
                    const auto factor = (float)render::GetTextureHeight(icon_tex->Get()) / (float)render::GetTextureWidth(icon_tex->Get());
                    auto icon_width = (i32)(this->items_h * this->icon_item_sizes_factor);
                    auto icon_height = icon_width;
                    if(factor < 1) {
                        icon_height = (i32)(icon_width * factor);
                    }
                    else {
                        icon_width = (i32)(icon_height * factor);
                    }

                    const auto icon_x = x + this->icon_margin;
                    const auto icon_y = cur_item_y + (this->items_h - icon_height) / 2;
                    name_x = icon_x + icon_width + this->text_margin;
                    drawer->RenderTexture(icon_tex->Get(), icon_x, icon_y, render::TextureRenderOptions::WithCustomDimensions(icon_width, icon_height));
                }
                drawer->RenderTexture(name_tex, name_x, name_y);
                cur_item_y += this->items_h;
            }

            if(this->items_to_show < this->items.size()) {
                const auto scrollbar_x = x + (this->w - this->scrollbar_width);
                const auto scrollbar_height = this->GetHeight();
                drawer->RenderRectangleFill(this->scrollbar_clr, scrollbar_x, y, this->scrollbar_width, scrollbar_height);

                const auto light_scrollbar_clr = this->MakeLighterScrollbarColor();
                const auto scrollbar_factor = (double)this->items_to_show / (double)this->items.size();
                const auto scrollbar_front_height = (u32)(scrollbar_height * scrollbar_factor);
                const auto scrollbar_front_y = y + (u32)(this->advanced_item_count * ((double)scrollbar_height / (double)this->items.size()));
                drawer->RenderRectangleFill(light_scrollbar_clr, scrollbar_x, scrollbar_front_y, this->scrollbar_width, scrollbar_front_height);
            }
            drawer->RenderShadowSimple(x, cur_item_y, this->w, this->shadow_height, this->shadow_base_alpha);
        }
    }

    void Menu::OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) {
        if(this->items.empty()) {
            return;
        }

        if((this->move_status == MoveStatus::WaitingUp) || (this->move_status == MoveStatus::WaitingDown)) {
            const auto cur_time = std::chrono::steady_clock::now();
            const auto time_diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - this->move_start_time).count();
            if(time_diff_ms >= this->move_wait_time_ms) {
                if(this->move_status == MoveStatus::WaitingUp) {
                    this->MoveUp();
                }
                else {
                    this->MoveDown();
                }
                this->move_status = MoveStatus::None;
            }
        }
        if(!touch_pos.IsEmpty()) {
            const auto x = this->GetProcessedX();
            auto cur_item_y = this->GetProcessedY();
            const auto item_count = this->GetItemCount();
            for(u32 i = this->advanced_item_count; i < (this->advanced_item_count + item_count); i++) {
                if(touch_pos.HitsRegion(x, cur_item_y, this->w, this->items_h)) {
                    this->item_touched = true;
                    this->prev_selected_item_idx = this->selected_item_idx;
                    this->selected_item_idx = i;
                    this->HandleOnSelectionChanged();
                    if(i == this->selected_item_idx) {
                        this->selected_item_alpha = 0xFF;
                        this->selected_item_alpha_incr.StartToZero(this->item_alpha_incr_steps, 0xFF);
                    }
                    else if(static_cast<i32>(i) == this->prev_selected_item_idx) {
                        this->prev_selected_item_alpha = 0;
                        this->prev_selected_item_alpha_incr.StartFromZero(this->item_alpha_incr_steps, 0xFF);
                    }
                    break;
                }
                cur_item_y += this->items_h;
            }
        }
        else if(this->item_touched) {
            if((this->selected_item_alpha >= 0xFF) && (this->prev_selected_item_alpha <= 0)) {
                if(this->cooldown_enabled) {
                    this->cooldown_enabled = false;
                }
                else {
                    this->RunSelectedItemCallback(TouchPseudoKey);
                }
                this->item_touched = false;
            }
        }
        else {
            if(keys_down & HidNpadButton_Down) {
                this->MoveDown();
            }
            else if((keys_held & HidNpadButton_StickLDown) || (keys_held & HidNpadButton_StickRDown)) {
                if(this->move_status == MoveStatus::None) {
                    this->move_start_time = std::chrono::steady_clock::now();
                    this->move_status = MoveStatus::WaitingDown;
                }
            }
            else if(keys_down & HidNpadButton_Up) {
                this->MoveUp();
            }
            else if((keys_held & HidNpadButton_StickLUp) || (keys_held & HidNpadButton_StickRUp)) {
                if(this->move_status == MoveStatus::None) {
                    this->move_start_time = std::chrono::steady_clock::now();
                    this->move_status = MoveStatus::WaitingUp;
                }
            }
            else {
                this->RunSelectedItemCallback(keys_down);
            }
        }
    }

}
