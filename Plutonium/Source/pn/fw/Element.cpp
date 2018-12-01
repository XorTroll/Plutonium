#include <pn/fw/Element.hpp>

namespace pn::fw
{
    Element::Element()
    {
        this->visible = true;
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