
#pragma once
#include <pu/pu_Base.hpp>
#include <pu/sdl2/sdl2_Types.hpp>

namespace pu::ui {

    union Color {

        u32 value;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };

        static constexpr u8 ComponentMax = UINT8_MAX;

        Color() : value(0) {}

        static inline Color FromValue(u32 value) {
            Color clr = {};
            clr.value = value;
            return clr;
        }

        static inline Color FromRGBA(u8 r, u8 g, u8 b, u8 a) {
            Color clr = {};
            clr.r = r;
            clr.g = g;
            clr.b = b;
            clr.a = a;
            return clr;
        }

        static inline Color FromSDLColor(SDL_Color clr) {
            return FromRGBA(clr.r, clr.g, clr.b, clr.a);
        }

        inline SDL_Color ToSDLColor() {
            SDL_Color sdlclr = {};
            sdlclr.r = this->r;
            sdlclr.g = this->g;
            sdlclr.b = this->b;
            sdlclr.a = this->a;
            return sdlclr;
        }

        static inline Color FromHexString(const std::string &str) {
            Color clr = {};
            std::sscanf(str.c_str(), "#%02x%02x%02x%02x", (u32*)&clr.r, (u32*)&clr.g, (u32*)&clr.b, (u32*)&clr.a);
            return clr;
        }

        inline std::string ToHexString() {
            char buf[0x20] = {0};
            std::sprintf(buf, "#%02x%02x%02x%02x", (u32)this->r, (u32)this->g, (u32)this->b, (u32)this->a);
            return buf;
        }
    };

    static_assert(sizeof(Color) == sizeof(u32), "Invalid RGBA8 color");

}