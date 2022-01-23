
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

        private:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            double val;
            double max_val;
            Color progress_clr;
            Color bg_clr;

        public:
            ProgressBar(const i32 x, const i32 y, const i32 width, const i32 height, const double max_val) : Element(), x(x), y(y), w(width), h(height), val(0), max_val(max_val), progress_clr(DefaultProgressColor), bg_clr(DefaultBackgroundColor) {}
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

            inline Color GetProgressColor() {
                return this->progress_clr;
            }

            inline void SetProgressColor(const Color progress_clr) {
                this->progress_clr = progress_clr;
            }

            inline Color GetBackgroundColor() {
                return this->bg_clr;
            }

            inline void SetBackgroundColor(const Color bg_clr) {
                this->bg_clr = bg_clr;
            }

            inline double GetProgress() {
                return this->val;
            }

            void SetProgress(const double progress);
            
            inline void IncrementProgress(const double extra_progress) {
                this->SetProgress(this->val + extra_progress);
            }
            
            inline void DecrementProgress(const double extra_progress) {
                this->SetProgress(this->val - extra_progress);
            }

            inline void SetMaxProgress(const double max_progress) {
                this->max_val = max_progress;
            }

            inline double GetMaxProgress() {
                return this->max_val;
            }

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