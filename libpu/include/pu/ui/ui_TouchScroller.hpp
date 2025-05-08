/**
 * Plutonium library
 * @file ui_TouchScroller.hpp
 * @brief Contains pu::ui::TouchScroller class
 * @author XorTroll
 * @copyright XorTroll
*/

#pragma once
#include <pu/ui/ui_Types.hpp>

namespace pu::ui {

    /**
     * @brief Class used to manager scrolling in a region using touch input.
     * @note This class is used to manage scrolling in a region using touch input. It allows for smooth scrolling in UI elements.
     */
    class TouchScroller final {
        private:
            TouchPoint start_touch_pos;
            s32 scroll_x;
            s32 scroll_y;
            s32 last_dx;
            s32 last_dy;
            s32 max_scroll_x;
            s32 max_scroll_y;
            bool enable_x;
            bool enable_y;
            s32 speed_x;
            s32 speed_y;
            float speed_x_t;
            float speed_y_t;

        public:
            /**
             * @brief Creates a new instance of a TouchScroller object.
             * @param max_scroll_x Maximum scrollable X value.
             * @param max_scroll_y Maximum scrollable Y value.
             * @note This constructor initializes the scroller with the specified maximum scroll values. The minimum scroll values are always 0.
             */
            TouchScroller(const s32 max_scroll_x, const s32 max_scroll_y) : start_touch_pos(), scroll_x(0), scroll_y(0), last_dx(0), last_dy(0), max_scroll_x(max_scroll_x), max_scroll_y(max_scroll_y), enable_x(false), enable_y(false), speed_x(0), speed_y(0), speed_x_t(0.0f), speed_y_t(0.0f) {}

            /**
             * @brief Updates the touch scroller with the current touch position and the (visible part of the) region to check.
             * @param touch_pos Current touch position.
             * @param x X position of the region to check.
             * @param y Y position of the region to check.
             * @param width Width of the region to check.
             * @param height Height of the region to check.
             * @note This function should be called each frame (ideally in the input handling code) to update the scroll state.
             */
            void Update(const TouchPoint touch_pos, const s32 x, const s32 y, const s32 width, const s32 height);

            PU_CLASS_POD_GETSET(MaximumScrollX, max_scroll_x, s32)
            PU_CLASS_POD_GETSET(MaximumScrollY, max_scroll_y, s32)

            PU_CLASS_POD_GETSET(XScrollEnabled, enable_x, bool)
            PU_CLASS_POD_GETSET(YScrollEnabled, enable_y, bool)

            /**
             * @brief Gets the current scroll X value.
             * @return Current scroll X value.
             * @note This function returns the current scroll X value. If X scrolling is disabled, it will just return 0.
             */
            inline s32 GetScrollX() {
                if(!this->enable_x) {
                    return 0;
                }
                return this->scroll_x;
            }

            /**
             * @brief Gets the current scroll Y value.
             * @return Current scroll Y value.
             * @note This function returns the current scroll Y value. If Y scrolling is disabled, it will just return 0.
             */
            inline s32 GetScrollY() {
                if(!this->enable_y) {
                    return 0;
                }
                return this->scroll_y;
            }

            inline void SetScrollX(const s32 scroll_x) {
                this->scroll_x = scroll_x;
            }

            inline void SetScrollY(const s32 scroll_y) {
                this->scroll_y = scroll_y;
            }

            /**
             * @brief Gets whether the user is currently scrolling in any direction (X, Y or both).
             * @return Whether the user is currently scrolling in any direction.
             */ 
            inline bool IsScrolling() {
                return (this->last_dx != 0) || (this->last_dy != 0);
            }
    };

}
