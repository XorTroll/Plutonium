
/*

    Plutonium library

    @file ui_Overlay.hpp
    @brief An overlay is some kind of "pop-up", like notification messages or similar items
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Container.hpp>

namespace pu::ui
{
    class Overlay : public Container
    {
        public:
            Overlay(s32 X, s32 Y, s32 Width, s32 Height, Color Background, bool Rounded = true);
            PU_SMART_CTOR(Overlay)

            void SetRadius(s32 Radius);
            s32 GetRadius();
            virtual void OnPreRender(render::Renderer::Ref &Drawer);
            virtual void OnPostRender(render::Renderer::Ref &Drawer);
            bool Render(render::Renderer::Ref &Drawer);
            void NotifyEnding(bool End);
        private:
            s32 fadea;
            Color bg;
            s32 rad;
            bool end;
            bool round;
    };
}