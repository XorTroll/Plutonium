#include <pu/element/Element.hpp>

namespace pu::element
{
    Element::Element()
    {
        this->visible = true;
    }

    Element::~Element()
    {
    }

    bool Element::IsVisible()
    {
        return this->visible;
    }

    void Element::SetVisible(bool Visible)
    {
        this->visible = Visible;
    }
}