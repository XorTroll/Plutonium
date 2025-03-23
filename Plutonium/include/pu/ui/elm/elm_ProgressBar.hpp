/**
 * Plutonium library
 * @file elm_ProgressBar.hpp
 * @brief Contains an element for creating UI progress bars.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for creating UI progress bars.
     */
    class ProgressBar : public Element {
        public:
            static constexpr Color DefaultProgressColor = { 139, 195, 74, 255 };
            static constexpr Color DefaultBackgroundColor = { 140, 140, 140, 255 };

            static constexpr double DefaultHeightRadiusFactor = 0.333;

        private:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            double val;
            double max_val;
            u32 radius;
            Color progress_clr;
            Color bg_clr;

        public:
            /**
             * @brief Creates a new instance of a ProgressBar.
             * @param x X position of the ProgressBar.
             * @param y Y position of the ProgressBar.
             * @param width Width of the ProgressBar.
             * @param height Height of the ProgressBar.
             * @param max_val Maximum value of the ProgressBar.
             */
            ProgressBar(const i32 x, const i32 y, const i32 width, const i32 height, const double max_val);
            PU_SMART_CTOR(ProgressBar)

            inline i32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the ProgressBar.
             * @param x New X position.
             */
            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the ProgressBar.
             * @param y New Y position.
             */
            inline void SetY(const i32 y) {
                this->y = y;
            }

            inline i32 GetWidth() override {
                return this->w;
            }

            /**
             * @brief Sets the width of the ProgressBar.
             * @param width New width.
             */
            inline void SetWidth(const i32 width) {
                this->w = width;
            }

            inline i32 GetHeight() override {
                return this->h;
            }

            /**
             * @brief Sets the height of the ProgressBar.
             * @param height New height.
             */
            inline void SetHeight(const i32 height) {
                this->h = height;
            }

            PU_CLASS_POD_GETSET(Radius, radius, u32)
            PU_CLASS_POD_GETSET(ProgressColor, progress_clr, Color)
            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)

            PU_CLASS_POD_GET(Progress, val, double)

            /**
             * @brief Sets the progress of the ProgressBar.
             * @param progress Progress to set, with respect to the maximum value.
             */
            void SetProgress(const double progress);
            
            /**
             * @brief Increments the progress of the ProgressBar.
             * @param extra_progress Extra progress to add, with respect to the maximum value.
             */
            inline void IncrementProgress(const double extra_progress) {
                this->SetProgress(this->val + extra_progress);
            }
            
            /**
             * @brief Decrements the progress of the ProgressBar.
             * @param extra_progress Extra progress to subtract, with respect to the maximum value.
             */
            inline void DecrementProgress(const double extra_progress) {
                this->SetProgress(this->val - extra_progress);
            }

            PU_CLASS_POD_GETSET(MaxProgress, max_val, double)

            /**
             * @brief Fills the ProgressBar up to the maximum value.
             */
            inline void FillProgress() {
                this->SetProgress(this->max_val);
            }

            /**
             * @brief Clears the ProgressBar progress.
             */
            inline void ClearProgress() {
                this->SetProgress(0);
            }

            /**
             * @brief Gets whether the ProgressBar is completed.
             * @return Whether the ProgressBar is completed, that is, the progress is equal to the maximum value.
             */
            inline bool IsCompleted() {
                return this->val == this->max_val;
            }

            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}
