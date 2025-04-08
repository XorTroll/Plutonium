#include <pu/ui/elm/elm_Rectangle.hpp>

namespace pu::ui::elm {

    void Rectangle::OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) {
        drawer->RenderRectangleFill(this->clr, x, y, this->w, this->h);
    }

}
