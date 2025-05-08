/**
 * Plutonium library
 * @file elm_TextBlock.hpp
 * @brief Contains an element for text rendering.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Text.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for text rendering.
     */
    class TextBlock : public Element {
        public:
            // Self-explanatory constants

            static constexpr s32 DefaultClampSpeedSteps = 3;
            static constexpr s32 DefaultClampStaticDelaySteps = 20;
            static constexpr s32 NoClamp = -1;

        private:
            s32 x;
            s32 y;
            Text::Ref text;
            s32 clamp_w;
            s32 clamp_speed;
            s32 clamp_delay;
            s32 clamp_cur_x;
            s32 clamp_cur_delay;
        
        public:
            /**
             * @brief Creates a new instance of a TextBlock element.
             * @param x X position of the TextBlock.
             * @param y Y position of the TextBlock.
             * @param text Text to render.
             */
            TextBlock(const s32 x, const s32 y, Text::Ref text) : Element(), x(x), y(y), text(text), clamp_w(NoClamp), clamp_speed(DefaultClampSpeedSteps), clamp_delay(DefaultClampStaticDelaySteps), clamp_cur_x(0), clamp_cur_delay(0) {}
            PU_SMART_CTOR(TextBlock)

            inline bool SupportsFocus() override {
                return false;
            }

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the TextBlock.
             * @param x New X position.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the TextBlock.
             * @param y New Y position.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            s32 GetWidth() override;
            s32 GetHeight() override;

            PU_CLASS_POD_GETSET(Text, text, Text::Ref)
            PU_CLASS_POD_GETSET(ClampWidth, clamp_w, s32)
            PU_CLASS_POD_GETSET(ClampSpeed, clamp_speed, s32)
            PU_CLASS_POD_GETSET(ClampDelay, clamp_delay, s32)

            /**
             * @brief Resets the clamping of the TextBlock.
             */
            inline void ResetClamp() {
                this->clamp_cur_x = 0;
                this->clamp_cur_delay = 0;
            }

            void OnRender(render::Renderer::Ref &drawer) override;

            bool OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {
                return false;
            }
    };

}
