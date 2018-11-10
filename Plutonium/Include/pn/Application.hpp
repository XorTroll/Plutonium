
#pragma once
#include <vector>
#include <pn/fw/Rectangle.hpp>

namespace pn
{
    class Application
    {
        public:
            Application();
            ~Application();
            void AddChild(fw::Element *Child);
            void ClearChildren();
            draw::Color GetBackgroundColor();
            void SetBackgroundColor(draw::Color BackColor);
            std::string GetBackgroundImage();
            bool HasBackgroundImage();
            void SetBackgroundImage(std::string Path);
            void DeleteBackgroundImage();
            void Show();
            void Close();
        protected:
            draw::Color bgcolor;
            std::string bgimage;
            bool hasimage;
            bool show;
            std::vector<fw::Element*> elems;
            render::Renderer *rend;
    };
}