/**
 * Plutonium library
 * @file ui_Dialog.hpp
 * @brief Dialog class header.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/render/render_Renderer.hpp>
#include <vector>

namespace pu::ui {

    class Application;

    /**
     * @brief Class that represents a dialog, which is a simple way to show a message and various options to the user and get a response.
     * @note A Dialog is rendered over the current Layout, in a similar (but different) way to Overlay.
     */
    class Dialog {
        public:
            // These are all self-explanatory
        
            static constexpr Color DefaultTitleColor = { 0xA, 0xA, 0xA, 0xFF };
            static constexpr Color DefaultContentColor = { 0x14, 0x14, 0x14, 0xFF };
            static constexpr Color DefaultOptionColor = { 0xA, 0xA, 0xA, 0xFF };

            static constexpr u32 DefaultDialogBorderRadius = 52;

            static constexpr u32 DefaultSpaceBetweenOptions = 30;
            static constexpr u32 DefaultSpaceBetweenOptionRows = 15;

            static constexpr u32 DefaultTitleExtraWidth = 135;
            static constexpr u32 DefaultContentExtraWidth = 135;
            static constexpr u32 DefaultSpaceBetweenContentAndOptions = 210;
            static constexpr u32 DefaultTitleTopMargin = 30;

            static constexpr u32 DefaultTitleX = 67;
            static constexpr u32 DefaultTitleY = 82;
            static constexpr u32 DefaultContentX = 67;
            static constexpr u32 DefaultContentY = 210;

            static constexpr u32 DefaultIconExtraHeight = 37;

            static constexpr u32 DefaultOptionsBaseHorizontalMargin = 67;
            static constexpr u32 DefaultOptionHeight = 90;
            static constexpr u32 DefaultOptionHorizontalMargin = 45;
            static constexpr u32 DefaultOptionBorderRadius = DefaultOptionHeight / 3;
            static constexpr u32 DefaultOptionBottomMargin = 37;
            
            static constexpr u8 DefaultMaxScreenFadeAlpha = 125;

            static constexpr u32 DefaultIconMargin = 45;

            static constexpr u8 DefaultOverAlphaIncrementSteps = 12;
            static constexpr u8 DefaultFadeAlphaIncrementSteps = 18;

            static constexpr Color DefaultDialogColor = { 0xE1, 0xE1, 0xE1, 0xFF };
            static constexpr Color DefaultOverColor = { 0xB4, 0xB4, 0xC8, 0xFF };

        private:
            std::string title_font_name;
            std::string cnt_font_name;
            std::string opt_font_name;
            std::string title;
            std::string cnt;
            sdl2::Texture title_tex;
            sdl2::Texture cnt_tex;
            std::vector<std::string> opts;
            std::string cancel_opt;
            u32 selected_opt_idx;
            s32 selected_opt_over_alpha;
            SigmoidIncrementer<s32> selected_opt_over_alpha_incr;
            s32 prev_selected_opt_idx;
            s32 prev_selected_opt_over_alpha;
            SigmoidIncrementer<s32> prev_selected_opt_over_alpha_incr;
            bool user_cancelled;
            sdl2::TextureHandle::Ref icon_tex;
            Color title_clr;
            Color cnt_clr;
            Color opt_clr;
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
            void DisposeIcon();

        public:
            /**
             * @brief Creates a new Dialog with the specified title and content.
             * @param title Title of the Dialog.
             * @param content Content of the Dialog.
             */
            Dialog(const std::string &title, const std::string &content);
            PU_SMART_CTOR(Dialog)
            ~Dialog();

            /**
             * @brief Adds an option to the Dialog.
             * @param opt_name Name of the option to add.
             */
            void AddOption(const std::string &opt_name);
            
            /**
             * @brief Sets the option that will cancel the Dialog.
             * @note If this option is selected, the Dialog will be cancelled.
             * @note This option will always be the last one.
             * @param opt_name Name of the option that will cancel the Dialog.
             */
            inline void SetCancelOption(const std::string &opt_name) {
                this->cancel_opt = opt_name;
            }

            /**
             * @brief Removes the cancel option from the Dialog.
             */
            inline void RemoveCancelOption() {
                this->SetCancelOption("");
            }
            
            /**
             * @brief Checks whether the Dialog has a cancel option.
             * @return Whether the Dialog has a cancel option.
             */
            inline bool HasCancelOption() {
                return !this->cancel_opt.empty();
            }

            PU_CLASS_POD_GET(TitleColor, title_clr, Color)

            /**
             * @brief Sets the color of the title.
             * @param clr New color of the title.
             */
            void SetTitleColor(const Color clr);

            /**
             * @brief Sets the title of the Dialog.
             * @param new_title New title of the Dialog.
             */
            void SetTitle(const std::string &new_title);

            PU_CLASS_POD_GET(ContentColor, cnt_clr, Color)

            /**
             * @brief Sets the color of the content.
             * @param clr New color of the content.
             */
            void SetContentColor(const Color clr);

            /**
             * @brief Sets the content of the Dialog.
             * @param new_content New content of the Dialog.
             */
            void SetContent(const std::string &new_content);

            PU_CLASS_POD_GETSET(OptionColor, opt_clr, Color)

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

            /**
             * @brief Sets the icon of the Dialog.
             * @param tex Texture of the icon.
             */
            void SetIcon(sdl2::TextureHandle::Ref tex);
            
            /**
             * @brief Checks whether the Dialog has an icon.
             * @return Whether the Dialog has an icon.
             */
            inline bool HasIcon() {
                return this->icon_tex != nullptr;
            }
            
            /**
             * @brief Shows the Dialog to the user.
             * @param app_ref Reference to the Application that will show the Dialog.
             * @note This is not really meant to be used manually. Application calls this internally. Check Application::ShowDialog or Application::CreateShowDialog.
             * @return Index of the selected option by the user.
             */
            s32 Show(Application *app_ref);
            
            /**
             * @brief Gets whether the user cancelled the Dialog.
             * @note If the Dialog has not been shown yet, this will always return false.
             * @return Whether the user cancelled the Dialog.
             */
            inline constexpr bool UserCancelled() {
                return this->user_cancelled;
            }
            
            /**
             * @brief Gets whether the Dialog has been shown and the user selected an option.
             * @note If the Dialog has not been shown yet, this will always return false.
             * @return Whether the Dialog has been shown and the user selected an option.
             */
            inline bool IsOk() {
                if(this->user_cancelled) {
                    return false;
                }

                if(this->HasCancelOption() && (this->selected_opt_idx == (this->opts.size() - 1))) {
                    return false;
                }

                return true;
            }
    };

}
