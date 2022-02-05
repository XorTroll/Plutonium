#include <pu/ui/elm/elm_Image.hpp>
#include <sys/stat.h>

namespace pu::ui::elm {

    Image::Image(const i32 x, const i32 y, const std::string &image_path) : Element::Element() {
        this->x = x;
        this->y = y;
        this->img_tex = nullptr;
        this->rend_opts = render::TextureRenderOptions::Default();
        this->SetImage(image_path);
    }

    Image::~Image() {
        render::DeleteTexture(this->img_tex);
    }

    void Image::SetImage(const std::string &image_path) {
        render::DeleteTexture(this->img_tex);

        struct stat st;
        if(stat(image_path.c_str(), &st) == 0) {
            this->img_path = image_path;
            this->img_tex = render::LoadImage(image_path);
            this->rend_opts.width = render::GetTextureWidth(this->img_tex);
            this->rend_opts.height = render::GetTextureHeight(this->img_tex);
        }
    }

    void Image::OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) {
        drawer->RenderTexture(this->img_tex, x, y, this->rend_opts);
    }

}