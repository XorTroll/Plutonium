/**
 * Plutonium library
 * @file elm_TextBlock.hpp
 * @brief Contains an element for text rendering.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for text rendering.
     */
    class TextBlock : public Element {
        public:
            // Self-explanatory constants

            static constexpr Color DefaultColor = { 0, 0, 0, 0xFF };
            static constexpr i32 DefaultClampSpeedSteps = 3;
            static constexpr i32 DefaultClampStaticDelaySteps = 20;
            static constexpr i32 NoClamp = -1;

        private:
            i32 x;
            i32 y;
            Color clr;
            std::string text;
            sdl2::Texture text_tex;
            std::string fnt_name;
            i32 clamp_w;
            i32 clamp_speed;
            i32 clamp_delay;
            i32 clamp_cur_x;
            i32 clamp_cur_delay;
        
        public:
            /**
             * @brief Creates a new instance of a TextBlock element.
             * @param x X position of the TextBlock.
             * @param y Y position of the TextBlock.
             * @param text Text to render.
             */
            TextBlock(const i32 x, const i32 y, const std::string &text);
            PU_SMART_CTOR(TextBlock)
            ~TextBlock();

            inline i32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the TextBlock.
             * @param x New X position.
             */
            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the TextBlock.
             * @param y New Y position.
             */
            inline void SetY(const i32 y) {
                this->y = y;
            }

            i32 GetWidth() override;
            i32 GetHeight() override;

            /**
             * @brief Gets the text of the TextBlock.
             * @return Text of the TextBlock.
             */
            inline std::string GetText() {
                return this->text;
            }

            /**
             * @brief Sets the text of the TextBlock.
             * @param text New text.
             * @note This will re-render the text.
             */
            void SetText(const std::string &text);

            /**
             * @brief Gets the font name of the TextBlock.
             * @return Font name of the TextBlock.
             * @note This will re-render the text.
             */
            void SetFont(const std::string &font_name);

            PU_CLASS_POD_GET(Color, clr, Color)
            
            /**
             * @brief Sets the color of the TextBlock.
             * @param clr New color.
             * @note This will re-render the text.
             */
            void SetColor(const Color clr);

            PU_CLASS_POD_GETSET(ClampWidth, clamp_w, i32)
            PU_CLASS_POD_GETSET(ClampSpeed, clamp_speed, i32)
            PU_CLASS_POD_GETSET(ClampDelay, clamp_delay, i32)

            /**
             * @brief Resets the clamping of the TextBlock.
             */
            inline void ResetClamp() {
                this->clamp_cur_x = 0;
                this->clamp_cur_delay = 0;
            }

            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}
