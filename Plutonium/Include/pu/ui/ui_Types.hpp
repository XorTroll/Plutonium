
/*

    Plutonium library

    @file ui_Types.hpp
    @brief Several basic types helpful for UI and rendering, such as Color
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

    struct Touch
    {
        s32 X;
        s32 Y;

        bool IsEmpty();

        static const Touch Empty;
    };

    inline constexpr const Touch Touch::Empty = { -1, -1 };
}