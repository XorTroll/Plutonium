#include <pu/ui/elm/elm_Rectangle.hpp>

namespace pu::ui::elm {

    void Rectangle::OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) {
        drawer->RenderRectangleFill(this->clr, x, y, this->w, this->h);
    }

}