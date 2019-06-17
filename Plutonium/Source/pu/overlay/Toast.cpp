#include <pu/overlay/Toast.hpp>

namespace pu::overlay
{
    Toast::Toast(std::string Text, s32 FontSize, draw::Color TextColor, draw::Color BaseColor) : Overlay(0, 550, 0, 0, BaseColor)
    {
        this->text = new element::TextBlock(0, 0, Text, FontSize);
        this->text->SetColor(TextColor);
        this->text->SetHorizontalAlign(pu::element::HorizontalAlign::Center);
        this->text->SetVerticalAlign(pu::element::VerticalAlign::Center);
        s32 textw = this->text->GetTextWidth();
        s32 texth = this->text->GetTextHeight();
        s32 toastw = textw + (texth * 4);
        s32 toasth = texth * 3;
        this->SetX((1280 - toastw) / 2);
        this->SetWidth(toastw);
        this->SetHeight(toasth);
        this->Add(this->text);
    }

    void Toast::SetText(std::string Text)
    {
        this->text->SetText(Text);
        s32 textw = this->text->GetTextWidth();
        s32 texth = this->text->GetTextHeight();
        s32 toastw = textw + (texth * 4);
        s32 toasth = texth * 3;
        this->SetX((1280 - toastw) / 2);
        this->SetWidth(toastw);
        this->SetHeight(toasth);
    }

    void Toast::OnPreRender(render::Renderer *Drawer)
    {
        Drawer->SetBaseRenderAlpha(200);
    }

    void Toast::OnPostRender(render::Renderer *Drawer)
    {
        Drawer->UnsetBaseRenderAlpha();
    }
}