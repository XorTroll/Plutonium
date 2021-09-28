
/*

    Plutonium library

    @file Button.hpp
    @brief A Button is an Element for option selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <functional>
#include <pu/pu_String.hpp>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    class Button : public Element
    {
        public:
            Button(i32 X, i32 Y, i32 Width, i32 Height, String Content, Color TextColor, Color Color);
            PU_SMART_CTOR(Button)
            ~Button();

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            void SetWidth(i32 Width);
            i32 GetHeight();
            void SetHeight(i32 Height);
            String GetContent();
            void SetContent(String Content);
            Color GetColor();
            void SetColor(Color Color);
            void SetContentFont(String font_name);
            void SetOnClick(std::function<void()> ClickCallback);
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            String fnt_name;
            Color clr;
            String cnt;
            std::function<void()> clickcb;
            bool hover;
            i32 hoverfact;
            sdl2::Texture ntex;
    };
}