
/*

    Plutonium library

    @file Button.hpp
    @brief A Button is an Element for option selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <functional>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    class Button : public Element {
        public:
            using OnClickCallback = std::function<void()>;

            static constexpr u8 DefaultDarkerColorFactor = 70;

            static constexpr u8 DefaultHoverAlphaIncrementSteps = 48;

            static constexpr DefaultFontSize DefaultContentFontSize = DefaultFontSize::MediumLarge;

        private:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            std::string fnt_name;
            Color bg_clr;
            Color cnt_clr;
            std::string cnt;
            sdl2::Texture cnt_tex;
            OnClickCallback on_click_cb;
            bool hover;
            i32 hover_alpha;
            SigmoidIncrementer<i32> hover_alpha_incr;
            u8 darker_color_factor;
            u8 hover_alpha_incr_steps;

            inline Color MakeHoverBackgroundColor(const i32 alpha) {
                i32 base_r = this->bg_clr.r - this->darker_color_factor;
                if(base_r < 0) {
                    base_r = 0;
                }
                i32 base_g = this->bg_clr.g - this->darker_color_factor;
                if(base_g < 0) {
                    base_g = 0;
                }
                i32 base_b = this->bg_clr.b - this->darker_color_factor;
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
            Button(const i32 x, const i32 y, const i32 width, const i32 height, const std::string &content, const Color content_clr, const Color bg_clr);
            PU_SMART_CTOR(Button)
            ~Button();

            inline i32 GetX() override {
                return this->x;
            }

            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            inline void SetY(const i32 y) {
                this->y = y;
            }

            inline i32 GetWidth() override {
                return this->w;
            }

            inline void SetWidth(const i32 width) {
                this->w = width;
            }

            inline i32 GetHeight() override {
                return this->h;
            }

            inline void SetHeight(const i32 height) {
                this->h = height;
            }

            inline std::string GetContent() {
                return this->cnt;
            }

            void SetContent(const std::string &content);

            PU_CLASS_POD_GET(ContentColor, cnt_clr, Color)

            void SetContentColor(const Color content_clr);

            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)

            void SetContentFont(const std::string &font_name);
            
            inline void SetOnClick(OnClickCallback on_click_cb) {
                this->on_click_cb = on_click_cb;
            }
            
            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };

}
