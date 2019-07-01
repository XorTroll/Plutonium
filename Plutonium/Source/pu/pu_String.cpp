#include <pu/pu_String.hpp>
#include <locale>
#include <codecvt>

namespace pu
{
    String::String()
    {
    }

    String::String(const char *C_UTF8)
    {
        std::string utf8(C_UTF8);
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        this->base = converter.from_bytes(utf8);
    }

    String::String(const char16_t *C_UTF16)
    {
        this->base = std::u16string(C_UTF16);
    }

    String::String(std::string UTF8)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        this->base = converter.from_bytes(UTF8);
    }

    String::String(std::u16string UTF16)
    {
        this->base = UTF16;
    }

    const char16_t *String::CStr()
    {
        return this->base.c_str();
    }

    const char *String::CStr8()
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        std::string utf8 = converter.to_bytes(this->base);
        return utf8.c_str();
    }
}