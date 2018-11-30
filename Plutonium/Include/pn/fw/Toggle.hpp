
#pragma once
#include <pn/fw/Element.hpp>

namespace pn::fw
{
    class Toggle : public Element
    {
        public:
            Toggle(u32 X, u32 Y, std::string Content, draw::Color General);
            Toggle(u32 X, u32 Y, std::string Content, draw::Color On, draw::Color Off);
            u32 GetX();
            void SetX(u32 X);
            u32 GetY();
            void SetY(u32 Y);
            u32 GetWidth();
            u32 GetHeight();
            std::string GetContent();
            void SetContent(std::string Content);
            draw::Font GetFont();
            void SetFont(draw::Font Font);
            u32 GetFontSize();
            void SetFontSize(u32 Size);
            draw::Color GetColor();
            void SetColor(draw::Color General);
            draw::Color GetOnColor();
            void SetOnColor(draw::Color On);
            draw::Color GetOffColor();
            void SetOffColor(draw::Color Off);
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Input);
        private:
            std::string cnt;
            u32 x;
            u32 y;
            bool toggled;
            bool genclr;
            draw::Color on;
            draw::Color off;
    };
}