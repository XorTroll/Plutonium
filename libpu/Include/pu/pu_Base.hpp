
#pragma once
#include <switch.h>
#include <memory>
#include <string>

#include <pu/pu_Results.hpp>

// Feature macros

#ifndef _PU_SDL2_MIXER
#ifdef PU_USE_SDL2_MIXER
    #define _PU_SDL2_MIXER 1
#else 
    #define _PU_SDL2_MIXER 0
#endif
#endif

#ifndef _PU_SDL2_GFX
#ifdef PU_USE_SDL2_GFX
    #define _PU_SDL2_GFX 1
#else 
    #define _PU_SDL2_GFX 0
#endif
#endif

#ifndef _PU_SDL2_IMAGE
#ifdef PU_USE_SDL2_IMAGE
    #define _PU_SDL2_IMAGE 1
#else 
    #define _PU_SDL2_IMAGE 0
#endif
#endif

using i8 = s8;
using i16 = s16;
using i32 = s32;
using i64 = s64;

namespace pu  {

    template<typename Base, typename Derived, typename ...Args>
    inline std::shared_ptr<Base> NewInstance(Args &&...args) {
        static_assert(std::is_base_of_v<Base, Derived>, "Invalid classes!");
        return std::make_shared<Derived>(args...);
    }

    template<typename T, typename ...Args>
    inline std::shared_ptr<T> NewInstance(Args &&...args) {
        return std::make_shared<T>(args...);
    }

    struct ScopedLock {

        Mutex mtx;

        ScopedLock(Mutex mutex) : mtx(mutex) {
            // mutexLock(&this->mtx);
        }

        ~ScopedLock() {
            // mutexUnlock(&this->mtx);
        }
    };

    inline Mutex CreateMutex() {
        Mutex mtx;
        mutexInit(&mtx);
        return mtx;
    }

    template<typename ...Args>
    inline std::string Format(const std::string& fmt, Args &&...args)  {
        std::string out;
        size_t size = snprintf(nullptr, 0, fmt.c_str(), args...) + 1; // Extra space for '\0'
        if(size > 0) {
            char *tmp = new char[size]();
            snprintf(tmp, size, fmt.c_str(), args...);
            out.assign(tmp);
            delete[] tmp;
        }
        return out;
    }
}

/*
#define PU_LOCKED_SCOPE(mtx, ...) { \
    pu::ScopedLock _lk(mtx); \
    __VA_ARGS__ \
}
*/

#define PU_LOCKED_SCOPE(mtx, ...) __VA_ARGS__