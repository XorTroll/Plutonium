
/*

    Plutonium library

    @file Toggle.hpp
    @brief A Toggle is an Element used to switch between two options by toggling the item.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_String.hpp>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    constexpr u64 TouchPseudoKey = HidNpadButton_29;

    class Toggle : public Element
    {
        public:
            Toggle(i32 X, i32 Y, String Content, u64 Key, Color Color);
            PU_SMART_CTOR(Toggle)
            ~Toggle();

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            i32 GetHeight();
            String GetContent();
            void SetContent(String Content);
            void SetFont(String font_name);
            Color GetColor();
            void SetColor(Color General);
            u64 GetKey();
            void SetKey(u64 Key);
            bool IsChecked();
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            String cnt;
            i32 x;
            i32 y;
            u64 key;
            bool checked;
            Color clr;
            String fnt_name;
            i32 fsize;
            i32 togfact;
            sdl2::Texture ntex;
    };
}