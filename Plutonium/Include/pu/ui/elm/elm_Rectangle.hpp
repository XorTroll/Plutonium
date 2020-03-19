
/*

    Plutonium library

    @file Rectangle.hpp
    @brief A Rectangle is an Element which simply draws a filled rectangle.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    class Rectangle : public Element
    {
        public:
            Rectangle(i32 X, i32 Y, i32 Width, i32 Height, Color RecColor, i32 BorderRadius = 0);
            PU_SMART_CTOR(Rectangle)

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            void SetWidth(i32 Width);
            i32 GetHeight();
            void SetHeight(i32 Height);
            i32 GetBorderRadius();
            void SetBorderRadius(i32 Radius);
            Color GetColor();
            void SetColor(Color RecColor);
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            i32 borderr;
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            Color clr;
    };
}