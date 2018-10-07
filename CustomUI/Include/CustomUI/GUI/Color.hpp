
#pragma once
#include "../Common/Include.hpp"

namespace CustomUI
{
    namespace GUI
    {
        struct Color
        {
            Color();
            Color(u8 Red, u8 Green, u8 Blue);
            Color(u8 Red, u8 Green, u8 Blue, u8 Alpha);
            u8 Red;
            u8 Green;
            u8 Blue;
            u8 Alpha;
        };
    }
}