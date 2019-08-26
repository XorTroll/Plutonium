
/*

    Plutonium library

    @file ui_Application.hpp
    @brief An Application is the base to use the UI system of this library.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <vector>
#include <functional>
#include <chrono>
#include <pu/ui/ui_Dialog.hpp>
#include <pu/ui/ui_Layout.hpp>
#include <pu/ui/ui_Overlay.hpp>

namespace pu::ui
{
    class Application
    {
        public:
            Application(u32 Flags = SDL_INIT_EVERYTHING, bool RenderAccel = true);
            PU_SMART_CTOR(Application)
            ~Application();

            template<typename Lyt>
            void LoadLayout(std::shared_ptr<Lyt> &Layout)
            {
                static_assert(std::is_base_of<ui::Layout, Lyt>::value, "Layouts must inherit from pu::ui::Layout!");

                this->lyt = std::dynamic_pointer_cast<ui::Layout>(Layout);
            }

            void AddThread(std::function<void()> Callback);
            void SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held, bool Touch)> Callback);
            s32 ShowDialog(std::shared_ptr<Dialog> &ToShow);
            int CreateShowDialog(String Title, String Content, std::vector<String> Options, bool UseLastOptionAsCancel, std::string Icon = "");
            void StartOverlay(std::shared_ptr<Overlay> &Ovl);
            void StartOverlayWithTimeout(std::shared_ptr<Overlay> &Ovl, u64 Milli);
            void EndOverlay();
            void Show();
            void ShowWithFadeIn();
            bool IsShown();
            bool CallForRender();
            bool CallForRenderWithRenderOver(std::function<bool(std::shared_ptr<render::Renderer>&)> RenderFunc);
            void FadeIn();
            void FadeOut();
            bool IsFadedIn();
            void SetFadeAlphaAmountPerFrame(u8 Alpha);
            void OnRender();
            void Close();
            void CloseWithFadeOut();
        protected:
            bool rover;
            std::function<bool(std::shared_ptr<render::Renderer>&)> rof;
            bool show;
            u8 aapf;
            s32 fadea;
            bool closefact;
            std::shared_ptr<Layout> lyt;
            u64 tmillis;
            std::chrono::steady_clock::time_point tclock;
            bool fovl;
            bool ffovl;
            std::shared_ptr<Overlay> ovl;
            std::vector<std::function<void()>> thds;
            std::function<void(u64, u64, u64, bool)> cbipt;
            std::shared_ptr<render::Renderer> rend;
    };
}