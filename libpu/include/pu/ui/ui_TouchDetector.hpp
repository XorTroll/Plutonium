/**
 * Plutonium library
 * @file ui_TouchDetector.hpp
 * @brief Contains pu::ui::TouchDetector class
 * @author XorTroll
 * @copyright XorTroll
*/

#pragma once
#include <pu/ui/ui_Types.hpp>

namespace pu::ui {

    /**
     * @brief Helper class used to detect touch hovering/clicking in a given region (base touch logic for buttons or similar UI elements).
     */
    class TouchDetector final {
        private:
            bool prev_valid;
            bool prev_in;
            bool held;
            bool clicked;

        public:
            /**
             * @brief Creates a new instance of a TouchDetector object.
             */
            TouchDetector() : prev_valid(false), prev_in(false), held(false), clicked(false) {}

            /**
             * @brief Updates the touch detector with the current touch position and the region to check.
             * @param touch_pos Current touch position.
             * @param x X position of the region to check.
             * @param y Y position of the region to check.
             * @param width Width of the region to check.
             * @param height Height of the region to check.
             * @note This function should be called each frame (ideally in the input handling code) to update the touch state.
             */
            void Update(const TouchPoint touch_pos, const s32 x, const s32 y, const s32 width, const s32 height);

            /**
             * @brief Returns the region is currently being held.
             * @return Whether the region is currently being held.
             */
            inline bool IsHeld() {
                return this->held;
            }

            /**
             * @brief Returns whether the region is/was clicked (and the click state is consumed).
             * @return Whether the region is/was clicked.
             */
            inline bool ConsumeClicked() {
                const auto clicked = this->clicked;
                this->clicked = false;
                return clicked;
            }
    };

}
