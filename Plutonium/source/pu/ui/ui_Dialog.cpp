#include <pu/ui/ui_Dialog.hpp>
#include <pu/ui/ui_Application.hpp>

namespace pu::ui {

    void Dialog::LoadTitle() {
        render::DeleteTexture(this->title_tex);
        this->title_tex = render::RenderText(this->title_font_name, this->title, this->title_clr);
    }

    void Dialog::LoadContent() {
        render::DeleteTexture(this->cnt_tex);
        this->cnt_tex = render::RenderText(this->cnt_font_name, this->cnt, this->cnt_clr);
    }

    void Dialog::DisposeIcon() {
        this->icon_tex = {};
    }

    Dialog::Dialog(const std::string &title, const std::string &content) {
        this->title_font_name = GetDefaultFont(DefaultFontSize::Large);
        this->cnt_font_name = GetDefaultFont(DefaultFontSize::Medium);
        this->opt_font_name = GetDefaultFont(DefaultFontSize::Small);
        this->title = title;
        this->cnt = content;
        this->title_tex = nullptr;
        this->cnt_tex = nullptr;
        this->icon_tex = nullptr;
        this->selected_opt_idx = 0;
        this->prev_selected_opt_idx = 0;
        this->selected_opt_over_alpha = 0xFF;
        this->prev_selected_opt_over_alpha = 0;
        this->user_cancelled = false;

        this->title_clr = DefaultTitleColor;
        this->cnt_clr = DefaultContentColor;
        this->opt_clr = DefaultOptionColor;
        this->dialog_border_radius = DefaultDialogBorderRadius;
        this->space_between_options = DefaultSpaceBetweenOptions;
        this->space_between_option_rows = DefaultSpaceBetweenOptionRows;
        this->title_extra_width = DefaultTitleExtraWidth;
        this->cnt_extra_width = DefaultContentExtraWidth;
        this->space_between_cnt_and_options = DefaultSpaceBetweenContentAndOptions;
        this->title_top_margin = DefaultTitleTopMargin;
        this->title_x = DefaultTitleX;
        this->title_y = DefaultTitleY;
        this->cnt_x = DefaultContentX;
        this->cnt_y = DefaultContentY;
        this->opts_base_h_margin = DefaultOptionsBaseHorizontalMargin;
        this->opt_height = DefaultOptionHeight;
        this->opt_h_margin = DefaultOptionHorizontalMargin;
        this->opt_border_radius = DefaultOptionBorderRadius;
        this->opt_bottom_margin = DefaultOptionBottomMargin;
        this->max_screen_fade_alpha = DefaultMaxScreenFadeAlpha;
        this->icon_margin = DefaultIconMargin;
        this->dialog_clr = DefaultDialogColor;
        this->over_clr = DefaultOverColor;
        this->over_alpha_incr_steps = DefaultOverAlphaIncrementSteps;
        this->fade_alpha_incr_steps = DefaultFadeAlphaIncrementSteps;

        this->LoadTitle();
        this->LoadContent();
    }

    Dialog::~Dialog() {
        render::DeleteTexture(this->title_tex);
        render::DeleteTexture(this->cnt_tex);
        this->DisposeIcon();
    }

    void Dialog::AddOption(const std::string &opt_name)  {
        this->opts.push_back(opt_name);
    }

    void Dialog::SetTitleColor(const Color clr) {
        this->title_clr = clr;
        this->LoadTitle();
    }
    
    void Dialog::SetTitle(const std::string &new_title) {
        this->title = new_title;
        this->LoadTitle();
    }

    void Dialog::SetContentColor(const Color clr) {
        this->cnt_clr = clr;
        this->LoadContent();
    }

    void Dialog::SetContent(const std::string &new_content) {
        this->cnt = new_content;
        this->LoadContent();
    }

    void Dialog::SetIcon(sdl2::TextureHandle::Ref tex) {
        this->DisposeIcon();
        this->icon_tex = tex;
    }

    i32 Dialog::Show(Application *app_ref) {
        if(this->HasCancelOption()) {
            this->AddOption(this->cancel_opt);
        }

        std::vector<sdl2::Texture> opts_texs;
        for(const auto &opt: this->opts) {
            opts_texs.push_back(render::RenderText(this->opt_font_name, opt, this->opt_clr));
        }

        if(opts_texs.empty()) {
            return 0;
        }

        auto opts_width = (this->space_between_options * (opts_texs.size() - 1)) + 2 * this->opts_base_h_margin;
        u32 row_opt_width = this->opts_base_h_margin;
        u32 opt_row_count = 1;
        for(const auto &opt_tex: opts_texs) {
            const auto opt_width = render::GetTextureWidth(opt_tex) + 2 * this->opt_h_margin;
            opts_width += opt_width;

            row_opt_width += opt_width + this->space_between_options;
            if((row_opt_width + this->opts_base_h_margin) >= render::ScreenWidth) {
                opt_row_count++;
                // Move this option to the next row
                row_opt_width = this->opts_base_h_margin + opt_width + this->space_between_options;
            }
        }

        auto dialog_width = opts_width;

        const auto cnt_width = render::GetTextureWidth(this->cnt_tex) + this->cnt_extra_width;
        if(cnt_width > dialog_width) {
            dialog_width = cnt_width;
        }

        const auto title_width = render::GetTextureWidth(this->title_tex) + this->title_extra_width;
        if(title_width > dialog_width) {
            dialog_width = title_width;
        }
        const auto title_cnt_height = this->title_top_margin + render::GetTextureHeight(this->title_tex) + render::GetTextureHeight(this->cnt_tex) + this->space_between_cnt_and_options;
        auto opt_base_y = title_cnt_height;
    
        if(this->HasIcon()) {
            const auto icon_height = render::GetTextureHeight(this->icon_tex->Get()) + 2 * this->icon_margin;
            if(icon_height > opt_base_y) {
                opt_base_y = icon_height;
            }

            const auto icon_width = render::GetTextureWidth(this->icon_tex->Get()) + 2 * this->icon_margin;

            const auto icon_title_width = title_width + icon_width;
            if(icon_title_width > dialog_width) {
                dialog_width = icon_title_width;
            }

            const auto icon_cnt_width = cnt_width + icon_width;
            if(icon_cnt_width > dialog_width) {
                dialog_width = icon_cnt_width;
            }

            const auto icon_opts_width = opts_width + icon_width;
            if(icon_opts_width > dialog_width) {
                dialog_width = icon_opts_width;
            }
        }
        
        if(dialog_width > render::ScreenWidth) {
            dialog_width = render::ScreenWidth;
        }

        auto dialog_height = opt_base_y + opt_row_count * this->opt_height + (opt_row_count - 1) * this->space_between_option_rows + this->opt_bottom_margin;
        if(dialog_height > render::ScreenHeight) {
            dialog_height = render::ScreenHeight;
        }

        const auto dialog_x = (render::ScreenWidth - dialog_width) / 2;
        const auto dialog_y = (render::ScreenHeight - dialog_height) / 2;
        opt_base_y += dialog_y;

        auto finish = false;
        auto is_finishing = false;
        i32 initial_fade_alpha = 0;
        SigmoidIncrementer<i32> initial_fade_alpha_incr;
        initial_fade_alpha_incr.StartFromZero(this->fade_alpha_incr_steps, 0xFF);
        const auto base_opt_base_y = opt_base_y;
        while(true) {
            opt_base_y = base_opt_base_y;
            const auto ok = app_ref->CallForRenderWithRenderOver([&](render::Renderer::Ref &drawer) -> bool {
                const auto keys_down = app_ref->GetButtonsDown();
                const auto tch_state = app_ref->GetTouchState();
                const TouchPoint tch_pos = {
                    (u32)((double)tch_state.touches[0].x * render::ScreenFactor),
                    (u32)((double)tch_state.touches[0].y * render::ScreenFactor)
                };
                if(keys_down & HidNpadButton_AnyLeft) {
                    if(this->selected_opt_idx > 0) {
                        this->prev_selected_opt_idx = this->selected_opt_idx;
                        this->selected_opt_idx--;

                        this->selected_opt_over_alpha = 0;
                        this->selected_opt_over_alpha_incr.StartFromZero(this->over_alpha_incr_steps, 0xFF);
                        this->prev_selected_opt_over_alpha = 0xFF;
                        this->prev_selected_opt_over_alpha_incr.StartToZero(this->over_alpha_incr_steps, 0xFF);
                    }
                }
                else if(keys_down & HidNpadButton_AnyRight) {
                    if(this->selected_opt_idx < (opts_texs.size() - 1)) {
                        this->prev_selected_opt_idx = this->selected_opt_idx;
                        this->selected_opt_idx++;

                        this->selected_opt_over_alpha = 0;
                        this->selected_opt_over_alpha_incr.StartFromZero(this->over_alpha_incr_steps, 0xFF);
                        this->prev_selected_opt_over_alpha = 0xFF;
                        this->prev_selected_opt_over_alpha_incr.StartToZero(this->over_alpha_incr_steps, 0xFF);
                    }
                }
                else if(keys_down & HidNpadButton_A) {
                    this->user_cancelled = false;
                    finish = true;
                }
                else if(keys_down & HidNpadButton_B) {
                    if(this->HasCancelOption()) {
                        this->selected_opt_idx = this->opts.size() - 1;
                        this->selected_opt_over_alpha = 0xFF;
                        this->prev_selected_opt_over_alpha = 0;
                    }
                    this->user_cancelled = true;
                    finish = true;
                }
                if(tch_state.count > 0) {
                    auto cur_opt_x = dialog_x + this->opts_base_h_margin;
                    for(u32 i = 0; i < this->opts.size(); i++) {
                        auto &opt_tex = opts_texs.at(i);
                        const auto opt_name_x = cur_opt_x + this->opt_h_margin;
                        const auto opt_name_width = render::GetTextureWidth(opt_tex);
                        const auto opt_width = opt_name_width + 2 * this->opt_h_margin;

                        if(tch_pos.HitsRegion(cur_opt_x, opt_base_y, opt_width, this->opt_height)) {
                            this->selected_opt_idx = i;
                            this->user_cancelled = false;
                            finish = true;
                            break;
                        }

                        cur_opt_x += opt_width + this->space_between_options;

                        if((opt_name_x + opt_width) > pu::ui::render::ScreenWidth) {
                            cur_opt_x = dialog_x + this->opts_base_h_margin;
                            opt_base_y += this->opt_height + this->space_between_option_rows;
                        }
                    }
                }

                opt_base_y = base_opt_base_y;
                
                const auto dialog_clr = MakeDialogColor(static_cast<u8>(initial_fade_alpha));
                auto screen_fade_alpha = initial_fade_alpha;
                if(screen_fade_alpha < 0) {
                    screen_fade_alpha = 0;
                }
                if(screen_fade_alpha > this->max_screen_fade_alpha) {
                    screen_fade_alpha = this->max_screen_fade_alpha;
                }
                const Color screen_fade_clr = { 0, 0, 0, static_cast<u8>(screen_fade_alpha) };
                drawer->RenderRectangleFill(screen_fade_clr, 0, 0, render::ScreenWidth, render::ScreenHeight);
                
                drawer->RenderRoundedRectangleFill(dialog_clr, dialog_x, dialog_y, dialog_width, dialog_height, this->dialog_border_radius);
                
                render::SetAlphaValue(this->title_tex, initial_fade_alpha);
                render::SetAlphaValue(this->cnt_tex, initial_fade_alpha);
                drawer->RenderTexture(this->title_tex, dialog_x + this->title_x, dialog_y + this->title_y);
                drawer->RenderTexture(this->cnt_tex, dialog_x + this->cnt_x, dialog_y + this->cnt_y);
                
                if(this->HasIcon()) {
                    const auto icon_width = render::GetTextureWidth(this->icon_tex->Get());
                    const auto icon_x = dialog_x + (dialog_width - (icon_width + 2 * this->icon_margin));
                    const auto icon_y = dialog_y + this->icon_margin;
                    drawer->RenderTexture(this->icon_tex->Get(), icon_x, icon_y, render::TextureRenderOptions(static_cast<u8>(initial_fade_alpha), {}, {}, {}, {}, {}));
                }

                auto cur_opt_x = dialog_x + this->opts_base_h_margin;
                for(u32 i = 0; i < opts_texs.size(); i++) {
                    auto &opt_tex = opts_texs.at(i);
                    const auto opt_name_width = render::GetTextureWidth(opt_tex);
                    const auto opt_name_height = render::GetTextureHeight(opt_tex);
                    const auto opt_width = opt_name_width + 2 * this->opt_h_margin;
                    if((cur_opt_x + opt_width) >= pu::ui::render::ScreenWidth) {
                        cur_opt_x = dialog_x + this->opts_base_h_margin;
                        opt_base_y += this->opt_height + this->space_between_option_rows;
                    }

                    const auto opt_name_x = cur_opt_x + this->opt_h_margin;
                    const auto opt_name_y = opt_base_y + ((this->opt_height - opt_name_height) / 2);

                    if(this->selected_opt_idx == i) {
                        this->selected_opt_over_alpha_incr.Increment(this->selected_opt_over_alpha);

                        auto over_clr = MakeOverColor(static_cast<u8>(initial_fade_alpha));
                        if(this->selected_opt_over_alpha < 0xFF) {
                            over_clr = MakeOverColor(static_cast<u8>(this->selected_opt_over_alpha));
                        }
                        drawer->RenderRoundedRectangleFill(over_clr, cur_opt_x, opt_base_y, opt_width, this->opt_height, this->opt_border_radius);
                    }
                    else if(this->prev_selected_opt_idx == static_cast<i32>(i)) {
                        this->prev_selected_opt_over_alpha_incr.Increment(this->prev_selected_opt_over_alpha);

                        if(this->prev_selected_opt_over_alpha > 0) {
                            const auto over_clr = MakeOverColor(static_cast<u8>(this->prev_selected_opt_over_alpha));
                            drawer->RenderRoundedRectangleFill(over_clr, cur_opt_x, opt_base_y, opt_width, this->opt_height, this->opt_border_radius);
                        }
                    }

                    render::SetAlphaValue(opt_tex, static_cast<u8>(initial_fade_alpha));
                    drawer->RenderTexture(opt_tex, opt_name_x, opt_name_y);

                    cur_opt_x += opt_width + this->space_between_options;
                }

                if(finish && !is_finishing) {
                    finish = false;

                    is_finishing = true;
                    initial_fade_alpha_incr.StartToZero(this->fade_alpha_incr_steps, 0xFF);
                }

                if(is_finishing) {
                    if(initial_fade_alpha_incr.Increment(initial_fade_alpha)) {
                        return false;
                    }
                }
                else {
                    initial_fade_alpha_incr.Increment(initial_fade_alpha);
                }
                return true;
            });

            if(!ok) {
                app_ref->CallForRenderWithRenderOver([](render::Renderer::Ref&) -> bool {
                    return false;
                });
                break;
            }
        }

        for(auto &opt_tex: opts_texs) {
            render::DeleteTexture(opt_tex);
        }

        return this->selected_opt_idx;
    }

}
