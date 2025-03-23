/**
 * Plutonium library
 * @file ui_Overlay.hpp
 * @brief Overlay class header.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Container.hpp>

namespace pu::ui {

    /**
     * @brief Class that represents an overlay, which is a container that is rendered over the current Layout.
     * @note The overlay consists on a base rectangle (or rounded rectangle) over which child classes can do custom rendering.
     */
    class Overlay : public Container {
        public:
            /**
             * @brief Default radius of the overlay rectangle.
             */
            static constexpr i32 DefaultRadius = 37;

            /**
             * @brief Default maximum alpha value for the overlay fade effect.
             */
            static constexpr u8 DefaultMaxFadeAlpha = 200;

            /**
             * @brief Default alpha variation (increment) for the overlay fade effect.
             */
            static constexpr u8 DefaultFadeAlphaVariation = 25;

        private:
            i32 fade_a;
            Color bg_clr;
            i32 rad;
            bool is_ending;
            u8 max_fade_alpha;
            u8 fade_alpha_variation;

        public:
            /**
             * @brief Creates a new Overlay with the specified position, size, and background color.
             * @param x X coordinate of the Overlay.
             * @param y Y coordinate of the Overlay.
             * @param width Width of the Overlay.
             * @param height Height of the Overlay.
             * @param bg_clr Background color of the Overlay.
             */
            Overlay(const i32 x, const i32 y, const i32 width, const i32 height, const Color bg_clr) : Container(x, y, width, height), fade_a(0), bg_clr(bg_clr), rad(DefaultRadius), is_ending(false), max_fade_alpha(DefaultMaxFadeAlpha), fade_alpha_variation(DefaultFadeAlphaVariation) {}
            PU_SMART_CTOR(Overlay)

            PU_CLASS_POD_GETSET(Radius, rad, i32)

            /**
             * @brief Checks whether the overlay has a radius for its background rectangle.
             * @return Whether the overlay has a rounded rectangle.
             */
            inline bool HasRadius() {
                return this->rad > 0;
            }

            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)
            PU_CLASS_POD_GETSET(MaxFadeAlpha, max_fade_alpha, u8)
            PU_CLASS_POD_GETSET(FadeAlphaVariation, fade_alpha_variation, u8)

            /**
             * @brief Function called before the overlay is rendered. You may use it to configure additional effects, such as alpha modulation during the Overlay rendering.
             * @param drawer Renderer used to render the overlay.
             */
            virtual void OnPreRender(render::Renderer::Ref &drawer) {}

            /**
             * @brief Function called after the overlay is rendered. You may use it to configure additional effects, such as alpha modulation during the Overlay rendering.
             * @param drawer Renderer used to render the overlay.
             */
            virtual void OnPostRender(render::Renderer::Ref &drawer) {}

            /**
             * @brief Rendering callback of the overlay.
             */
            bool Render(render::Renderer::Ref &drawer);

            /**
             * @brief Notifies the overlay that it is ending (fading out).
             * @note Used by Application to handle the overlay fade out effect.
             * @param ending Whether the overlay is ending.
             */
            inline void NotifyEnding(const bool ending) {
                this->is_ending = ending;
            }
    };

}
