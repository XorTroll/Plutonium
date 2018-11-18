
#pragma once
#include <pn/fw/Element.hpp>

namespace pn::fw
{
    class TextBlock : public Element
    {
        public:
            TextBlock(u32 X, u32 Y, std::string Text);
            TextBlock(u32 X, u32 Y, std::string Text, draw::Color TextColor);
            TextBlock(u32 X, u32 Y, std::string Text, draw::SystemFont Font);
            TextBlock(u32 X, u32 Y, std::string Text, draw::Color TextColor, draw::SystemFont Font);
            TextBlock(u32 X, u32 Y, std::string Text, draw::Color TextColor, draw::SystemFont Font, u32 Size);
            u32 GetX();
            void SetX(u32 X);
            u32 GetY();
            void SetY(u32 Y);
            u32 GetWidth();
            u32 GetHeight();
            std::string GetText();
            void SetText(std::string Text);
            draw::SystemFont GetFont();
            void SetFont(draw::SystemFont Font);
            u32 GetFontSize();
            void SetFontSize(u32 Size);
            draw::Color GetColor();
            void SetColor(draw::Color TextColor);
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Input);
        private:
            std::string text;
            u32 x;
            u32 y;
            draw::SystemFont fnt;
            u32 fsize;
            draw::Color clr;
    };
}