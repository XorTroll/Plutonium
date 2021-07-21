
/*

    Plutonium library

    @file pu_String.hpp
    @brief A custom string class to support UTF16 and UTF8 -> UTF16 conversion
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <string>
#include <switch.h>
#include <pu/pu_Macros.hpp>

namespace pu
{
    class String
    {
        using iterator = std::u16string::iterator;

        public:
            String();
            static const size_t npos;

            String(const char *C_UTF8);
            bool operator==(const char *C_UTF8);
            bool operator!=(const char *C_UTF8);
            String operator+=(const char *C_UTF8);

            String(const char16_t *C_UTF16);
            bool operator==(const char16_t *C_UTF16);
            bool operator!=(const char16_t *C_UTF16);
            String operator+=(const char16_t *C_UTF16);

            String(std::string UTF8);
            bool operator==(std::string UTF8);
            bool operator!=(std::string UTF8);
            String operator+=(std::string UTF8);
            std::string AsUTF8();

            String(std::u16string UTF16);
            bool operator==(std::u16string UTF16);
            bool operator!=(std::u16string UTF16);
            String operator+=(std::u16string UTF16);
            std::u16string AsUTF16();

            bool operator==(String Str);
            bool operator!=(String Str);
            String operator+=(String Str);

            bool StartsWith(String Str);
            bool IsEmpty();
            bool HasAny();
            size_t GetLength();
            String Substring(size_t Index, size_t Length);

            // C++ string compatibility
            
            bool empty();
            size_t length();
            String substr(size_t Offset, size_t Length = npos);
            size_t find_first_of(String Str, size_t Position = 0);
            size_t find_last_of(String Str, size_t Position = npos);
            void erase(size_t Offset, size_t Length = npos);
            iterator begin();
            iterator end();
            size_t find(String Str, size_t Position = 0);
            String replace(size_t Position, size_t Length, String Str);
            void reserve(size_t Length);

            friend String operator+(const String &L, char R);
            friend String operator+(const String &L, const char *R);
            friend String operator+(const String &L, const char16_t *R);
            friend String operator+(const String &L, const std::string R);
            friend String operator+(const String &L, const std::u16string R);
            friend String operator+(const String &L, const String &R);

            friend String operator+(const String &L, u8 U);
            friend String operator+(const String &L, u16 U);
            friend String operator+(const String &L, u32 U);
            friend String operator+(const String &L, u64 U);
            friend String operator+(const String &L, s8 I);
            friend String operator+(const String &L, s16 I);
            friend String operator+(const String &L, i32 I);
            friend String operator+(const String &L, s64 I);
            friend String operator+(const String &L, float D);
            friend String operator+(const String &L, double D);

            String operator+=(char C);
            String operator+=(u8 U);
            String operator+=(u16 U);
            String operator+=(u32 U);
            String operator+=(u64 U);
            String operator+=(s8 I);
            String operator+=(s16 I);
            String operator+=(i32 I);
            String operator+=(s64 I);
            String operator+=(float D);
            String operator+=(double D);
        private:
            std::u16string base;
    };
}

namespace std
{
    // More compatibility
    int stoi(pu::String Str, size_t *Index = 0, int Base = 10);
}