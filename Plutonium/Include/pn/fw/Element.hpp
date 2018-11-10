
#pragma once
#include <pn/render/Renderer.hpp>

namespace pn::fw
{
    class Element
    {
        public:
            virtual u32 GetX() = 0;
            virtual u32 GetY() = 0;
            virtual u32 GetWidth() = 0;
            virtual u32 GetHeight() = 0;
            virtual void OnRender(render::Renderer *Drawer) = 0;
            virtual void OnGlobalInput(u64 Input) = 0;
            virtual void OnTouch(u32 TouchX, u32 TouchY) = 0;
    };
}