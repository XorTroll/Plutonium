
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
            virtual void OnInput(u64 Input) = 0;
    };
}