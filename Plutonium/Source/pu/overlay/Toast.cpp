#include <pu/overlay/Toast.hpp>

namespace pu::overlay
{
    Toast::Toast(std::string Text, u32 FontSize, draw::Color TextColor, draw::Color BaseColor) : Overlay(0, 550, 0, 0, BaseColor)
    {
        this->text = new element::TextBlock(0, 0, Text, FontSize);
        this->text->SetColor(TextColor);
        u32 textw = this->text->GetTextWidth();
        u32 texth = this->text->GetTextHeight();
        u32 toastw = textw + (texth * 4);
        u32 toasth = texth * 3;
        this->SetX((1280 - toastw) / 2);
        this->SetWidth(toastw);
        this->SetHeight(toasth);
        u32 textx = texth * 2;
        u32 texty = texth;
        this->text->SetX(textx);
        this->text->SetY(texty);
        this->Add(this->text);
    }

    void Toast::SetText(std::string Text)
    {
        this->text->SetText(Text);
        u32 textw = this->text->GetTextWidth();
        u32 texth = this->text->GetTextHeight();
        u32 toastw = textw + (texth * 4);
        u32 toasth = texth * 3;
        this->SetX((1280 - toastw) / 2);
        this->SetWidth(toastw);
        this->SetHeight(toasth);
        u32 textx = texth * 2;
        u32 texty = texth;
        this->text->SetX(textx);
        this->text->SetY(texty);
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