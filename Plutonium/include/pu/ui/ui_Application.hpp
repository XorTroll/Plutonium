
/*

    Plutonium library

    @file ui_Application.hpp
    @brief An Application is the base to use the UI system of this library.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Dialog.hpp>
#include <pu/ui/ui_Layout.hpp>
#include <pu/ui/ui_Overlay.hpp>
#include <chrono>

namespace pu::ui {

    class Application {
        public:
            using DialogPrepareCallback = std::function<void(Dialog::Ref&)>;
            using OnInputCallback = std::function<void(const u64, const u64, const u64, const TouchPoint)>;
            using RenderCallback = std::function<void()>;
            using RenderOverFunction = std::function<bool(render::Renderer::Ref&)>;

            static constexpr u8 DefaultFadeAlphaIncrementSteps = 20;

        protected:
            bool loaded;
            bool in_render_over;
            RenderOverFunction render_over_fn;
            bool is_shown;
            u8 fade_alpha_increment_steps;
            SigmoidIncrementer<i32> fade_alpha_incr;
            i32 fade_alpha;
            sdl2::TextureHandle::Ref fade_bg_tex;
            Color fade_bg_clr;
            Layout::Ref lyt;
            Overlay::Ref ovl;
            u64 ovl_timeout_ms;
            std::chrono::steady_clock::time_point ovl_start_time;
            std::vector<RenderCallback> render_cbs;
            OnInputCallback on_ipt_cb;
            render::Renderer::Ref renderer;
            RMutex render_lock;
        
        public:
            Application(render::Renderer::Ref renderer);
            PU_SMART_CTOR(Application)
            virtual ~Application();

            inline void LoadLayout(Layout::Ref lyt) {
                this->lyt = lyt;
            }

            template<typename L>
            inline std::shared_ptr<L> GetLayout() {
                static_assert(std::is_base_of_v<ui::Layout, L>);
                return std::static_pointer_cast<L>(this->lyt);
            }

            void Prepare();

            // Force create a derived Application class which initializes everything here
            virtual void OnLoad() = 0;

            inline void AddRenderCallback(RenderCallback render_cb) {
                this->render_cbs.push_back(render_cb);
            }

            inline void SetOnInput(OnInputCallback on_ipt_cb) {
                this->on_ipt_cb = on_ipt_cb;
            }

            inline i32 ShowDialog(Dialog::Ref &dialog) {
                return dialog->Show(this);
            }

            i32 CreateShowDialog(const std::string &title, const std::string &content, const std::vector<std::string> &opts, const bool use_last_opt_as_cancel, sdl2::TextureHandle::Ref icon = {}, DialogPrepareCallback prepare_cb = nullptr);
            
            inline void StartOverlay(Overlay::Ref ovl) {
                if(this->ovl == nullptr) {
                    this->ovl = ovl;
                }
            }

            void StartOverlayWithTimeout(Overlay::Ref ovl, const u64 ms);
            void EndOverlay();
            void Show();
            
            inline void ShowWithFadeIn() {
                this->FadeIn();
                this->Show();
            }
            
            inline bool IsShown() {
                return this->is_shown;
            }

            inline bool CanBeShown() {
                return this->loaded && (this->lyt != nullptr);
            }
            
            bool CallForRender();
            bool CallForRenderWithRenderOver(RenderOverFunction render_over_fn);

            inline void LockRender() {
                rmutexLock(&this->render_lock);
            }

            inline void UnlockRender() {
                rmutexUnlock(&this->render_lock);
            }

            void FadeIn();
            void FadeOut();
            
            inline bool IsFadedIn() {
                return this->fade_alpha > 0;
            }
            
            inline void SetFadeAlphaIncrementStepCount(const u8 fade_alpha_increment_steps) {
                this->fade_alpha_increment_steps = fade_alpha_increment_steps;
            }

            void SetFadeBackgroundImage(sdl2::TextureHandle::Ref bg_tex);
            void ResetFadeBackgroundImage();

            inline sdl2::TextureHandle::Ref &GetFadeBackgroundImageTexture() {
                return this->fade_bg_tex;
            }

            inline bool HasFadeBackgroundImage() {
                return this->fade_bg_tex != nullptr;
            }

            void SetFadeBackgroundColor(const Color clr);
            
            void OnRender();
            void Close(const bool do_exit = false);
            
            inline void CloseWithFadeOut(const bool do_exit = false) {
                this->FadeOut();
                this->Close(do_exit);
            }

            inline u64 GetButtonsDown() {
                return this->renderer->GetButtonsDown();
            }

            inline u64 GetButtonsUp() {
                return this->renderer->GetButtonsUp();
            }

            inline u64 GetButtonsHeld() {
                return this->renderer->GetButtonsHeld();
            }

            inline HidTouchScreenState GetTouchState() {
                HidTouchScreenState state = {};
                hidGetTouchScreenStates(&state, 1);
                return state;
            }
    };

}
