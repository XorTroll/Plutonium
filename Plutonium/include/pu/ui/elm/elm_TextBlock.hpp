
/*

    Plutonium library

    @file TextBlock.hpp
    @brief A TextBlock is a very useful Element which is used to draw text on the screen.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_String.hpp>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    class TextBlock : public Element
    {
        public:
            TextBlock(i32 X, i32 Y, String Text);
            PU_SMART_CTOR(TextBlock)
            ~TextBlock();

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            i32 GetHeight();
            i32 GetTextWidth();
            i32 GetTextHeight();
            String GetText();
            void SetText(String Text);
            void SetFont(String font_name);
            Color GetColor();
            void SetColor(Color Color);
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            String text;
            i32 x;
            i32 y;
            String fnt_name;
            Color clr;
            sdl2::Texture ntex;
    };
}