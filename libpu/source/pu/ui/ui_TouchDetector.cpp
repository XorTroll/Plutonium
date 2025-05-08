#include <pu/ui/ui_TouchDetector.hpp>

namespace pu::ui {

    void TouchDetector::Update(const TouchPoint touch_pos, const s32 x, const s32 y, const s32 width, const s32 height) {
        if(!touch_pos.IsEmpty()) {
            const auto is_in = touch_pos.HitsRegion(x, y, width, height) && !touch_pos.is_scrolling;
            if(!this->prev_valid && is_in) {
                this->held = true;
            }
            else if(!is_in) {
                this->held = false;
            }
            this->prev_in = is_in;
        }
        else {
            if(this->prev_in && this->held) {
                this->clicked = true;
            }

            this->held = false;
            this->prev_in = false;
        }

        this->prev_valid = !touch_pos.IsEmpty();
    }

}
