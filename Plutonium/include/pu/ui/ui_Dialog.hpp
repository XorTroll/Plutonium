
/*

    Plutonium library

    @file ui_Dialog.hpp
    @brief A Dialog is an easy way to ask the user to choose between several options.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/render/render_Renderer.hpp>
#include <vector>

namespace pu::ui {

    class Application;

    class Dialog {
        public:
            static constexpr Color DefaultTitleColor = { 0xA, 0xA, 0xA, 0xFF };
            static constexpr Color DefaultContentColor = { 0x14, 0x14, 0x14, 0xFF };
            static constexpr Color DefaultOptionColor = { 0xA, 0xA, 0xA, 0xFF };

            static constexpr u32 DefaultDialogExtraBaseWidth = 250;
            static constexpr u32 DefaultDialogBorderRadius = 35;

            static constexpr u32 DefaultSpaceBetweenOptions = 20;
            static constexpr u32 DefaultSpaceBetweenOptionRows = 10;

            static constexpr u32 DefaultTitleExtraWidth = 90;
            static constexpr u32 DefaultContentExtraWidth = 90;
            static constexpr u32 DefaultSpaceBetweenContentAndOptions = 140;
            static constexpr u32 DefaultTitleTopMargin = 20; 

            static constexpr u32 DefaultTitleX = 45;
            static constexpr u32 DefaultTitleY = 55;
            static constexpr u32 DefaultContentX = 45;
            static constexpr u32 DefaultContentY = 140;

            static constexpr u32 DefaultIconExtraHeight = 25;

            static constexpr u32 DefaultOptionsBaseHorizontalMargin = 45;
            static constexpr u32 DefaultOptionHeight = 60;
            static constexpr u32 DefaultOptionHorizontalMargin = 30;
            static constexpr u32 DefaultOptionBorderRadius = DefaultOptionHeight / 3;
            static constexpr u32 DefaultOptionBottomMargin = 25;
            
            static constexpr u8 DefaultMaxScreenFadeAlpha = 125;

            static constexpr u32 DefaultIconMargin = 30;

            static constexpr u8 DefaultOverAlphaIncrementSteps = 12;
            static constexpr u8 DefaultFadeAlphaIncrementSteps = 18;

            static constexpr Color DefaultDialogColor = { 225, 225, 225, 255 };
            static constexpr Color DefaultOverColor = { 180, 180, 180, 255 };

        private:
            std::string title_font_name;
            std::string cnt_font_name;
            std::string opt_font_name;
            std::string title;
            std::string cnt;
            sdl2::Texture title_tex;
            sdl2::Texture cnt_tex;
            std::vector<std::string> opts;
            std::vector<sdl2::Texture> opt_texs;
            std::string cancel_opt;
            u32 selected_opt_idx;
            i32 selected_opt_over_alpha;
            SigmoidIncrementer<i32> selected_opt_over_alpha_incr;
            i32 prev_selected_opt_idx;
            i32 prev_selected_opt_over_alpha;
            SigmoidIncrementer<i32> prev_selected_opt_over_alpha_incr;
            bool user_cancelled;
            sdl2::Texture icon_tex;
            Color title_clr;
            Color cnt_clr;
            Color opt_clr;
            u32 dialog_extra_base_width;
            u32 dialog_border_radius;
            u32 space_between_options;
            u32 space_between_option_rows;
            u32 title_extra_width;
            u32 cnt_extra_width;
            u32 space_between_cnt_and_options;
            u32 title_top_margin;
            u32 title_x;
            u32 title_y;
            u32 cnt_x;
            u32 cnt_y;
            u32 icon_extra_height;
            u32 opts_base_h_margin;
            u32 opt_height;
            u32 opt_h_margin;
            u32 opt_border_radius;
            u32 opt_bottom_margin;
            u8 max_screen_fade_alpha;
            u32 icon_margin;
            Color dialog_clr;
            Color over_clr;
            u8 over_alpha_incr_steps;
            u8 fade_alpha_incr_steps;

            inline Color MakeDialogColor(const u8 alpha) {
                return this->dialog_clr.WithAlpha(alpha);
            }
            
            inline Color MakeOverColor(const u8 alpha) {
                return this->over_clr.WithAlpha(alpha);
            }

            void LoadTitle();
            void LoadContent();

        public:
            Dialog(const std::string &title, const std::string &content);
            PU_SMART_CTOR(Dialog)
            ~Dialog();

            void AddOption(const std::string &opt_name);
            
            inline void SetCancelOption(const std::string &opt_name) {
                this->cancel_opt = opt_name;
            }

            inline void RemoveCancelOption() {
                this->SetCancelOption("");
            }
            
            inline bool HasCancelOption() {
                return !this->cancel_opt.empty();
            }

            PU_CLASS_POD_GET(TitleColor, title_clr, Color)

            void SetTitleColor(const Color clr);

            void SetTitle(const std::string &new_title);

            PU_CLASS_POD_GET(ContentColor, cnt_clr, Color)

            void SetContentColor(const Color clr);

            void SetContent(const std::string &new_content);

            PU_CLASS_POD_GETSET(OptionColor, opt_clr, Color)

            PU_CLASS_POD_GETSET(DialogExtraBaseWidth, dialog_extra_base_width, u32)
            PU_CLASS_POD_GETSET(DialogBorderRadius, dialog_border_radius, u32)
            PU_CLASS_POD_GETSET(SpaceBetweenOptions, space_between_options, u32)
            PU_CLASS_POD_GETSET(SpaceBetweenOptionRows, space_between_option_rows, u32)
            PU_CLASS_POD_GETSET(TitleExtraWidth, title_extra_width, u32)
            PU_CLASS_POD_GETSET(ContentExtraWidth, cnt_extra_width, u32)
            PU_CLASS_POD_GETSET(SpaceBetweenContentAndOptions, space_between_cnt_and_options, u32)
            PU_CLASS_POD_GETSET(TitleTopMargin, title_top_margin, u32)
            PU_CLASS_POD_GETSET(TitleX, title_x, u32)
            PU_CLASS_POD_GETSET(TitleY, title_y, u32)
            PU_CLASS_POD_GETSET(ContentX, cnt_x, u32)
            PU_CLASS_POD_GETSET(ContentY, cnt_y, u32)
            PU_CLASS_POD_GETSET(IconExtraHeight, icon_extra_height, u32)
            PU_CLASS_POD_GETSET(OptionsBaseHorizontalMargin, opts_base_h_margin, u32)
            PU_CLASS_POD_GETSET(OptionHeight, opt_height, u32)
            PU_CLASS_POD_GETSET(OptionHorizontalMargin, opt_h_margin, u32)
            PU_CLASS_POD_GETSET(OptionBorderRadius, opt_border_radius, u32)
            PU_CLASS_POD_GETSET(OptionBottomMargin, opt_bottom_margin, u32)
            PU_CLASS_POD_GETSET(MaxScreenFadeAlpha, max_screen_fade_alpha, u8)
            PU_CLASS_POD_GETSET(IconMargin, icon_margin, u32)
            PU_CLASS_POD_GETSET(DialogColor, dialog_clr, Color)
            PU_CLASS_POD_GETSET(OverColor, over_clr, Color)
            PU_CLASS_POD_GETSET(OverAlphaIncrementSteps, over_alpha_incr_steps, u8)
            PU_CLASS_POD_GETSET(FadeAlphaIncrementSteps, fade_alpha_incr_steps, u8)

            void SetIcon(const std::string &icon_path);
            
            inline constexpr bool HasIcon() {
                return this->icon_tex != nullptr;
            }
            
            i32 Show(Application *app_ref);
            
            inline constexpr bool UserCancelled() {
                return this->user_cancelled;
            }
            
            inline bool IsOk() {
                if(this->user_cancelled) {
                    return false;
                }

                if(this->HasCancelOption() && (this->selected_opt_idx == (this->opt_texs.size() - 1))) {
                    return false;
                }

                return true;
            }
    };

}
