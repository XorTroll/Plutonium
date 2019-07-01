
/*

    Plutonium library

    @file ui_Color.hpp
    @brief A Color is used for basic RGBA drawing in all kind of elements.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <switch.h>
#include <string>

namespace pu::ui
{
    struct Color
    {
        Color();
        Color(u8 R, u8 G, u8 B, u8 A);
        u8 R;
        u8 G;
        u8 B;
        u8 A;

        static Color FromHex(std::string HexFmt);
    };
}