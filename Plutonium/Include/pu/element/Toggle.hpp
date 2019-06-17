
/*

    Plutonium library

    @file Toggle.hpp
    @brief A Toggle is an Element used to switch between two options by toggling the item.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>

namespace pu::element
{
    class Toggle : public Element
    {
        public:
            Toggle(s32 X, s32 Y, std::string Content, u64 Key, draw::Color Color);
            ~Toggle();
            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            s32 GetHeight();
            std::string GetContent();
            void SetContent(std::string Content);
            void SetFont(render::NativeFont Font);
            draw::Color GetColor();
            void SetColor(draw::Color General);
            u64 GetKey();
            void SetKey(u64 Key);
            bool IsChecked();
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);
        private:
            std::string cnt;
            s32 x;
            s32 y;
            u64 key;
            bool checked;
            draw::Color clr;
            render::NativeFont fnt;
            s32 fsize;
            s32 togfact;
            render::NativeTexture ntex;
    };
}