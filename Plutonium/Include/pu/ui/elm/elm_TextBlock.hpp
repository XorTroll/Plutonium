
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
            TextBlock(s32 X, s32 Y, String Text, s32 FontSize = 25);
            ~TextBlock();
            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            s32 GetHeight();
            s32 GetTextWidth();
            s32 GetTextHeight();
            String GetText();
            void SetText(String Text);
            void SetFont(render::NativeFont Font);
            Color GetColor();
            void SetColor(Color Color);
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);
        private:
            String text;
            s32 x;
            s32 y;
            render::NativeFont fnt;
            s32 fsize;
            Color clr;
            render::NativeTexture ntex;
    };
}