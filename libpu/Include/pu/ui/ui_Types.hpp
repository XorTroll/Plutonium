
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

    struct Position {

        i32 x;
        i32 y;

        constexpr inline bool IsOutsideScreen() {
            // Negative positions are allowed in SDL :P
            return (x < 0) && (y < 0);
        }

    };

    struct TouchPosition : public Position {

        constexpr inline bool IsValid() {
            // For touch positions, negative coords = invalid
            return !this->IsOutsideScreen();
        }

    };

    #define PU_UI_FORWARD_POSITION(pos) pos.x, pos.y

    struct Size {

        u32 w;
        u32 h;

        constexpr inline bool IsValid() {
            // Let's consider 0 width/height is invalid
            return (w > 0) && (h > 0);
        }
    };

    #define PU_UI_FORWARD_SIZE(sz) sz.w, sz.h

    struct PositionAndSize : public Position, public Size {
        // Convenience type inheriting from both

        inline SDL_Rect ToSDLRect() {
            SDL_Rect rect = {};
            rect.x = this->x;
            rect.y = this->y;
            rect.w = this->w;
            rect.h = this->h;
            return rect;
        }
        
    };

    #define PU_UI_FORWARD_POSITION_AND_SIZE(pas) pas.x, pas.y, pas.w, pas.h

    // Input-related

    enum class InputControllerMode {

        All,
        Any,
        Auto,

    };

    enum class InputMode {

        Down,
        Up,
        Held

    };

    static constexpr u32 ControllerCount = 10;

    struct Input {

        u64 hid_down;
        u64 hid_up;
        u64 hid_held;

        template<InputControllerMode Mode>
        static Input LoadCurrentInput() {

            Input ipt = {};

            switch(Mode) {
                case InputControllerMode::All: {
                    for(u32 i = 0; i < ControllerCount; i++) {
                        HidControllerID ctrl_id = (HidControllerID)i;
                        if(hidIsControllerConnected(ctrl_id)) {
                            ipt.hid_down |= hidKeysDown(ctrl_id);
                            ipt.hid_up |= hidKeysUp(ctrl_id);
                            ipt.hid_held |= hidKeysHeld(ctrl_id);
                        }
                    }
                    break;
                }
                case InputControllerMode::Any: {
                    for(u32 i = 0; i < ControllerCount; i++) {
                        HidControllerID ctrl_id = (HidControllerID)i;
                        if(hidIsControllerConnected(ctrl_id)) {
                            ipt.hid_down = hidKeysDown(ctrl_id);
                            ipt.hid_up = hidKeysUp(ctrl_id);
                            ipt.hid_held = hidKeysHeld(ctrl_id);
                            break;
                        }
                    }
                    break;
                }
                case InputControllerMode::Auto: {
                    ipt.hid_down = hidKeysDown(CONTROLLER_P1_AUTO);
                    ipt.hid_up = hidKeysUp(CONTROLLER_P1_AUTO);
                    ipt.hid_held = hidKeysHeld(CONTROLLER_P1_AUTO);
                    break;
                }
            }

            return ipt;

        }

        template<u64 Key>
        NX_CONSTEXPR bool Matches(u64 input) {
            return input & Key;
        }

        template<InputMode Mode>
        constexpr inline u64 GetInputValue() {
            switch(Mode) {
                case InputMode::Down:
                    return this->hid_down;
                case InputMode::Up:
                    return this->hid_up;
                case InputMode::Held:
                    return this->hid_held;
            }
        }

        template<InputMode Mode, u64 Key, u64 ...Keys>
        constexpr inline bool MatchesAny() {
            if(Matches<Key>(this->GetInputValue<Mode>())) {
                return true;
            }
            if constexpr(sizeof...(Keys) > 0) {
                return MatchesAny<Mode, Keys...>();
            }
            return false;
        }

        template<InputMode Mode, u64 Key, u64 ...Keys>
        constexpr inline bool MatchesAll() {
            if(!Matches<Key>(this->GetInputValue<Mode>())) {
                return false;
            }
            if constexpr(sizeof...(Keys) > 0) {
                return MatchesAll<Mode, Keys...>();
            }
            return true;
        }

    };

}