/**
 * Plutonium library
 * @file ui_Layout.hpp
 * @brief Layout class header.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Group.hpp>
#include <pu/ui/ui_Layer.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

    /**
     * @brief Class that represents a layout, the base Layer in the library.
     * @note The layout covers the entire screen, has a background and it renders all its children elements over it.
     */
    class Layout : public Layer {
        public:
            /**
             * @brief Callback type used for input handling.
             * @note This callback is called every loop.
             * @param keys_down Keys that were pressed in this frame.
             * @param keys_up Keys that were released in this frame.
             * @param keys_held Keys that are being held in this frame.
             * @param touch_pos Touch position in this frame.
             */
            using OnInputCallback = std::function<void(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos)>;

            /**
             * @brief Callback type used for rendering.
             * @note This callback is called every loop, so it may be used in a similar fashion to main loop handling.
             */
            using RenderCallback = std::function<void()>;

        private:
            bool has_image;
            Color over_bg_color;
            sdl2::TextureHandle::Ref over_bg_tex;
            s32 over_bg_tex_x_offset;
            OnInputCallback on_ipt;
            std::vector<RenderCallback> render_cbs;
            Group::Ref root;
            elm::Element::RenderContext ctx;

        public:
            /**
             * @brief Creates a new Layout with the default background (white-ish).
             */
            Layout();
            PU_SMART_CTOR(Layout)
            virtual ~Layout();

            inline bool CapturesInput() final {
                return true;
            }

            /**
             * @brief Sets the input callback for the Layout.
             * @param on_ipt_cb Input callback to set.
             */
            inline void SetOnInput(OnInputCallback on_ipt_cb) {
                this->on_ipt = on_ipt_cb;
            }

            /**
             * @brief Gets the input callback for the Layout.
             * @return The input callback for the Layout.
             */
            inline OnInputCallback GetOnInput() {
                return this->on_ipt;
            }

            /**
             * @brief Adds a render callback to the Layout.
             * @param render_cb Render callback to add.
             */
            inline void AddRenderCallback(RenderCallback render_cb) {
                this->render_cbs.push_back(render_cb);
            }

            /**
             * @brief Gets all render callbacks from the Layout.
             * @return All render callbacks from the Layout.
             */
            inline std::vector<RenderCallback> &GetRenderCallbacks() {
                return this->render_cbs;
            }

            /**
             * @brief Checks whether the Layout has a background image.
             * @return Whether the Layout has a background image.
             */
            inline bool HasBackgroundImage() {
                return this->over_bg_tex != nullptr;
            }

            /**
             * @brief Gets the background image texture of the Layout.
             * @return The background image texture of the Layout.
             */
            inline sdl2::TextureHandle::Ref &GetBackgroundImageTexture() {
                return this->over_bg_tex;
            }

            /**
             * @brief Gets the background color of the Layout.
             * @return The background color of the Layout.
             */
            inline Color GetBackgroundColor() {
                return this->over_bg_color;
            }

            /**
             * @brief Sets the background image of the Layout.
             * @note This will override the background color.
             * @param bg_tex Background image texture to set.
             */
            void SetBackgroundImage(sdl2::TextureHandle::Ref bg_tex);

            /**
             * @brief Resets the background image of the Layout.
             * @note If the Layout has no background image, its background color will be visible instead.
             */
            void ResetBackgroundImage();

            /**
             * @brief Sets the background color of the Layout.
             * @param clr Background color to set.
             */
            void SetBackgroundColor(const Color clr);

            /**
             * @brief Sets the offset of the background image.
             * @param x_offset X offset to set.
             */
            inline void SetBackgroundImageXOffset(const s32 x_offset) {
                this->over_bg_tex_x_offset = x_offset;
            }

            /**
             * @brief Gets the offset of the background image.
             * @return The offset of the background image.
             */
            inline s32 GetBackgroundImageXOffset() {
                return this->over_bg_tex_x_offset;
            }

            /**
             * @brief Resets the offset of the background image.
             */
            inline void ResetBackgroundImageXOffset() {
                this->over_bg_tex_x_offset = 0;
            }

            inline Group::Ref &GetRoot() {
                return this->root;
            }

            inline void AddElement(elm::Element::Ref elem) {
                this->root->AddElement(elem);
            }

            inline void AddSubgroup(Group::Ref group) {
                this->root->AddSubgroup(group);
            }

            void OnStart() final;
            void OnStop() final;
            void OnRender(render::Renderer::Ref &drawer) final;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) final;
    };

}
