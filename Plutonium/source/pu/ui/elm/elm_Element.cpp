#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Layout.hpp>

namespace pu::ui::elm {

    i32 Element::GetProcessedX() {
        auto x = this->GetX();
        if(this->parent_container != nullptr) {
            auto container = reinterpret_cast<Container*>(this->parent_container);
            x += container->GetX();

            if(this->h_align == HorizontalAlign::Center) {
                x = container->GetX() + ((container->GetWidth() - this->GetWidth()) / 2);
            }
            else if(this->h_align == HorizontalAlign::Right) {
                x = container->GetX() + (container->GetWidth() - this->GetWidth());
            }
        }
        return x;
    }

    i32 Element::GetProcessedY() {
        auto y = this->GetY();
        if(this->parent_container != nullptr) {
            auto container = reinterpret_cast<Container*>(this->parent_container);
            y += container->GetY();

            if(this->v_align == VerticalAlign::Center) {
                y = container->GetY() + ((container->GetHeight() - this->GetHeight()) / 2);
            }
            else if(this->v_align == VerticalAlign::Down) {
                y = container->GetY() + (container->GetHeight() - this->GetHeight());
            }
        }
        return y;
    }

}