#include <pu/ui/elm/elm_ProgressBar.hpp>

namespace pu::ui::elm
{
    ProgressBar::ProgressBar(i32 X, i32 Y, i32 Width, i32 Height, double MaxValue) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->clr = { 140, 140, 140, 255 };
        this->oclr = { 139, 195, 74, 255 };
        this->val = 0.0f;
        this->maxval = MaxValue;
    }

    i32 ProgressBar::GetX()
    {
        return this->x;
    }

    void ProgressBar::SetX(i32 X)
    {
        this->x = X;
    }

    i32 ProgressBar::GetY()
    {
        return this->y;
    }

    void ProgressBar::SetY(i32 Y)
    {
        this->y = Y;
    }

    i32 ProgressBar::GetWidth()
    {
        return this->w;
    }

    void ProgressBar::SetWidth(i32 Width)
    {
        this->w = Width;
    }

    i32 ProgressBar::GetHeight()
    {
        return this->h;
    }

    void ProgressBar::SetHeight(i32 Height)
    {
        this->h = Height;
    }

    Color ProgressBar::GetColor()
    {
        return this->clr;
    }

    void ProgressBar::SetColor(Color Color)
    {
        this->clr = Color;
    }

    Color ProgressBar::GetProgressColor()
    {
        return this->oclr;
    }

    void ProgressBar::SetProgressColor(Color Color)
    {
        this->oclr = Color;
    }

    double ProgressBar::GetProgress()
    {
        return this->val;
    }

    void ProgressBar::SetProgress(double Progress)
    {
        if(Progress >= this->maxval) this->FillProgress();
        else this->val = Progress;
    }

    void ProgressBar::IncrementProgress(double Progress)
    {
        double res = (this->val + Progress);
        if(res >= this->maxval) this->FillProgress();
        else this->val = res;
    }

    void ProgressBar::DecrementProgress(double Progress)
    {
        if(this->val > Progress) this->ClearProgress();
        else this->val -= Progress;
    }

    void ProgressBar::SetMaxValue(double Max)
    {
        this->maxval = Max;
    }

    double ProgressBar::GetMaxValue()
    {
        return this->maxval;
    }

    void ProgressBar::FillProgress()
    {
        this->val = this->maxval;
    }

    void ProgressBar::ClearProgress()
    {
        this->val = 0;
    }

    bool ProgressBar::IsCompleted()
    {
        return (this->val >= this->maxval);
    }

    void ProgressBar::OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y)
    {
        i32 rdx = X;
        i32 rdy = Y;
        i32 pcw = (i32)((this->val / this->maxval) * (double)this->w);
        i32 rad = (this->h / 3);
        Drawer->RenderRoundedRectangleFill(this->clr, rdx, rdy, this->w, this->h, rad);
        Drawer->RenderRoundedRectangleFill(this->oclr, rdx, rdy, std::max(this->h, pcw), this->h, rad);
    }

    void ProgressBar::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
    }
}