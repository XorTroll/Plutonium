
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
            Application(render::Renderer::Ref Renderer);
            PU_SMART_CTOR(Application)

            template<typename L>
            inline void LoadLayout(std::shared_ptr<L> Layout)
            {
                static_assert(std::is_base_of_v<ui::Layout, L>);

                this->lyt = std::static_pointer_cast<ui::Layout>(Layout);
            }

            template<typename L>
            inline std::shared_ptr<L> GetLayout()
            {
                static_assert(std::is_base_of_v<ui::Layout, L>);

                return std::static_pointer_cast<L>(this->lyt);
            }

            void Prepare();

            // Force create a derived Application class which initializes everything here
            virtual void OnLoad() = 0;

            void AddThread(std::function<void()> Callback);
            void SetOnInput(std::function<void(u64 Down, u64 Up, u64 Held, Touch Pos)> Callback);
            i32 ShowDialog(Dialog::Ref &ToShow);
            int CreateShowDialog(String Title, String Content, std::vector<String> Options, bool UseLastOptionAsCancel, std::string Icon = "");
            
            template<typename O>
            inline void StartOverlay(std::shared_ptr<O> Overlay)
            {
                static_assert(std::is_base_of_v<ui::Overlay, O>);

                if(this->ovl == nullptr) this->ovl = std::dynamic_pointer_cast<ui::Overlay>(Overlay);
            }

            template<typename O>
            inline void StartOverlayWithTimeout(std::shared_ptr<O> Overlay, u64 Milli)
            {
                static_assert(std::is_base_of_v<ui::Overlay, O>);

                if(this->ovl == nullptr)
                {
                    this->ovl = std::dynamic_pointer_cast<ui::Overlay>(Overlay);
                    this->tmillis = Milli;
                    this->tclock = std::chrono::steady_clock::now();
                }
            }

            void EndOverlay();
            void Show();
            void ShowWithFadeIn();
            bool IsShown();
            bool CallForRender();
            bool CallForRenderWithRenderOver(std::function<bool(render::Renderer::Ref&)> RenderFunc);
            void FadeIn();
            void FadeOut();
            bool IsFadedIn();
            void SetFadeAlphaAmountPerFrame(u8 Alpha);
            void OnRender();
            void Close();
            void CloseWithFadeOut();

            inline void UpdateButtons() {
                padUpdate(&this->input_pad);
            }

            inline u64 GetButtonsDown() {
                return padGetButtonsDown(&this->input_pad);
            }

            inline u64 GetButtonsUp() {
                return padGetButtonsUp(&this->input_pad);
            }

            inline u64 GetButtonsHeld() {
                return padGetButtons(&this->input_pad);
            }

            inline HidTouchScreenState GetTouchState() {
                HidTouchScreenState state = {};
                hidGetTouchScreenStates(&state, 1);
                return state;
            }

        protected:
            bool loaded;
            bool rover;
            std::function<bool(render::Renderer::Ref&)> rof;
            bool show;
            u8 aapf;
            i32 fadea;
            bool closefact;
            Layout::Ref lyt;
            u64 tmillis;
            std::chrono::steady_clock::time_point tclock;
            bool fovl;
            bool ffovl;
            Overlay::Ref ovl;
            std::vector<std::function<void()>> thds;
            std::function<void(u64, u64, u64, Touch)> cbipt;
            render::Renderer::Ref rend;
            PadState input_pad;
    };
}