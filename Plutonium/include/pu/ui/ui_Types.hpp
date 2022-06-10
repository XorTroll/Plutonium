
/*

    Plutonium library

    @file ui_Types.hpp
    @brief Several basic types helpful for UI and rendering, such as Color
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_Include.hpp>

namespace pu::ui {

    // Font sizes Plutonium components use by default

    enum class DefaultFontSize : u32 {
        Small,
        Medium,
        MediumLarge,
        Large,

        Count
    };
    
    constexpr u32 DefaultFontSizes[static_cast<u32>(DefaultFontSize::Count)] = { 18, 20, 25, 30 };

    inline std::string MakeDefaultFontName(const u32 font_size) {
        return "DefaultFont@" + std::to_string(font_size);
    }

    inline constexpr u32 GetDefaultFontSize(const DefaultFontSize kind) {
        return DefaultFontSizes[static_cast<u32>(kind)];
    }

    inline std::string GetDefaultFont(const DefaultFontSize kind) {
        return MakeDefaultFontName(GetDefaultFontSize(kind));
    }

    struct Color {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        constexpr Color() : r(0), g(0), b(0), a(0xFF) {}
        constexpr Color(const u8 r, const u8 g, const u8 b, const u8 a) : r(r), g(g), b(b), a(a) {}

        static Color FromHex(const std::string &str_clr);
    };

    static inline constexpr bool TouchHitsRegion(const i32 touch_x, const i32 touch_y, const i32 region_x, const i32 region_y, const i32 region_w, const i32 region_h) {
        return (touch_x >= region_x) && (touch_x < (region_x + region_w)) && (touch_y >= region_y) && (touch_y < (region_y + region_h));
    }

    constexpr u64 TouchPseudoKey = 1 << 29;

    struct TouchPoint {
        i32 x;
        i32 y;

        constexpr TouchPoint() : x(-1), y(-1) {}
        constexpr TouchPoint(const u32 x, const u32 y) : x(x), y(y) {}

        inline constexpr bool IsEmpty() const {
            return (this->x < 0) && (this->y < 0);
        }

        inline constexpr bool HitsRegion(const i32 region_x, const i32 region_y, const i32 region_w, const i32 region_h) const {
            if(this->IsEmpty()) {
                return false;
            }
            
            return TouchHitsRegion(this->x, this->y, region_x, region_y, region_w, region_h);
        }
    };

}