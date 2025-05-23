/**
 * Plutonium library
 * @file elm_Image.hpp
 * @brief Contains an element for image rendering.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for image rendering.
     */
    class Image : public Element {
        private:
            std::string img_path;
            sdl2::TextureHandle::Ref img_tex;
            render::TextureRenderOptions rend_opts;
            s32 x;
            s32 y;

        public:
            /**
             * @brief Creates a new instance of an Image element.
             * @param x X position of the Image.
             * @param y Y position of the Image.
             * @param image Path to the image to render.
             */
            Image(const s32 x, const s32 y, sdl2::TextureHandle::Ref image);
            PU_SMART_CTOR(Image)

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Image.
             * @param x New X position.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the Image.
             * @param y New Y position.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            inline s32 GetWidth() override {
                return this->rend_opts.width;
            }

            /**
             * @brief Sets the width of the Image.
             * @param width New width.
             */
            inline void SetWidth(const s32 width) {
                this->rend_opts.width = width;
            }

            inline s32 GetHeight() override {
                return this->rend_opts.height;
            }

            /**
             * @brief Sets the height of the Image.
             * @param height New height.
             */
            inline void SetHeight(const s32 height) {
                this->rend_opts.height = height;
            }

            PU_CLASS_POD_GETSET(RotationAngle, rend_opts.rot_angle, float)

            /**
             * @brief Sets the image to render.
             * @param image Path to the image to render.
             */
            void SetImage(sdl2::TextureHandle::Ref image);

            /**
             * @brief Gets the image being rendered.
             * @return Path to the image being rendered.
             */
            inline bool IsImageValid() {
                return this->img_tex != nullptr;
            }
            
            void OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}
