
/*

    Plutonium library

    @file Overlay.hpp
    @brief TODO...
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/Container.hpp>

namespace pu::overlay
{
    class Overlay : public Container
    {
        public:
            Overlay(s32 X, s32 Y, s32 Width, s32 Height, draw::Color Background, bool Rounded = true);
            ~Overlay();
            void SetRadius(s32 Radius);
            s32 GetRadius();
            virtual void OnPreRender(render::Renderer *Drawer);
            virtual void OnPostRender(render::Renderer *Drawer);
            bool Render(render::Renderer *Drawer);
            void NotifyEnding(bool End);
        private:
            s32 fadea;
            draw::Color bg;
            s32 rad;
            bool end;
            bool round;
    };
}