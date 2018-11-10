
#pragma once
#include <pn/horizon/Page.hpp>
#include <pn/Application.hpp>

namespace pn::horizon
{
    class HorizonApplication : public Application
    {
        public:
            void AddPage(Page *NewPage);
            void ClearPages();
    };
}