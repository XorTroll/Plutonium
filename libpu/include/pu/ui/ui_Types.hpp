/**
 * Plutonium library
 * @file ui_Types.hpp
 * @brief Basic UI types header.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/pu_Include.hpp>
#include <pu/util/util_Hex.hpp>

namespace pu::ui {

    /**
     * @brief Enum containing the default font sizes used by Plutonium components.
     */
    enum class DefaultFontSize : u32 {
        Small,
        Medium,
        MediumLarge,
        Large,

        Count
    };
    
    /**
     * @brief Array containing the default font size values used by Plutonium components, for all DefaultFontSize values.
     */
    constexpr u32 DefaultFontSizes[static_cast<u32>(DefaultFontSize::Count)] = { 27, 30, 37, 45 };

    /**
     * @brief Makes a default font name with the specified font size.
     * @param font_size Font size to use.
     * @return Default font name.
     */
    inline std::string MakeDefaultFontName(const u32 font_size) {
        return "DefaultFont@" + std::to_string(font_size);
    }

    /**
     * @brief Gets the default font size value for the specified DefaultFontSize.
     * @param kind DefaultFontSize to get the value from.
     * @return Default font size value.
     */
    inline constexpr u32 GetDefaultFontSize(const DefaultFontSize kind) {
        return DefaultFontSizes[static_cast<u32>(kind)];
    }

    /**
     * @brief Gets the default font name for the specified DefaultFontSize.
     * @param kind DefaultFontSize to get the font name from.
     * @return Default font name.
     */
    inline std::string GetDefaultFont(const DefaultFontSize kind) {
        return MakeDefaultFontName(GetDefaultFontSize(kind));
    }

    /**
     * @brief Type encoding a RGBA-8888 color.
     */
    struct Color {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        /**
         * @brief Creates a new Color with the specified values.
         * @param r Red value.
         * @param g Green value.
         * @param b Blue value.
         * @param a Alpha value.
         */
        constexpr Color(const u8 r, const u8 g, const u8 b, const u8 a) : r(r), g(g), b(b), a(a) {}

        /**
         * @brief Creates a new Color with all RGB values set to 0 but full alpha by default (black color).
         */
        constexpr Color() : r(0), g(0), b(0), a(0xFF) {}

        /**
         * @brief Creates a new Color from a constant RGB hexadecimal string ("#RRGGBB" format).
         * @param str_clr Hexadecimal string to create the Color from.
         * @return Created Color.
         */
        NX_CONSTEXPR Color FromConstHexRGB(const char *str) {
            // Expected format: "#RRGGBB"
            return Color {
                util::ParseHexByte(str[1], str[2]),
                util::ParseHexByte(str[3], str[4]),
                util::ParseHexByte(str[5], str[6]),
                0xFF
            };
        }

        /**
         * @brief Creates a new Color from a constant RGBA hexadecimal string ("#RRGGBBAA" format).
         * @param str_clr Hexadecimal string to create the Color from.
         * @return Created Color.
         */
        NX_CONSTEXPR Color FromConstHexRGBA(const char *str) {
            // Expected format: "#RRGGBBAA"
            return Color {
                util::ParseHexByte(str[1], str[2]),
                util::ParseHexByte(str[3], str[4]),
                util::ParseHexByte(str[5], str[6]),
                util::ParseHexByte(str[7], str[8])
            };
        }

        /**
         * @brief Creates a new Color from a run-time hexadecimal string ("#RRGGBB" or "#RRGGBBAA" format).
         * @param str Hexadecimal string to create the Color from.
         * @return Created Color.
         * @note This function is not constexpr, as it needs to check the string length and format at runtime. Please use the FromConstHexRGB or FromConstHexRGBA functions when defining Color at compile time.
         */
        static Color FromHex(const std::string &str);

        /**
         * @brief Creates a new Color with this Color's RGB values and the specified alpha value.
         * @param a Alpha value to set.
         * @return Created Color.
         */
        inline Color WithAlpha(const u8 a) const {
            return { this->r, this->g, this->b, a };
        }
    };

    /**
     * @brief Helper function to check whether a rectangle subregion is inside a rectangle region.
     * @param sub_x X coordinate of the subregion.
     * @param sub_y Y coordinate of the subregion.
     * @param sub_w Width of the subregion.
     * @param sub_h Height of the subregion.
     * @param region_x X coordinate of the region.
     * @param region_y Y coordinate of the region.
     * @param region_w Width of the region.
     * @param region_h Height of the region.
     * @return Whether the subregion is inside the region.
     */
    static inline constexpr bool SubregionInsideRegion(const s32 sub_x, const s32 sub_y, const s32 sub_w, const s32 sub_h, const s32 region_x, const s32 region_y, const s32 region_w, const s32 region_h) {
        return (sub_x >= region_x) && ((sub_x + sub_w) <= (region_x + region_w)) && (sub_y >= region_y) && ((sub_y + sub_h) <= (region_y + region_h));
    }
    
    /**
     * @brief Helper function to check whether a touch point hits a rectangle region.
     * @param touch_x X coordinate of the touch point.
     * @param touch_y Y coordinate of the touch point.
     * @param region_x X coordinate of the region.
     * @param region_y Y coordinate of the region.
     * @param region_w Width of the region.
     * @param region_h Height of the region.
     * @return Whether the touch point hits the region.
     */
    static inline constexpr bool TouchHitsRegion(const s32 touch_x, const s32 touch_y, const s32 region_x, const s32 region_y, const s32 region_w, const s32 region_h) {
        return (touch_x >= region_x) && (touch_x < (region_x + region_w)) && (touch_y >= region_y) && (touch_y < (region_y + region_h));
    }

    /**
     * @brief Input key value used internally by Plutonium to represent the presence of a touch input.
     */
    constexpr u64 TouchPseudoKey = 1 << 29;

    /**
     * @brief Type encoding a touch point.
     */
    struct TouchPoint {
        s32 x;
        s32 y;
        bool is_scrolling;

        /**
         * @brief Creates a new, invalid TouchPoint (with both coordinates set to -1).
         */
        constexpr TouchPoint() : x(-1), y(-1), is_scrolling(false) {}

        /**
         * @brief Creates a new TouchPoint with the specified coordinates.
         * @param x X coordinate.
         * @param y Y coordinate.
         */
        constexpr TouchPoint(const u32 x, const u32 y) : x(x), y(y), is_scrolling(false) {}

        /**
         * @brief Checks whether this TouchPoint is not valid (both coordinates are less than 0).
         * @return Whether this TouchPoint is invalid/empty.
         */
        inline constexpr bool IsEmpty() const {
            return (this->x < 0) && (this->y < 0);
        }

        /**
         * @brief Checks whether this TouchPoint hits a rectangle region.
         * @param region_x X coordinate of the region.
         * @param region_y Y coordinate of the region.
         * @param region_w Width of the region.
         * @param region_h Height of the region.
         * @return Whether this TouchPoint hits the region.
         */
        inline constexpr bool HitsRegion(const s32 region_x, const s32 region_y, const s32 region_w, const s32 region_h) const {
            if(this->IsEmpty()) {
                return false;
            }
            
            return TouchHitsRegion(this->x, this->y, region_x, region_y, region_w, region_h);
        }
    };

}
