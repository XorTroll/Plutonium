
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
            bool operator==(const char *C_UTF8);
            bool operator!=(const char *C_UTF8);
            String operator+(const char *C_UTF8);
            const char *AsCUTF8();

            String(const char16_t *C_UTF16);
            bool operator==(const char16_t *C_UTF16);
            bool operator!=(const char16_t *C_UTF16);
            String operator+(const char16_t *C_UTF16);
            const char16_t *AsCUTF16();

            String(std::string UTF8);
            bool operator==(std::string &UTF8);
            bool operator!=(std::string &UTF8);
            String operator+(std::string &UTF8);
            std::string AsUTF8();

            String(std::u16string UTF16);
            bool operator==(std::u16string &UTF16);
            bool operator!=(std::u16string &UTF16);
            String operator+(std::u16string &UTF16);
            std::u16string AsUTF16();

            bool operator==(String &Str);
            bool operator!=(String &Str);
            String operator+(String &Str);

            bool StartsWith(String Str);
            bool IsEmpty();
            bool HasAny();
            size_t GetLength();
            pu::String Substring(size_t Index, size_t Length);

            // C++ string compatibility
            
            bool empty();
            size_t length();
            pu::String substr(size_t Offset, size_t Length = std::u16string::npos);
        private:
            std::u16string base;
    };
}