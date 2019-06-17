
/*

    Plutonium library

    @file Button.hpp
    @brief A Button is an Element for option selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <functional>
#include <pu/element/Element.hpp>

namespace pu::element
{
    class Button : public Element
    {
        public:
            Button(s32 X, s32 Y, s32 Width, s32 Height, std::string Content, draw::Color TextColor, draw::Color Color);
            ~Button();
            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            void SetWidth(s32 Width);
            s32 GetHeight();
            void SetHeight(s32 Height);
            std::string GetContent();
            void SetContent(std::string Content);
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            void SetContentFont(render::NativeFont Font);
            void SetOnClick(std::function<void()> ClickCallback);
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);
        private:
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            render::NativeFont fnt;
            draw::Color clr;
            std::string cnt;
            std::function<void()> clickcb;
            bool hover;
            s32 hoverfact;
            render::NativeTexture ntex;
    };
}