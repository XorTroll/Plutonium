
/*

    Plutonium library

    @file Toggle.hpp
    @brief A Toggle is an Element used to switch between two options by toggling the item.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    class Toggle : public Element {
        public:
            static constexpr u32 DefaultContentHorizontalMargin = 30;
            static constexpr u32 DefaultContentVerticalMargin = 20;

            static constexpr DefaultFontSize DefaultContentFontSize = DefaultFontSize::MediumLarge;

            static constexpr u8 DefaultToggleAlphaIncrement = 48;

            static constexpr Color DefaultBackgroundColor = { 130, 130, 130, 255 };

        private:
            i32 x;
            i32 y;
            u64 key;
            bool checked;
            Color clr;
            std::string fnt_name;
            i32 toggle_alpha;
            std::string cnt;
            sdl2::Texture cnt_tex;
            u32 cnt_h_margin;
            u32 cnt_v_margin;
            u8 toggle_alpha_incr;
            Color bg_clr;

            inline Color MakeBackgroundColor(const u8 alpha) {
                return this->bg_clr.WithAlpha(alpha);
            }

        public:
            Toggle(const i32 x, const i32 y, const std::string &content, const u64 toggle_key, const Color clr);
            PU_SMART_CTOR(Toggle)
            ~Toggle();

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
            
            i32 GetWidth() override;
            i32 GetHeight() override;

            inline std::string GetContent() {
                return this->cnt;
            }
            
            void SetContent(const std::string &content);
            void SetFont(const std::string &font_name);

            PU_CLASS_POD_GET(Color, clr, Color)
            
            void SetColor(const Color clr);

            PU_CLASS_POD_GETSET(Key, key, u64)

            PU_CLASS_POD_GET(Checked, checked, bool)

            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };

}
