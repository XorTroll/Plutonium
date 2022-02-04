#include <pu/ui/ui_Dialog.hpp>
#include <pu/ui/ui_Application.hpp>

namespace pu::ui {

    Dialog::Dialog(const std::string &title, const std::string &content) {
        this->title_font_name = GetDefaultFont(DefaultFontSize::Large);
        this->cnt_font_name = GetDefaultFont(DefaultFontSize::Medium);
        this->opt_font_name = GetDefaultFont(DefaultFontSize::Small);
        this->title = title;
        this->cnt = content;
        this->title_tex = render::RenderText(this->title_font_name, title, DefaultTitleColor);
        this->cnt_tex = render::RenderText(this->cnt_font_name, content, DefaultContentColor);
        this->icon_tex = nullptr;
        this->selected_opt_idx = 0;
        this->prev_selected_opt_idx = 0;
        this->selected_opt_over_alpha = 0xFF;
        this->prev_selected_opt_over_alpha = 0;
        this->user_cancelled = false;
    }

    Dialog::~Dialog() {
        render::DeleteTexture(this->title_tex);
        render::DeleteTexture(this->cnt_tex);
        render::DeleteTexture(this->icon_tex);
        for(auto &opt_tex: this->opt_texs) {
            render::DeleteTexture(opt_tex);
        }
    }

    void Dialog::AddOption(const std::string &opt_name)  {
        this->opts.push_back(opt_name);
        this->opt_texs.push_back(render::RenderText(this->opt_font_name, opt_name, DefaultOptionColor));
    }

    void Dialog::SetIcon(const std::string &icon_path) {
        render::DeleteTexture(this->icon_tex);
        this->icon_tex = render::LoadImage(icon_path);
    }

    i32 Dialog::Show(Application *app_ref) {
        if(this->HasCancelOption()) {
            this->AddOption(this->cancel_opt);
        }

        if(this->opt_texs.empty()) {
            return 0;
        }

        auto opts_width = (SpaceBetweenOptions * (this->opt_texs.size() - 1)) + 2 * OptionsBaseHorizontalMargin;
        for(const auto &opt_tex : this->opt_texs) {
            const auto opt_width = render::GetTextureWidth(opt_tex) + 2 * OptionHorizontalMargin;
            opts_width += opt_width;
        }
        auto dialog_width = opts_width;

        const auto cnt_width = render::GetTextureWidth(this->cnt_tex) + ContentExtraWidth;
        if(cnt_width > dialog_width) {
            dialog_width = cnt_width;
        }

        const auto title_width = render::GetTextureWidth(this->title_tex) + TitleExtraWidth;
        if(title_width > dialog_width) {
            dialog_width = title_width;
        }
        const auto title_cnt_height = TitleTopMargin + render::GetTextureHeight(this->title_tex) + render::GetTextureHeight(this->cnt_tex) + SpaceBetweenContentAndOptions;
        auto opt_base_y = title_cnt_height;
    
        if(this->HasIcon()) {
            const auto icon_height = render::GetTextureHeight(this->icon_tex) + 2 * IconMargin;
            if(icon_height > opt_base_y) {
                opt_base_y = icon_height;
            }

            const auto icon_width = render::GetTextureWidth(this->icon_tex) + 2 * IconMargin;

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

        auto dialog_height = opt_base_y + OptionHeight + OptionBottomMargin;
        if(dialog_height > render::ScreenHeight) {
            dialog_height = render::ScreenHeight;
        }

        const auto dialog_x = (render::ScreenWidth - dialog_width) / 2;
        const auto dialog_y = (render::ScreenHeight - dialog_height) / 2;
        opt_base_y += dialog_y;

        auto is_finishing = false;
        i32 initial_fade_alpha = 0;
        while(true) {
            const auto ok = app_ref->CallForRenderWithRenderOver([&](render::Renderer::Ref &drawer) -> bool {
                const auto keys_down = app_ref->GetButtonsDown();
                const auto tch_state = app_ref->GetTouchState();
                const TouchPoint tch_pos = { tch_state.touches[0].x, tch_state.touches[0].y };
                if(keys_down & HidNpadButton_AnyLeft) {
                    if(this->selected_opt_idx > 0) {
                        this->prev_selected_opt_idx = this->selected_opt_idx;
                        this->selected_opt_idx--;

                        this->selected_opt_over_alpha = 0;
                        this->prev_selected_opt_over_alpha = 0xFF;
                    }
                }
                else if(keys_down & HidNpadButton_AnyRight) {
                    if(this->selected_opt_idx < (this->opt_texs.size() - 1)) {
                        this->prev_selected_opt_idx = this->selected_opt_idx;
                        this->selected_opt_idx++;

                        this->selected_opt_over_alpha = 0;
                        this->prev_selected_opt_over_alpha = 0xFF;
                    }
                }
                else if(keys_down & HidNpadButton_A) {
                    this->user_cancelled = false;
                    is_finishing = true;
                }
                else if(keys_down & HidNpadButton_B) {
                    this->user_cancelled = true;
                    is_finishing = true;
                }
                if(tch_state.count > 0) {
                    auto cur_opt_x = dialog_x + OptionsBaseHorizontalMargin;
                    for(u32 i = 0; i < this->opts.size(); i++) {
                        auto &opt_tex = this->opt_texs.at(i);
                        const auto opt_name_width = render::GetTextureWidth(opt_tex);
                        const auto opt_width = opt_name_width + 2 * OptionHorizontalMargin;

                        if(tch_pos.HitsRegion(cur_opt_x, opt_base_y, opt_width, OptionHeight)) {
                            this->selected_opt_idx = i;
                            this->user_cancelled = false;
                            is_finishing = true;
                            break;
                        }

                        cur_opt_x += opt_width + SpaceBetweenOptions;
                    }
                }
                
                const auto dialog_clr = MakeDialogColor(static_cast<u8>(initial_fade_alpha));
                auto screen_fade_alpha = initial_fade_alpha;
                if(screen_fade_alpha < 0) {
                    screen_fade_alpha = 0;
                }
                if(screen_fade_alpha > MaxScreenFadeAlpha) {
                    screen_fade_alpha = MaxScreenFadeAlpha;
                }
                const Color screen_fade_clr = { 0, 0, 0, static_cast<u8>(screen_fade_alpha) };
                drawer->RenderRectangleFill(screen_fade_clr, 0, 0, render::ScreenWidth, render::ScreenHeight);
                
                drawer->RenderRoundedRectangleFill(dialog_clr, dialog_x, dialog_y, dialog_width, dialog_height, DialogBorderRadius);
                
                render::SetAlphaValue(this->title_tex, initial_fade_alpha);
                render::SetAlphaValue(this->cnt_tex, initial_fade_alpha);
                drawer->RenderTexture(this->title_tex, dialog_x + TitleX, dialog_y + TitleY);
                drawer->RenderTexture(this->cnt_tex, dialog_x + ContentX, dialog_y + ContentY);
                
                if(this->HasIcon()) {
                    const auto icon_width = render::GetTextureWidth(this->icon_tex);
                    const auto icon_x = dialog_x + (dialog_width - (icon_width + 2 * IconMargin));
                    const auto icon_y = dialog_y + IconMargin;
                    drawer->RenderTexture(this->icon_tex, icon_x, icon_y, render::TextureRenderOptions::WithCustomAlpha(static_cast<u8>(initial_fade_alpha)));
                }

                auto cur_opt_x = dialog_x + OptionsBaseHorizontalMargin;
                for(u32 i = 0; i < this->opt_texs.size(); i++) {
                    auto &opt_tex = this->opt_texs.at(i);
                    const auto opt_name_width = render::GetTextureWidth(opt_tex);
                    const auto opt_name_height = render::GetTextureHeight(opt_tex);
                    const auto opt_width = opt_name_width + 2 * OptionHorizontalMargin;
                    const auto opt_name_x = cur_opt_x + OptionHorizontalMargin;
                    const auto opt_name_y = opt_base_y + ((OptionHeight - opt_name_height) / 2);
                    if(this->selected_opt_idx == i) {
                        if(this->selected_opt_over_alpha < 0xFF) {
                            const auto over_clr = MakeOverColor(static_cast<u8>(this->selected_opt_over_alpha));
                            drawer->RenderRoundedRectangleFill(over_clr, cur_opt_x, opt_base_y, opt_width, OptionHeight, OptionBorderRadius);
                            this->selected_opt_over_alpha += OverAlphaIncrement;
                        }
                        else {
                            this->selected_opt_over_alpha = 0xFF;
                            const auto over_clr = MakeOverColor(static_cast<u8>(initial_fade_alpha));
                            drawer->RenderRoundedRectangleFill(over_clr, cur_opt_x, opt_base_y, opt_width, OptionHeight, OptionBorderRadius);
                        }
                    }
                    else if(this->prev_selected_opt_idx == static_cast<i32>(i)) {
                        if(this->prev_selected_opt_over_alpha > 0) {
                            const auto over_clr = MakeOverColor(static_cast<u8>(this->prev_selected_opt_over_alpha));
                            drawer->RenderRoundedRectangleFill(over_clr, cur_opt_x, opt_base_y, opt_width, OptionHeight, OptionBorderRadius);
                            this->prev_selected_opt_over_alpha -= OverAlphaIncrement;
                        }
                        else {
                            this->prev_selected_opt_over_alpha = 0;
                        }
                    }

                    render::SetAlphaValue(opt_tex, static_cast<u8>(initial_fade_alpha));
                    drawer->RenderTexture(opt_tex, opt_name_x, opt_name_y);
                    cur_opt_x += opt_width + SpaceBetweenOptions;
                }

                if(is_finishing) {
                    if(initial_fade_alpha == 0) {
                        return false;
                    }
                    
                    if(initial_fade_alpha > 0) {
                        initial_fade_alpha -= FadeAlphaIncrement;
                    }
                    if(initial_fade_alpha < 0) {
                        initial_fade_alpha = 0;
                    }
                }
                else {
                    if(initial_fade_alpha < 0xFF) {
                        initial_fade_alpha += FadeAlphaIncrement;
                    }
                    if(initial_fade_alpha > 0xFF) {
                        initial_fade_alpha = 0xFF;
                    }
                }
                return true;
            });

            if(!ok) {
                app_ref->CallForRenderWithRenderOver([](render::Renderer::Ref&) -> bool { return false; });
                break;
            }
        }

        return this->selected_opt_idx;
    }

}