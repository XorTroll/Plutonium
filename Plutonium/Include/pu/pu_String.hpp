
/*

    Plutonium library

    @file pu_String.hpp
    @brief A custom string class to support UTF16 and UTF8 -> UTF16 conversion
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <string>

namespace pu
{
    class String
    {
        public:
            String();
            String(const char *C_UTF8);
            String(const char16_t *C_UTF16);
            String(std::string UTF8);
            String(std::u16string UTF16);
            std::string AsUTF8();
            std::u16string AsUTF16();
        private:
            std::u16string base;
    };
}