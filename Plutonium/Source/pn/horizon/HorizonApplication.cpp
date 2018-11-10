#include <pn/horizon/HorizonApplication.hpp>

namespace pn::horizon
{
    void HorizonApplication::AddPage(Page *NewPage)
    {
        this->AddChild(NewPage);
    }

    void HorizonApplication::ClearPages()
    {
        this->ClearChildren();
    }
}