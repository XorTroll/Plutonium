
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
    class Toggle : public Element
    {
        public:
            Toggle(s32 X, s32 Y, String Content, u64 Key, Color Color);
            PU_SMART_CTOR(Toggle)
            ~Toggle();

            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            s32 GetHeight();
            String GetContent();
            void SetContent(String Content);
            void SetFont(render::NativeFont Font);
            Color GetColor();
            void SetColor(Color General);
            u64 GetKey();
            void SetKey(u64 Key);
            bool IsChecked();
            void OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, bool Touch);
        private:
            String cnt;
            s32 x;
            s32 y;
            u64 key;
            bool checked;
            Color clr;
            render::NativeFont fnt;
            s32 fsize;
            s32 togfact;
            render::NativeTexture ntex;
    };
}