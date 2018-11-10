
#pragma once
#include <pn/horizon/button/Light.hpp>
#include <pn/horizon/button/Dark.hpp>
#include <pn/fw/Element.hpp>
#include <switch.h>
#include <vector>
#include <string>
#include <map>

namespace pn::horizon
{
    class PageControls
    {
        public:
            void Add(std::string Button, std::string Description);
            void Clear();
            std::map<std::string, std::string> GetControls();
        private:
            std::map<std::string, std::string> ctrls;
    };

    class Page : public fw::Element
    {
        public:
            Page(std::string Name);
            std::string GetName();
            void SetName(std::string Name);
            PageControls *GetControls();
            void SetControls(PageControls *Controls);
            u32 GetX();
            u32 GetY();
            u32 GetWidth();
            u32 GetHeight();
            void AddChild(fw::Element *Child);
            void ClearChildren();
            void OnRender(render::Renderer *Drawer);
            void OnGlobalInput(u64 Input);
            void OnTouch(u32 TouchX, u32 TouchY);
        private:
            PageControls *ctrls;
            std::string name;
            std::vector<fw::Element*> pelems;
    };
}