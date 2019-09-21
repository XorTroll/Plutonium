
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
            Rectangle(s32 X, s32 Y, s32 Width, s32 Height, Color RecColor, s32 BorderRadius = 0);
            PU_SMART_CTOR(Rectangle)

            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            void SetWidth(s32 Width);
            s32 GetHeight();
            void SetHeight(s32 Height);
            s32 GetBorderRadius();
            void SetBorderRadius(s32 Radius);
            Color GetColor();
            void SetColor(Color RecColor);
            void OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            s32 borderr;
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            Color clr;
    };
}