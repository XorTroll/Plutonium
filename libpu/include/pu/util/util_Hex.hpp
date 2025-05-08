/**
 * Plutonium library
 * @file util_Hex.hpp
 * @brief Header for hex/byte utilities.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/pu_Include.hpp>

namespace pu::util {

    /**
     * @brief Converts a hex character to its numeric value (like '0' -> 0, 'A' -> 10, 'F' -> 15).
     * @param c The hex character to convert.
     * @return The numeric value of the hex character.
     */
    NX_CONSTEXPR u8 HexCharToNumeric(const char c) {
        return (c >= '0' && c <= '9') ? c - '0' :
            (c >= 'A' && c <= 'F') ? c - 'A' + 10 :
            (c >= 'a' && c <= 'f') ? c - 'a' + 10 : 0;
    }
    
    /**
     * @brief Converts two hex characters to a byte (like '1', '0' -> 16, 'F', 'F' -> 255).
     * @param hi The high nibble hex character.
     * @param lo The low nibble hex character.
     * @return The byte value represented by the two hex characters.
     */
    NX_CONSTEXPR u8 ParseHexByte(const char hi, const char lo) {
        return (HexCharToNumeric(hi) << 4) | HexCharToNumeric(lo);
    }

    /**
     * @brief Gets whether a character is a valid hex character (0-9, A-F, a-f).
     * @param c The character to check.
     * @return True if the character is a valid hex character, false otherwise.
     */
    NX_CONSTEXPR bool IsHexChar(const char c) {
        return (c >= '0' && c <= '9') ||
               (c >= 'A' && c <= 'F') ||
               (c >= 'a' && c <= 'f');
    }

}
