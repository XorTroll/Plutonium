/**
 * Plutonium library
 * @file elm_ProgressBar.hpp
 * @brief Contains an element for creating UI progress bars.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui::elm {

    /**
     * @brief Element for creating UI progress bars.
     */
    class ProgressBar : public Element {
        private:
            s32 x;
            s32 y;
            s32 width;
            s32 height;
            u32 radius;
            bool movable;
            double val;
            double max_val;
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
             * @note The ProgressBar is not movable by default.
             */
            ProgressBar(const s32 x, const s32 y, const s32 width, const s32 height, const double max_val) : Element(), x(x), y(y), width(width), height(height), radius(0), movable(false), val(0), max_val(max_val), progress_clr(GetStyle()->GetProgressBarProgressColor()), bg_clr(GetStyle()->GetProgressBarBackgroundColor()) {}
            PU_SMART_CTOR(ProgressBar)

            // Only D-pad left/right to move focus, while joysticks move the progress bar value

            inline u64 GetFocusLeftChangeKeysDown() override {
                return HidNpadButton_Left;
            }
            inline u64 GetFocusRightChangeKeysDown() override {
                return HidNpadButton_Right;
            }

            inline u64 GetFocusUpChangeKeysHeld() override {
                return 0;
            }
            inline u64 GetFocusDownChangeKeysHeld() override {
                return 0;
            }
            inline u64 GetFocusLeftChangeKeysHeld() override {
                return 0;
            }
            inline u64 GetFocusRightChangeKeysHeld() override {
                return 0;
            }

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the ProgressBar.
             * @param x New X position.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the ProgressBar.
             * @param y New Y position.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            inline s32 GetWidth() override {
                return this->width;
            }

            /**
             * @brief Sets the width of the ProgressBar.
             * @param width New width.
             */
            inline void SetWidth(const s32 width) {
                this->width = width;
            }

            inline s32 GetHeight() override {
                return this->height;
            }

            /**
             * @brief Sets the height of the ProgressBar.
             * @param height New height.
             */
            inline void SetHeight(const s32 height) {
                this->height = height;
            }

            PU_CLASS_POD_GETSET(Radius, radius, u32)
            PU_CLASS_POD_GETSET(ProgressColor, progress_clr, Color)
            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)
            PU_CLASS_POD_GETSET(Movable, movable, bool)

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

            void OnRender(render::Renderer::Ref &drawer) override;
            bool OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };

}
