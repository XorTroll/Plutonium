#include <pu/ui/extras/extras_Toast.hpp>

namespace pu::ui::extras
{
    Toast::Toast(String Text, String font_name, Color TextColor, Color BaseColor) : Overlay(0, 550, 0, 0, BaseColor)
    {
        this->text = elm::TextBlock::New(0, 0, Text);
        this->text->SetFont(font_name);
        this->text->SetColor(TextColor);
        this->text->SetHorizontalAlign(pu::ui::elm::HorizontalAlign::Center);
        this->text->SetVerticalAlign(pu::ui::elm::VerticalAlign::Center);
        i32 textw = this->text->GetTextWidth();
        i32 texth = this->text->GetTextHeight();
        i32 toastw = textw + (texth * 4);
        i32 toasth = texth * 3;
        this->SetX((1280 - toastw) / 2);
        this->SetWidth(toastw);
        this->SetHeight(toasth);
        this->Add(this->text);
    }

    void Toast::SetText(String Text)
    {
        this->text->SetText(Text);
        i32 textw = this->text->GetTextWidth();
        i32 texth = this->text->GetTextHeight();
        i32 toastw = textw + (texth * 4);
        i32 toasth = texth * 3;
        this->SetX((1280 - toastw) / 2);
        this->SetWidth(toastw);
        this->SetHeight(toasth);
    }

    void Toast::OnPreRender(render::Renderer::Ref &Drawer)
    {
        Drawer->SetBaseRenderAlpha(200);
    }

    void Toast::OnPostRender(render::Renderer::Ref &Drawer)
    {
        Drawer->UnsetBaseRenderAlpha();
    }
}