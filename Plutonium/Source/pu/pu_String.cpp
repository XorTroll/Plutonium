#include <pu/pu_String.hpp>
#include <locale>
#include <codecvt>

namespace pu
{
    static std::u16string MakeFromUTF8(std::string Str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        return converter.from_bytes(Str);
    }

    static std::string MakeFromUTF16(std::u16string Str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        return converter.to_bytes(Str);
    }

    String::String()
    {
    }

    String::String(const char *C_UTF8)
    {
        this->base = MakeFromUTF8(C_UTF8);
    }

    bool String::operator==(const char *C_UTF8)
    {
        return (this->base == MakeFromUTF8(C_UTF8));
    }

    bool String::operator!=(const char *C_UTF8)
    {
        return !(*this == C_UTF8);
    }

    String String::operator+(const char *C_UTF8)
    {
        return String(this->base + MakeFromUTF8(C_UTF8));
    }

    const char *String::AsCUTF8()
    {
        return this->AsUTF8().c_str();
    }

    String::String(const char16_t *C_UTF16)
    {
        this->base = std::u16string(C_UTF16);
    }

    bool String::operator==(const char16_t *C_UTF16)
    {
        return (this->base == std::u16string(C_UTF16));
    }

    bool String::operator!=(const char16_t *C_UTF16)
    {
        return !(*this == C_UTF16);
    }

    String String::operator+(const char16_t *C_UTF16)
    {
        auto sum = this->base + std::u16string(C_UTF16);
        return String(sum);
    }

    const char16_t *String::AsCUTF16()
    {
        return this->AsUTF16().c_str();
    }

    String::String(std::string UTF8)
    {
        this->base = MakeFromUTF8(UTF8);
    }

    bool String::operator==(std::string &UTF8)
    {
        return (*this == UTF8.c_str());
    }

    bool String::operator!=(std::string &UTF8)
    {
        return (*this != UTF8.c_str());
    }

    String String::operator+(std::string &UTF8)
    {
        return (*this + UTF8.c_str());
    }

    std::string String::AsUTF8()
    {
        return MakeFromUTF16(this->base);
    }

    String::String(std::u16string UTF16)
    {
        this->base = UTF16;
    }

    bool String::operator==(std::u16string &UTF16)
    {
        return (*this == UTF16.c_str());
    }

    bool String::operator!=(std::u16string &UTF16)
    {
        return (*this != UTF16.c_str());
    }

    String String::operator+(std::u16string &UTF16)
    {
        return (*this + UTF16.c_str());
    }

    std::u16string String::AsUTF16()
    {
        return this->base;
    }

    bool String::operator==(String &Str)
    {
        return (this->AsUTF16() == Str.AsUTF16());
    }

    bool String::operator!=(String &Str)
    {
        return !(*this == Str);
    }

    String String::operator+(String &Str)
    {
        return String(this->AsUTF16() + Str.AsUTF16());
    }

    bool String::StartsWith(String Str)
    {
        return (this->base.rfind(Str.AsUTF16(), 0) == 0);
    }

    bool String::IsEmpty()
    {
        return this->base.empty();
    }

    bool String::HasAny()
    {
        return !this->IsEmpty();
    }

    size_t String::GetLength()
    {
        return this->base.length();
    }

    pu::String String::Substring(size_t Index, size_t Length)
    {
        return this->base.substr(Index, Length);
    }

    bool String::empty()
    {
        return this->IsEmpty();
    }

    size_t String::length()
    {
        return this->GetLength();
    }

    pu::String String::substr(size_t Offset, size_t Length)
    {
        return this->Substring(Offset, Length);
    }
}