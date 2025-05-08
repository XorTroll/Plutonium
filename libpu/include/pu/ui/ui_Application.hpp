/**
 * Plutonium library
 * @file ui_Application.hpp
 * @brief Contains pu::ui::Application class
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Layout.hpp>
#include <pu/ui/ly/ly_Dialog.hpp>
#include <chrono>

namespace pu::ui {

    /**
     * @brief Type that represents the basic object in this library, the general context for UI and rendering.
     */
    class Application {
        public:
            /**
             * @brief Function type used to further customize a Dialog (setting fields) when using Application::CreateShowDialog.
             */
            using DialogPrepareCallback = std::function<void(ly::Dialog::Ref&)>;

            /**
             * @brief Function type used to handle input events.
             * @param keys_down The keys that were pressed in this frame.
             * @param keys_up The keys that were released in this frame.
             * @param keys_held The keys that are being held in this frame.
             * @param touch_pos The position of the touch on the screen.
             */
            using OnInputCallback = std::function<void(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos)>;

            /**
             * @brief Function type to be called every rendering loop/frame.
             */
            using RenderCallback = std::function<void()>;

            /**
             * @brief Function type to be called when rendering over the main rendering loop/frame.
             * @param renderer The Renderer instance to render over.
             * @return Whether the rendering loop/frame should continue.
             */
            using RenderOverFunction = std::function<bool(render::Renderer::Ref&)>;
            
            // Self-explanatory constant(s)

            static constexpr u8 DefaultFadeAlphaIncrementSteps = 20;

        private:
            void UpdateInput();
            void OnRender(const bool handle_input);

        protected:
            bool loaded;
            bool is_shown;
            u8 fade_alpha_increment_steps;
            SigmoidIncrementer<s32> fade_alpha_incr;
            s32 fade_alpha;
            sdl2::TextureHandle::Ref fade_bg_tex;
            Color fade_bg_clr;
            std::vector<Layer::Ref> layers;
            std::vector<RenderCallback> render_cbs;
            render::Renderer::Ref renderer;
            u64 keys_down;
            u64 keys_up;
            u64 keys_held;
            TouchPoint touch_pos;
        
        public:
            /**
             * @brief Creates a new Application with the specified Renderer.
             * @param renderer The Renderer to use for rendering.
             */
            Application(render::Renderer::Ref renderer);
            PU_SMART_CTOR(Application)
            virtual ~Application();

            /**
             * @brief Sets the Layout to be used by the Application.
             * @param lyt The Layout to load.
             * @note The Layout is always the bottom Layer rendered by the Application.
             */
            inline void LoadLayout(Layout::Ref lyt) {
                this->layers.at(0) = lyt;
            }

            /**
             * @brief Gets the current Layout (of the specified type).
             * @tparam L The type of Layout to get.
             * @return The Layout of the specified type.
             */
            template<typename L>
            inline std::shared_ptr<L> GetLayout() {
                static_assert(std::is_base_of_v<ui::Layout, L>);
                return std::static_pointer_cast<L>(this->layers.at(0));
            }

            /**
             * @brief Loads the Application.
             * @note This function must be called before calling Application::Show or similar.
             * @return Whether the Application was loaded successfully.
             */
            Result Load();

            /**
             * @brief Function to be implemented by child classes, called when the Application is loaded.
             * @note This function must be implemented by the user.
             */
            virtual void OnLoad() = 0;

            /**
             * @brief Adds a RenderCallback to the Application.
             * @param render_cb The RenderCallback to add.
             */
            inline void AddRenderCallback(RenderCallback render_cb) {
                this->render_cbs.push_back(render_cb);
            }

            /**
             * @brief Adds a Layer to the Application.
             * @param layer The Layer to add.
             * @note The Layer will be added to the top of the stack, and it will be rendered over any prior still-active Layers.
             * @note The topmost Layer that deals with input will be the only Layer capturing input.
             */
            void AddLayer(Layer::Ref layer);
            
            /**
             * @brief Wrapper function that shows a Dialog and waits for the user to interact with it.
             * @param dialog The Dialog to show.
             * @return The index of the option selected by the user.
             * @note This function will block until the user interacts with the Dialog. This is just a special wrapper around AddLayer for Dialog, waiting in loop until the Dialog finishes.
             */
            s32 ShowDialog(ly::Dialog::Ref dialog);

            /**
             * @brief Wrapper function that creates a Dialog with the specified parameters and shows it.
             * @param title The title of the Dialog.
             * @param content The content of the Dialog.
             * @param opts The options of the Dialog.
             * @param use_last_opt_as_cancel Whether the last option should be used as a cancel option.
             * @param icon The icon of the Dialog.
             * @param prepare_cb The DialogPrepareCallback to further customize the Dialog.
             * @return The index of the option selected by the user.
             * @note This function will block until the user interacts with the Dialog. This is just a wrapper around ShowDialog, creating the Dialog and waiting in loop until it finishes.
             */
            s32 CreateShowDialog(const std::string &title, const std::string &content, const std::vector<std::string> &opts, const bool use_last_opt_as_cancel, sdl2::TextureHandle::Ref icon = {}, DialogPrepareCallback prepare_cb = nullptr);

            /**
             * @brief Shows the Application.
             * @note Application::Load must be called before calling this function, and the Layout must be previously set using Application::LoadLayout.
             * @note If no Layout was previously set or if the Application was not loaded yet, this function will inmediately return.
             */
            Result Show();
            
            /**
             * @brief Shows the Application with a fade-in effect.
             * @note Application::Load must be called before calling this function, and the Layout must be previously set using Application::LoadLayout.
             * @note If no Layout was previously set or if the Application was not loaded yet, this function will inmediately return.
             */
            inline Result ShowWithFadeIn() {
                this->FadeIn();
                return this->Show();
            }
            
            /**
             * @brief Gets whether the Application is currently shown.
             * @return Whether the Application is currently shown.
             */
            inline bool IsShown() {
                return this->is_shown;
            }

            /**
             * @brief Gets whether the Application can be shown.
             * @note This function checks if the Application is loaded and if any Layout was set.
             * @return Whether the Application can be shown.
             */
            inline bool CanBeShown() {
                return this->loaded && (this->layers.at(0) != nullptr);
            }
            
            /**
             * @brief Calls for rendering the Application.
             * @param handle_input Whether to handle input in this call.
             * @return Whether the rendering loop/frame should continue.
             * @note This is essentially the rendering code called every frame. This function may be used to create custom rendering loops, but be careful when using it.
             * @note Return-values of false could happen, for instance, if there is no Layout loaded yet.
             */
            bool CallForRender(const bool handle_input);

            /**
             * @brief Starts and waits for a fade-in effect.
             * @note This function will block until the fade-in effect is completed. Input won't be handled during this time.
             */
            void FadeIn();

            /**
             * @brief Starts and waits for a fade-out effect.
             * @note This function will block until the fade-out effect is completed. Input won't be handled during this time.
             */
            void FadeOut();
            
            /**
             * @brief Gets whether the Application is currently fading in or already faded in.
             * @return Whether the Application is currently fading in or already faded in.
             */
            inline bool IsFadingOrFadedIn() {
                return this->fade_alpha > 0;
            }

            /**
             * @brief Sets the number of steps for the fade-in and fade-out effects.
             * @param fade_alpha_increment_steps The number of steps for the fade-in and fade-out effects.
             */
            inline void SetFadeAlphaIncrementStepCount(const u8 fade_alpha_increment_steps) {
                this->fade_alpha_increment_steps = fade_alpha_increment_steps;
            }

            /**
             * @brief Sets the target background image for the fade effect.
             * @param bg_tex The background image to use for the fade effect.
             * @note Fade effects will start/end with the specified background image.
             */
            void SetFadeBackgroundImage(sdl2::TextureHandle::Ref bg_tex);

            /**
             * @brief Resets the background image used for the fade effect.
             * @note This function will reset the background image used for the fade effect, and the fade effect will use the set solid color instead.
             */
            void ResetFadeBackgroundImage();

            /**
             * @brief Gets the background image used for the fade effect.
             * @return The background image used for the fade effect.
             */
            inline sdl2::TextureHandle::Ref &GetFadeBackgroundImageTexture() {
                return this->fade_bg_tex;
            }

            /**
             * @brief Gets whether the fade effect is using a background image.
             * @return Whether the fade effect is using a background image.
             */
            inline bool HasFadeBackgroundImage() {
                return this->fade_bg_tex != nullptr;
            }

            /**
             * @brief Sets the background color for the fade effect.
             * @param clr The background color to use for the fade effect.
             * @note Fade effects will start/end with the specified background color.
             * @note If a background image is set, this function will reset it.
             */
            void SetFadeBackgroundColor(const Color clr);
            
            /**
             * @brief Closes the Application.
             * @param do_exit Whether the program should fully exit after closing.
             * @note This function will finish the Application and, if specified, exit the program using `exit(0)`.
             */
            void Close(const bool do_exit = false);
            
            /**
             * @brief Closes the Application with a fade-out effect.
             * @param do_exit Whether the program should fully exit after closing.
             * @note This function will finish the Application with a fade-out effect and, if specified, exit the program using `exit(0)`.
             */
            inline void CloseWithFadeOut(const bool do_exit = false) {
                this->FadeOut();
                this->Close(do_exit);
            }
    };

}
