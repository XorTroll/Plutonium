
/*

    Plutonium library

    @file extras_Toast.hpp
    @brief An Overlay similar to Android's toast notifications
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Overlay.hpp>
#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::extras
{
    class Toast final : public Overlay
    {
        public:
            Toast(String Text, s32 FontSize, Color TextColor, Color BaseColor);
            void SetText(String Text);
            void OnPreRender(render::Renderer *Drawer);
            void OnPostRender(render::Renderer *Drawer);
        private:
            pu::ui::elm::TextBlock *text;
    };
}