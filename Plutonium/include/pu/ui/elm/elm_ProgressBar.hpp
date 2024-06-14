
/*

    Plutonium library

    @file ProgressBar.hpp
    @brief A ProgressBar is an Element which represents a progress (a percentage) by filling a bar.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

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
            ProgressBar(const i32 x, const i32 y, const i32 width, const i32 height, const double max_val);
            PU_SMART_CTOR(ProgressBar)

            inline i32 GetX() override {
                return this->x;
            }

            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            inline void SetY(const i32 y) {
                this->y = y;
            }

            inline i32 GetWidth() override {
                return this->w;
            }

            inline void SetWidth(const i32 width) {
                this->w = width;
            }

            inline i32 GetHeight() override {
                return this->h;
            }

            inline void SetHeight(const i32 height) {
                this->h = height;
            }

            PU_CLASS_POD_GETSET(Radius, radius, u32)
            PU_CLASS_POD_GETSET(ProgressColor, progress_clr, Color)
            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)

            PU_CLASS_POD_GET(Progress, val, double)

            void SetProgress(const double progress);
            
            inline void IncrementProgress(const double extra_progress) {
                this->SetProgress(this->val + extra_progress);
            }
            
            inline void DecrementProgress(const double extra_progress) {
                this->SetProgress(this->val - extra_progress);
            }

            PU_CLASS_POD_GETSET(MaxProgress, max_val, double)

            inline void FillProgress() {
                this->SetProgress(this->max_val);
            }

            inline void ClearProgress() {
                this->SetProgress(0);
            }

            inline bool IsCompleted() {
                return this->val == this->max_val;
            }

            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}