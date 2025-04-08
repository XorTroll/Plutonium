/**
 * Plutonium library
 * @file elm_Rectangle.hpp
 * @brief Contains an element for rendering rectangles.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for rendering rectangles.
     */
    class Rectangle : public Element {
        private:
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            Color clr;
            s32 border_radius;

        public:
            /**
             * @brief Creates a new instance of a Rectangle element.
             * @param x X position of the Rectangle.
             * @param y Y position of the Rectangle.
             * @param width Width of the Rectangle.
             * @param height Height of the Rectangle.
             * @param clr Color of the Rectangle.
             * @param border_radius Radius of the Rectangle's corners, or 0 for no rounded corners.
             */
            Rectangle(const s32 x, const s32 y, const s32 width, const s32 height, const Color clr, const s32 border_radius = 0) : Element(), x(x), y(y), w(width), h(height), clr(clr), border_radius(border_radius) {}
            PU_SMART_CTOR(Rectangle)

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Rectangle.
             * @param x New X position.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the Rectangle.
             * @param y New Y position.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            inline s32 GetWidth() override {
                return this->w;
            }

            /**
             * @brief Sets the width of the Rectangle.
             * @param width New width.
             */
            inline void SetWidth(const s32 width) {
                this->w = width;
            }

            inline s32 GetHeight() override {
                return this->h;
            }

            /**
             * @brief Sets the height of the Rectangle.
             * @param height New height.
             */
            inline void SetHeight(const s32 height) {
                this->h = height;
            }

            PU_CLASS_POD_GETSET(BorderRadius, border_radius, s32)
            PU_CLASS_POD_GETSET(Color, clr, Color)
            
            void OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}
