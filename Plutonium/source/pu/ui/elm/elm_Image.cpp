#include <pu/ui/elm/elm_Image.hpp>
#include <sys/stat.h>

namespace pu::ui::elm {

    Image::Image(const i32 x, const i32 y, sdl2::TextureHandle::Ref image) : Element() {
        this->x = x;
        this->y = y;
        this->img_tex = nullptr;
        this->rend_opts = render::TextureRenderOptions();
        this->SetImage(image);
    }

    void Image::SetImage(sdl2::TextureHandle::Ref image) {
        this->img_tex = image;
        if(this->img_tex != nullptr) {
            this->rend_opts.width = render::GetTextureWidth(this->img_tex->Get());
            this->rend_opts.height = render::GetTextureHeight(this->img_tex->Get());
        }
    }

    void Image::OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) {
        if(this->img_tex != nullptr) {
            drawer->RenderTexture(this->img_tex->Get(), x, y, this->rend_opts);
        }
    }

}
