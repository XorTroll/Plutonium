#include <pu/ui/elm/elm_Image.hpp>
#include <sys/stat.h>

namespace pu::ui::elm {

    Image::Image(const s32 x, const s32 y, sdl2::TextureHandle::Ref image) : Element() {
        this->x = x;
        this->y = y;
        this->img_tex = nullptr;
        this->rot_angle = -1.0f;
        this->SetImage(image);
    }

    void Image::SetImage(sdl2::TextureHandle::Ref image) {
        this->img_tex = image;
        if(this->img_tex != nullptr) {
            this->width = render::GetTextureWidth(this->img_tex->Get());
            this->height = render::GetTextureHeight(this->img_tex->Get());
        }
    }

    void Image::OnRender(render::Renderer::Ref &drawer) {
        if(this->img_tex != nullptr) {
            drawer->RenderTexture(this->img_tex->Get(), PU_UI_RENDER_XY, render::TextureRenderOptions({}, PU_UI_RENDER_WH, {}, {}, {}));
        }
    }

}
