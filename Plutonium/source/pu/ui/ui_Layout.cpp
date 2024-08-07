#include <pu/ui/ui_Layout.hpp>

namespace pu::ui {

    Layout::~Layout() {
        this->ResetBackgroundImage();
    }

    void Layout::SetBackgroundImage(sdl2::TextureHandle::Ref bg_tex) {
        this->ResetBackgroundImage();
        this->over_bg_tex = bg_tex;
    }

    void Layout::SetBackgroundColor(const Color clr) {
        this->ResetBackgroundImage();
        this->over_bg_color = clr;
    }

    void Layout::ResetBackgroundImage() {
        this->over_bg_tex = {};
    }

    TouchPoint Layout::ConsumeSimulatedTouchPosition() {
        auto touch_pos_copy = this->sim_touch_pos;
        this->sim_touch_pos = {};
        return touch_pos_copy;
    }

}
