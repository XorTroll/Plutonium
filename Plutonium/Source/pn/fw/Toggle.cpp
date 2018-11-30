#include <pn/fw/Toggle.hpp>

namespace pn::fw
{
    Toggle::Toggle(u32 X, u32 Y, std::string Content, draw::Color General)
    {
        this->x = x;
        this->y = y;
        this->cnt = Content;
        this->on = General;
        this->genclr = true;
    }

    Toggle::Toggle(u32 X, u32 Y, std::string Content, draw::Color On, draw::Color Off)
    {
        
    }

    u32 Toggle::GetX()
    {

    }

    void Toggle::SetX(u32 X)
    {
        this->x = X;
    }

    u32 Toggle::GetY()
    {
        return this->y;
    }

    void Toggle::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 Toggle::GetWidth()
    {
        return 0;
    }

    u32 Toggle::GetHeight()
    {
        return 0;
    }

    std::string Toggle::GetContent()
    {

    }

    void Toggle::SetContent(std::string Content)
    {

    }

    draw::Font Toggle::GetFont()
    {

    }

    void Toggle::SetFont(draw::Font Font)
    {

    }

    u32 Toggle::GetFontSize()
    {

    }

    void Toggle::SetFontSize(u32 Size)
    {

    }

    draw::Color Toggle::GetColor()
    {

    }

    void Toggle::SetColor(draw::Color General)
    {

    }

    draw::Color Toggle::GetOnColor()
    {

    }

    void Toggle::SetOnColor(draw::Color On)
    {

    }

    draw::Color Toggle::GetOffColor()
    {

    }

    void Toggle::SetOffColor(draw::Color Off)
    {

    }

    void Toggle::OnRender(render::Renderer *Drawer)
    {

    }

    void Toggle::OnInput(u64 Input)
    {

    }
}