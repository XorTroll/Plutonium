
/*

    Plutonium library

    @file ProgressBar.hpp
    @brief A ProgressBar is an Element which represents a progress (a percentage) by filling a bar.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    class ProgressBar : public Element
    {
        public:
            ProgressBar(i32 X, i32 Y, i32 Width, i32 Height, double MaxValue);
            PU_SMART_CTOR(ProgressBar)

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            void SetWidth(i32 Width);
            i32 GetHeight();
            void SetHeight(i32 Height);
            Color GetColor();
            void SetColor(Color Color);
            Color GetProgressColor();
            void SetProgressColor(Color Color);
            double GetProgress();
            void SetProgress(double Progress);
            void IncrementProgress(double Progress);
            void DecrementProgress(double Progress);
            void SetMaxValue(double Max);
            double GetMaxValue();
            void FillProgress();
            void ClearProgress();
            bool IsCompleted();
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            double val;
            double maxval;
            Color clr;
            Color oclr;
    };
}