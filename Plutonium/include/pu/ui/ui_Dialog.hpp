
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

            static constexpr u32 DialogExtraBaseWidth = 250;
            static constexpr u32 DialogBorderRadius = 35;

            static constexpr u32 SpaceBetweenOptions = 20;

            static constexpr u32 TitleExtraWidth = 90;
            static constexpr u32 ContentExtraWidth = 90;
            static constexpr u32 SpaceBetweenContentAndOptions = 140;
            static constexpr u32 TitleTopMargin = 20; 

            static constexpr u32 TitleX = 45;
            static constexpr u32 TitleY = 55;
            static constexpr u32 ContentX = 45;
            static constexpr u32 ContentY = 140;

            static constexpr u32 IconExtraHeight = 25;

            static constexpr u32 OptionsBaseHorizontalMargin = 45;
            static constexpr u32 OptionHeight = 60;
            static constexpr u32 OptionHorizontalMargin = 30;
            static constexpr u32 OptionBorderRadius = OptionHeight / 3;
            static constexpr u32 OptionBottomMargin = 25;
            
            static constexpr u8 MaxScreenFadeAlpha = 125;

            static constexpr u32 IconMargin = 30;

            static inline constexpr Color MakeDialogColor(const u8 alpha) {
                return { 0xE1, 0xE1, 0xE1, alpha };
            }
            
            static inline constexpr Color MakeOverColor(const u8 alpha) {
                return { 0xB4, 0xB4, 0xC8, alpha };
            }

            static constexpr u8 OverAlphaIncrement = 48;
            static constexpr u8 FadeAlphaIncrement = 25;

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
            i32 prev_selected_opt_idx;
            i32 prev_selected_opt_over_alpha;
            bool user_cancelled;
            sdl2::Texture icon_tex;

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