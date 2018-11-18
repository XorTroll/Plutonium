
#pragma once
#include <pn/fw/Element.hpp>
#include <vector>

namespace pn::fw
{
    class Layout : public Element
    {
        public:
            Layout();
            Layout(draw::Color background);
            u32 GetX();
            u32 GetY();
            u32 GetWidth();
            u32 GetHeight();
            void AddChild(Element *Child);
            void ClearChildren();
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Input);
        private:
            draw::Color bg;
            std::vector<Element*> elms;
    };
}