
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
            static constexpr i32 MaxFadeAlpha = 200;
            static constexpr i32 FadeAlphaVariation = 25;

        private:
            i32 fade_a;
            Color bg_clr;
            i32 rad;
            bool is_ending;
            bool round;

        public:
            Overlay(const i32 x, const i32 y, const i32 width, const i32 height, const Color bg_clr, const bool round = true, const i32 radius = DefaultRadius) : Container(x, y, width, height), fade_a(0), bg_clr(bg_clr), rad(radius), is_ending(false), round(round) {}
            PU_SMART_CTOR(Overlay)

            inline void SetRadius(const i32 radius) {
                this->rad = radius;
            }

            inline i32 GetRadius() {
                return this->rad;
            }

            virtual void OnPreRender(render::Renderer::Ref &drawer) {}
            virtual void OnPostRender(render::Renderer::Ref &drawer) {}
            bool Render(render::Renderer::Ref &drawer);
            
            inline void NotifyEnding(const bool ending) {
                this->is_ending = ending;
            }
    };

}