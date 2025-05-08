#include <pu/ui/elm/elm_Separator.hpp>

namespace pu::ui::elm {

    void Separator::OnRender(render::Renderer::Ref &drawer) {
        drawer->RenderRectangleFill(this->clr, PU_UI_RENDER_XYWH);
    }

}
