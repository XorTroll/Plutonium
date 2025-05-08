#include <pu/ui/ui_TouchScroller.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

    void TouchScroller::Update(const TouchPoint touch_pos, const s32 x, const s32 y, const s32 width, const s32 height) {
        if(!this->enable_x && !this->enable_y) {
            return;
        }

        if(!touch_pos.IsEmpty() && touch_pos.HitsRegion(x, y, width, height)) {
            if(!this->start_touch_pos.IsEmpty()) {
                if(this->enable_x) {
                    const auto dx = touch_pos.x - this->start_touch_pos.x;
                    if((this->last_dx != 0) || (std::abs(dx) > GetStyle()->GetTouchScrollThreshold())) {
                        this->scroll_x += dx;
                        this->last_dx = dx;
                        this->speed_x = 0;
                    }

                    if(this->scroll_x > 0) {
                        this->scroll_x = 0;
                    }
                    else if(this->scroll_x < -this->max_scroll_x) {
                        this->scroll_x = -this->max_scroll_x;
                    }
                }
                if(this->enable_y) {
                    const auto dy = touch_pos.y - this->start_touch_pos.y;
                    if((this->last_dy != 0) || (std::abs(dy) > GetStyle()->GetTouchScrollThreshold())) {
                        this->scroll_y += dy;
                        this->last_dy = dy;
                        this->speed_y = 0;
                    }

                    if(this->scroll_y > 0) {
                        this->scroll_y = 0;
                    }
                    else if(this->scroll_y < -this->max_scroll_y) {
                        this->scroll_y = -this->max_scroll_y;
                    }
                }
            }

            this->start_touch_pos = touch_pos;
        }
        else {
            this->start_touch_pos = {};

            if(this->speed_x != 0) {
                const auto speed_val_x = (s32)(1.0f * this->speed_x * (s32)std::sqrt(1.0f - this->speed_x_t*this->speed_x_t));
                this->scroll_x += speed_val_x;
                this->speed_x_t += 0.05f;

                if(speed_val_x == 0) {
                    this->speed_x = 0;
                }
            }
            else {
                this->speed_x = this->last_dx;
                this->last_dx = 0;
                this->speed_x_t = 0.0f;
            }

            if(this->speed_y != 0) {
                const auto speed_val_y = (s32)(this->speed_y * std::exp(- 3.0f * this->speed_y_t)); 
                // DebugLog("Speed Y: " + std::to_string(this->speed_y) + " Speed Y T: " + std::to_string(this->speed_y_t) + " Speed Val Y: " + std::to_string(speed_val_y) + " Scroll Y: " + std::to_string(this->scroll_y));
                this->scroll_y += speed_val_y;
                this->speed_y_t += 0.05f;

                if(speed_val_y == 0) {
                    this->speed_y = 0;
                }
            }
            else {
                this->speed_y = this->last_dy;
                this->last_dy = 0;
                this->speed_y_t = 0.0f;
            }

            if(this->scroll_x > 0) {
                this->scroll_x = 0;
            }
            if(this->scroll_x < -this->max_scroll_x) {
                this->scroll_x = -this->max_scroll_x;
            }
            if(this->scroll_y > 0) {
                this->scroll_y = 0;
            }
            if(this->scroll_y < -this->max_scroll_y) {
                this->scroll_y = -this->max_scroll_y;
            }
        }
    }

}
