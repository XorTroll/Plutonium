
/*

    Plutonium library

    @file ui_Layout.hpp
    @brief Contains pu::Layout class, the object used to render within applications
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Container.hpp>
#include <functional>

namespace pu::ui
{
    class Layout : public Container
    {
        public:
            Layout();
            PU_SMART_CTOR(Layout)
            ~Layout();

            bool HasChilds();
            void SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> Callback);
            std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> GetOnInput();
            void AddThread(std::function<void()> Callback);
            std::vector<std::function<void()>> GetAllThreads();
            void SetBackgroundImage(std::string Path);
            void SetBackgroundColor(Color Color);
            render::NativeTexture GetBackgroundImageTexture();
            Color GetBackgroundColor();
            bool HasBackgroundImage();
        private:
            bool hasimage;
            Color overbgcolor;
            render::NativeTexture overbgtex;
            std::function<void(u64, u64, u64, bool)> onipt;
            std::vector<std::function<void()>> thds;
    };
}