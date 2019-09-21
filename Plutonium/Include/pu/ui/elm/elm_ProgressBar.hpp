
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
            ProgressBar(s32 X, s32 Y, s32 Width, s32 Height, double MaxValue);
            PU_SMART_CTOR(ProgressBar)

            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            void SetWidth(s32 Width);
            s32 GetHeight();
            void SetHeight(s32 Height);
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
            void OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            double val;
            double maxval;
            Color clr;
            Color oclr;
    };
}