#include <pu/ui/ui_Layout.hpp>

namespace pu::ui {

    Layout::~Layout() {
        render::DeleteTexture(this->over_bg_tex);
    }

    void Layout::SetBackgroundImage(const std::string &path) {
        render::DeleteTexture(this->over_bg_tex);
        this->has_image = true;
        this->over_bg_tex = render::LoadImage(path);
    }

    void Layout::SetBackgroundColor(const Color clr) {
        render::DeleteTexture(this->over_bg_tex);
        this->has_image = false;
        this->over_bg_color = clr;
    }

    TouchPoint Layout::ConsumeSimulatedTouchPosition() {
        auto touch_pos_copy = this->sim_touch_pos;
        this->sim_touch_pos = {};
        return touch_pos_copy;
    }

}