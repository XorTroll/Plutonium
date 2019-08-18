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

    #define BASE_RETURN_THIS_PLUS(var) { \
        *this = *this + var; \
        return *this; \
    }

    const size_t String::npos = std::u16string::npos;

    String::String() : base()
    {
    }

    String::String(const char *C_UTF8)
    {
        this->base = MakeFromUTF8(std::string(C_UTF8));
    }

    bool String::operator==(const char *C_UTF8)
    {
        return (*this == std::string(C_UTF8));
    }

    bool String::operator!=(const char *C_UTF8)
    {
        return !(*this == C_UTF8);
    }

    String String::operator+=(const char *C_UTF8)
    BASE_RETURN_THIS_PLUS(C_UTF8)

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

    String String::operator+=(const char16_t *C_UTF16)
    BASE_RETURN_THIS_PLUS(C_UTF16)

    String::String(std::string UTF8)
    {
        this->base = MakeFromUTF8(UTF8);
    }

    bool String::operator==(std::string UTF8)
    {
        return (this->base == MakeFromUTF8(UTF8));
    }

    bool String::operator!=(std::string UTF8)
    {
        return !(*this == UTF8);
    }

    String String::operator+=(std::string UTF8)
    BASE_RETURN_THIS_PLUS(UTF8)

    std::string String::AsUTF8()
    {
        return MakeFromUTF16(this->base);
    }

    String::String(std::u16string UTF16)
    {
        this->base = UTF16;
    }

    bool String::operator==(std::u16string UTF16)
    {
        return (this->base == UTF16);
    }

    bool String::operator!=(std::u16string UTF16)
    {
        return !(*this == UTF16);
    }

    String String::operator+=(std::u16string UTF16)
    BASE_RETURN_THIS_PLUS(UTF16)

    std::u16string String::AsUTF16()
    {
        return this->base;
    }

    bool String::operator==(String Str)
    {
        return (this->AsUTF16() == Str.AsUTF16());
    }

    bool String::operator!=(String Str)
    {
        return !(*this == Str);
    }

    String String::operator+=(String Str)
    {
        this->base += Str.AsUTF16();
        return *this;
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

    size_t String::find_first_of(pu::String Str, size_t Position)
    {
        return this->base.find_first_of(Str.AsUTF16(), Position);
    }

    size_t String::find_last_of(pu::String Str, size_t Position)
    {
        return this->base.find_last_of(Str.AsUTF16(), Position);
    }

    void String::erase(size_t Offset, size_t Length)
    {
        this->base.erase(Offset, Length);
    }

    String::iterator String::begin()
    {
        return this->base.begin();
    }

    String::iterator String::end()
    {
        return this->base.end();
    }

    size_t String::find(pu::String Str, size_t Position)
    {
        return this->base.find(Str.AsUTF16(), Position);
    }

    String String::replace(size_t Position, size_t Length, pu::String Str)
    {
        return this->base.replace(Position, Length, Str.AsUTF16());
    }

    void String::reserve(size_t Length)
    {
        this->base.reserve(Length);
    }

    #define BASE_OPERATOR_BLOCK { \
        L = L + String(R); \
        return L; \
    }

    String operator+(const String &L, char R)
    {
        return String(L.base + MakeFromUTF8(std::string(1, R)));
    }

    String operator+(const String &L, const char *R)
    {
        return String(L.base + MakeFromUTF8(std::string(R)));
    }

    String operator+(const String &L, const char16_t *R)
    {
        return String(L.base + std::u16string(R));
    }

    String operator+(const String &L, const std::string R)
    {
        return String(L.base + MakeFromUTF8(R));
    }

    String operator+(const String &L, const std::u16string R)
    {
        return String(L.base + R);
    }

    String operator+(const String &L, const String &R)
    {
        return String(L.base + R.base);
    }

    String String::operator+=(char C)
    BASE_RETURN_THIS_PLUS(C)

    String String::operator+=(u8 N)
    BASE_RETURN_THIS_PLUS(N)

    String String::operator+=(u16 N)
    BASE_RETURN_THIS_PLUS(N)
    
    String String::operator+=(u32 N)
    BASE_RETURN_THIS_PLUS(N)
    
    String String::operator+=(u64 N)
    BASE_RETURN_THIS_PLUS(N)
    
    String String::operator+=(double Dec)
    BASE_RETURN_THIS_PLUS(Dec)
}

namespace std
{
    int stoi(pu::String Str, size_t *Index, int Base)
    {
        return std::stoi(Str.AsUTF8(), Index, Base);
    }
}