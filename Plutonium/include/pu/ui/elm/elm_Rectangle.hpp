
/*

    Plutonium library

    @file Rectangle.hpp
    @brief A Rectangle is an Element which simply draws a filled rectangle.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    class Rectangle : public Element
    {
        private:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            Color clr;
            i32 border_radius;

        public:
            Rectangle(const i32 x, const i32 y, const i32 width, const i32 height, const Color clr, const i32 border_radius = 0) : Element(), x(x), y(y), w(width), h(height), clr(clr), border_radius(border_radius) {}
            PU_SMART_CTOR(Rectangle)

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
            
            inline i32 GetBorderRadius() {
                return this->border_radius;
            }

            inline void SetBorderRadius(const i32 border_radius) {
                this->border_radius = border_radius;
            }

            
            inline Color GetColor() {
                return this->clr;
            }

            inline void SetColor(const Color clr) {
                this->clr = clr;
            }
            
            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}