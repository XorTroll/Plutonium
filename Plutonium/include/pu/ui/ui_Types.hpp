
/*

    Plutonium library

    @file ui_Types.hpp
    @brief Several basic types helpful for UI and rendering, such as Color
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_Macros.hpp>
#include <string>
#include <array>

namespace pu::ui
{
    // Default font sizes Plutonium components use by default
    static inline constexpr std::array<u32, 4> DefaultFontSizes = { 18, 20, 25, 30 };

    struct Color
    {
        u8 R;
        u8 G;
        u8 B;
        u8 A;

        constexpr Color() : R(0), G(0), B(0), A(0xFF) {}

        constexpr Color(u8 R, u8 G, u8 B, u8 A) : R(R), G(G), B(B), A(A) {}

        static Color FromHex(std::string HexFmt);
    };

    struct Touch
    {
        i32 X;
        i32 Y;

        inline constexpr bool IsEmpty()
        {
            if(X < 0)
            {
                if(Y < 0)
                {
                    return true;
                }
            }
            return false;
        }

        static const Touch Empty;
    };

    inline constexpr const Touch Touch::Empty = { -1, -1 };
}