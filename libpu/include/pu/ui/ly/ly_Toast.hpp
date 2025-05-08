/**
 * Plutonium library
 * @file ly_Toast.hpp
 * @brief Toast class to show simple messages on the screen.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Layer.hpp>
#include <pu/ui/ui_SigmoidIncrementer.hpp>
#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::ly {

    /**
     * @brief Layer that represents a simple message/notification that appears on the screen for some duration.
     */
    class Toast final : public Layer {
        public:
            // Self-explanatory constants

            static constexpr s32 DefaultY = 750;
            static constexpr s32 DefaultHeight = 50;
            static constexpr s32 DefaultHorizontalMargin = 50;
            static constexpr u8 DefaulBaseAlpha = 200;
            static constexpr s32 DefaultRadius = 18;
            static constexpr u8 DefaultFadeAlphaIncrementSteps = 25;

        private:
            s32 x;
            s32 y;
            s32 text_x;
            s32 text_y;
            s32 width;
            s32 height;
            s32 fade_alpha;
            s32 fade_alpha_incr_steps;
            SigmoidIncrementer<s32> fade_alpha_incr;
            Color bg_clr;
            s32 radius;
            bool is_ending;
            Text::Ref text;
            s32 h_margin;
            u8 base_alpha;
            u32 duration_ms;
            std::chrono::steady_clock::time_point start_time;

        public:
            /**
             * @brief Creates a new instance of a Toast.
             * @param text Text to use for the Toast.
             * @param bg_clr Background color of the Toast.
             * @param duration_ms Duration of the Toast (in milliseconds).
             */
            Toast(Text::Ref text, const Color bg_clr, const u32 duration_ms) : x(0), y(DefaultY), text_x(0), text_y(0), height(DefaultHeight), fade_alpha(0), fade_alpha_incr_steps(DefaultFadeAlphaIncrementSteps), fade_alpha_incr(), bg_clr(bg_clr), radius(DefaultRadius), is_ending(false), text(text), h_margin(DefaultHorizontalMargin), base_alpha(DefaulBaseAlpha), duration_ms(duration_ms) {}
            PU_SMART_CTOR(Toast)

            inline bool CapturesInput() override {
                return false;
            }

            /**
             * @brief Checks whether the overlay has a radius for its background rectangle.
             * @return Whether the overlay has a rounded rectangle.
             */
            inline bool HasRadius() {
                return this->radius > 0;
            }

            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)
            PU_CLASS_POD_GETSET(FadeAlphaIncrementSteps, fade_alpha_incr_steps, s32)
            PU_CLASS_POD_GETSET(HorizontalMargin, h_margin, s32)
            PU_CLASS_POD_GETSET(BaseAlpha, base_alpha, u8)
            PU_CLASS_POD_GETSET(Radius, radius, s32)
            PU_CLASS_POD_GETSET(Y, y, s32)
            PU_CLASS_POD_GETSET(Height, height, s32)
            PU_CLASS_POD_GETSET(Duration, duration_ms, u32)
            PU_CLASS_POD_GETSET(Text, text, Text::Ref)
            
            void OnStart() override;
            void OnStop() override {}
            void OnRender(render::Renderer::Ref &drawer) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}
