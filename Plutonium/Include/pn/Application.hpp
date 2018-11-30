
#pragma once
#include <vector>
#include <pn/fw.hpp>

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
            void SetCustomFont(std::string FontPath);
            bool UsesCustomFont();
            std::string GetCustomFont();
            void ShowDialog(fw::Dialog *Dialog);
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

    class LayoutApplication : public Application
    {
        public:
            LayoutApplication();
            void AddLayout(fw::Layout *NewLayout);
            void NavigateTo(fw::Layout *Source);
            void ClearLayouts();
            void Show();
        private:
            u32 layidx;
    };
}