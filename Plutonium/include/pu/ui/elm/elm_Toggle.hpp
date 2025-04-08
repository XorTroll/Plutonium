/**
 * Plutonium library
 * @file elm_Toggle.hpp
 * @brief Contains an element for toggling between two states.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for toggling between two states.
     */
    class Toggle : public Element {
        public:
            // Self-explanatory constants

            static constexpr u32 DefaultContentHorizontalMargin = 30;
            static constexpr u32 DefaultContentVerticalMargin = 20;

            static constexpr DefaultFontSize DefaultContentFontSize = DefaultFontSize::MediumLarge;

            static constexpr u8 DefaultToggleAlphaIncrement = 48;

            static constexpr Color DefaultBackgroundColor = { 130, 130, 130, 255 };

        private:
            s32 x;
            s32 y;
            u64 key;
            bool checked;
            Color clr;
            std::string fnt_name;
            s32 toggle_alpha;
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
            /**
             * @brief Creates a new instance of a Toggle element.
             * @param x X position of the Toggle.
             * @param y Y position of the Toggle.
             * @param content Content of the Toggle.
             * @param toggle_key Key to toggle the state of the Toggle.
             * @param clr Color of the Toggle.
             */
            Toggle(const s32 x, const s32 y, const std::string &content, const u64 toggle_key, const Color clr);
            PU_SMART_CTOR(Toggle)
            ~Toggle();

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Toggle.
             * @param x New X position.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the Toggle.
             * @param y New Y position.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }
            
            s32 GetWidth() override;
            s32 GetHeight() override;

            /**
             * @brief Gets the content of the Toggle.
             * @return Content of the Toggle.
             */
            inline std::string GetContent() {
                return this->cnt;
            }

            /**
             * @brief Sets the content of the Toggle.
             * @param content New content.
             * @note This will re-render the content of the Toggle.
             */
            void SetContent(const std::string &content);

            /**
             * @brief Gets the font name of the Toggle.
             * @return Font name of the Toggle.
             * @note This will re-render the content of the Toggle.
             */
            void SetFont(const std::string &font_name);

            PU_CLASS_POD_GET(Color, clr, Color)
            
            /**
             * @brief Sets the color of the Toggle.
             * @param clr New color.
             * @note This will re-render the content of the Toggle.
             */
            void SetColor(const Color clr);

            PU_CLASS_POD_GETSET(Key, key, u64)

            PU_CLASS_POD_GET(Checked, checked, bool)

            void OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };

}
