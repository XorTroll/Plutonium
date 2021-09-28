
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
            Overlay(i32 X, i32 Y, i32 Width, i32 Height, Color Background, bool Rounded = true);
            PU_SMART_CTOR(Overlay)

            void SetRadius(i32 Radius);
            i32 GetRadius();
            virtual void OnPreRender(render::Renderer::Ref &Drawer);
            virtual void OnPostRender(render::Renderer::Ref &Drawer);
            bool Render(render::Renderer::Ref &Drawer);
            void NotifyEnding(bool End);
        private:
            i32 fadea;
            Color bg;
            i32 rad;
            bool end;
            bool round;
    };
}