
/*

    Plutonium library

    @file Image.hpp
    @brief An Image is an Element showing a picture. (JPEG, PNG, TGA, BMP)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    class Image : public Element {
        private:
            std::string img_path;
            sdl2::TextureHandle::Ref img_tex;
            render::TextureRenderOptions rend_opts;
            i32 x;
            i32 y;

        public:
            Image(const i32 x, const i32 y, sdl2::TextureHandle::Ref image);
            PU_SMART_CTOR(Image)

            inline i32 GetX() override {
                return this->x;
            }

            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            inline void SetY(const i32 y) {
                this->y = y;
            }

            inline i32 GetWidth() override {
                return this->rend_opts.width;
            }

            inline void SetWidth(const i32 width) {
                this->rend_opts.width = width;
            }

            inline i32 GetHeight() override {
                return this->rend_opts.height;
            }

            inline void SetHeight(const i32 height) {
                this->rend_opts.height = height;
            }

            PU_CLASS_POD_GETSET(RotationAngle, rend_opts.rot_angle, float)
            
            void SetImage(sdl2::TextureHandle::Ref image);
            
            inline bool IsImageValid() {
                return this->img_tex != nullptr;
            }
            
            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}
