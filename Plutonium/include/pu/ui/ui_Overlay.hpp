
/*

    Plutonium library

    @file ui_Overlay.hpp
    @brief An overlay is some kind of "pop-up", like notification messages or similar items
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Container.hpp>

namespace pu::ui {

    class Overlay : public Container {
        public:
            static constexpr i32 DefaultRadius = 25;
            static constexpr u8 DefaultMaxFadeAlpha = 200;
            static constexpr u8 DefaultFadeAlphaVariation = 25;

        private:
            i32 fade_a;
            Color bg_clr;
            i32 rad;
            bool is_ending;
            u8 max_fade_alpha;
            u8 fade_alpha_variation;

        public:
            Overlay(const i32 x, const i32 y, const i32 width, const i32 height, const Color bg_clr) : Container(x, y, width, height), fade_a(0), bg_clr(bg_clr), rad(DefaultRadius), is_ending(false), max_fade_alpha(DefaultMaxFadeAlpha), fade_alpha_variation(DefaultFadeAlphaVariation) {}
            PU_SMART_CTOR(Overlay)

            PU_CLASS_POD_GETSET(Radius, rad, i32)

            inline bool HasRadius() {
                return this->rad > 0;
            }

            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)
            PU_CLASS_POD_GETSET(MaxFadeAlpha, max_fade_alpha, u8)
            PU_CLASS_POD_GETSET(FadeAlphaVariation, fade_alpha_variation, u8)

            virtual void OnPreRender(render::Renderer::Ref &drawer) {}
            virtual void OnPostRender(render::Renderer::Ref &drawer) {}
            bool Render(render::Renderer::Ref &drawer);
            
            inline void NotifyEnding(const bool ending) {
                this->is_ending = ending;
            }
    };

}
