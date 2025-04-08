/**
 * Plutonium library
 * @file elm_Button.hpp
 * @brief Represents a simple button that can be clicked and interacted with.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <functional>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    /**
     * @brief Represents a simple button that can be clicked and interacted with.
     */
    class Button : public Element {
        public:
            /**
             * @brief Callback that is called when the Button is clicked.
             */
            using OnClickCallback = std::function<void()>;

            // Self-explanatory constants

            static constexpr u8 DefaultDarkerColorFactor = 70;

            static constexpr u8 DefaultHoverAlphaIncrementSteps = 48;

            static constexpr DefaultFontSize DefaultContentFontSize = DefaultFontSize::MediumLarge;

        private:
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            std::string fnt_name;
            Color bg_clr;
            Color cnt_clr;
            std::string cnt;
            sdl2::Texture cnt_tex;
            OnClickCallback on_click_cb;
            bool hover;
            s32 hover_alpha;
            SigmoidIncrementer<s32> hover_alpha_incr;
            u8 darker_color_factor;
            u8 hover_alpha_incr_steps;

            inline Color MakeHoverBackgroundColor(const s32 alpha) {
                s32 base_r = this->bg_clr.r - this->darker_color_factor;
                if(base_r < 0) {
                    base_r = 0;
                }
                s32 base_g = this->bg_clr.g - this->darker_color_factor;
                if(base_g < 0) {
                    base_g = 0;
                }
                s32 base_b = this->bg_clr.b - this->darker_color_factor;
                if(base_b < 0) {
                    base_b = 0;
                }

                auto base_a = this->bg_clr.a;
                if(alpha >= 0) {
                    base_a = static_cast<u8>(alpha);
                }

                return { static_cast<u8>(base_r), static_cast<u8>(base_g), static_cast<u8>(base_b), base_a };
            }

        public:
            /**
             * @brief Creates a new instance of a Button.
             * @param x X position of the Button.
             * @param y Y position of the Button.
             * @param width Width of the Button.
             * @param height Height of the Button.
             * @param content Content of the Button.
             * @param content_clr Color of the content of the Button.
             * @param bg_clr Background color of the Button.
             */
            Button(const s32 x, const s32 y, const s32 width, const s32 height, const std::string &content, const Color content_clr, const Color bg_clr);
            PU_SMART_CTOR(Button)
            ~Button();

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Button.
             * @param x New X position to set.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the Button.
             * @param y New Y position to set.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            inline s32 GetWidth() override {
                return this->w;
            }

            /**
             * @brief Sets the width of the Button.
             * @param width New width to set.
             */
            inline void SetWidth(const s32 width) {
                this->w = width;
            }

            inline s32 GetHeight() override {
                return this->h;
            }

            /**
             * @brief Sets the height of the Button.
             * @param height New height to set.
             */
            inline void SetHeight(const s32 height) {
                this->h = height;
            }

            /**
             * @brief Gets the content of the Button.
             * @return Content of the Button.
             */
            inline std::string GetContent() {
                return this->cnt;
            }

            /**
             * @brief Sets the content of the Button.
             * @param content New content to set.
             */
            void SetContent(const std::string &content);

            PU_CLASS_POD_GET(ContentColor, cnt_clr, Color)

            /**
             * @brief Sets the color of the content of the Button.
             * @param content_clr New color to set.
             */
            void SetContentColor(const Color content_clr);

            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)

            /**
             * @brief Sets the background color of the Button.
             * @param bg_clr New background color to set.
             */
            void SetContentFont(const std::string &font_name);

            /**
             * @brief Sets the font of the content of the Button.
             * @param font_name New font to set.
             */
            inline void SetOnClick(OnClickCallback on_click_cb) {
                this->on_click_cb = on_click_cb;
            }
            
            void OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };

}
