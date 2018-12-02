#include <pn/fw/ProgressBar.hpp>

namespace pn::fw
{
    ProgressBar::ProgressBar(u32 X, u32 Y, u32 Width, u32 Height, draw::Color Color)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->h = Height;
        this->clr = Color;
    }

    u32 ProgressBar::GetX()
    {
        return this->x;
    }

    void ProgressBar::SetX(u32 X)
    {
        this->x = X;
    }

    u32 ProgressBar::GetY()
    {
        return this->y;
    }

    void ProgressBar::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 ProgressBar::GetWidth()
    {
        return this->w;
    }

    void ProgressBar::SetWidth(u32 Width)
    {
        this->w = Width;
    }

    u32 ProgressBar::GetHeight()
    {
        return this->h;
    }

    void ProgressBar::SetHeight(u32 Height)
    {
        this->h = Height;
    }

    draw::Color ProgressBar::GetColor()
    {
        return this->clr;
    }

    void ProgressBar::SetColor(draw::Color Color)
    {
        this->clr = Color;
    }

    u8 ProgressBar::GetProgress()
    {
        return this->perc;
    }

    void ProgressBar::SetProgress(u8 Percentage)
    {
        if(Percentage >= 100) this->perc = 100;
        else this->perc = Percentage;
    }

    void ProgressBar::IncrementProgress(u8 Percentage)
    {
        u8 res = (this->perc + Percentage);
        if(res >= 100) this->perc = 100;
        else this->perc = res;
    }

    void ProgressBar::DecrementProgress(u8 Percentage)
    {
        this->perc -= Percentage;
    }

    void ProgressBar::FillProgress()
    {
        this->perc = 100;
    }

    void ProgressBar::ClearProgress()
    {
        this->perc = 0;
    }

    bool ProgressBar::IsCompleted()
    {
        return (this->perc >= 100);
    }

    void ProgressBar::OnRender(render::Renderer *Drawer)
    {
        Drawer->DrawRectangleFill({ 150, 150, 150, 255 }, this->x, this->y, this->w, this->h);
        u32 pcw = ((this->perc * this->w) / 100);
        Drawer->DrawRectangleFill(this->clr, this->x, this->y, pcw, this->h);
    }

    void ProgressBar::OnInput(u64 Input)
    {
    }
}