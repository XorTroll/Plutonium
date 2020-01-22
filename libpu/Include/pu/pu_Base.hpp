
#pragma once
#include <switch.h>
#include <memory>
#include <string>

#define tmplog(fmt, ...) { \
    char buf[0x800] = {0}; \
    sprintf(buf, fmt, ##__VA_ARGS__); \
    svcOutputDebugString(buf, strlen(buf)); \
}

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

#define _PU_CLASS_PROPERTY_INNER_VAR(name, type) \
private: \
type name; \

#define _PU_CLASS_PROPERTY_SETTER(inner_var, type, name) \
public: \
void Set##name(type var) { \
    this->inner_var = var; \
}

#define _PU_CLASS_PROPERTY_GETTER(inner_var, type, name) \
public: \
type Get##name() { \
    return this->inner_var; \
}

// Creates a private variable and a Get* method to access it
#define PU_CLASS_PROPERTY_G(inner_var, type, g_type, name) \
_PU_CLASS_PROPERTY_INNER_VAR(inner_var, type) \
_PU_CLASS_PROPERTY_GETTER(inner_var, g_type, name)

// Creates a private variable and a Set* method to modify it
#define PU_CLASS_PROPERTY_S(inner_var, type, s_type, name) \
_PU_CLASS_PROPERTY_INNER_VAR(inner_var, type) \
_PU_CLASS_PROPERTY_SETTER(inner_var, s_type, name)

// Creates a private variable, a Get* method to access it and a Set* method to modify it
#define PU_CLASS_PROPERTY_GS(inner_var, type, g_type, s_type, name) \
_PU_CLASS_PROPERTY_INNER_VAR(inner_var, type) \
_PU_CLASS_PROPERTY_SETTER(inner_var, s_type, name) \
_PU_CLASS_PROPERTY_GETTER(inner_var, g_type, name)

#define PU_CLASS_PROPERTY_SIMPLE_G(inner_var, type, name) PU_CLASS_PROPERTY_G(inner_var, type, type, name)

#define PU_CLASS_PROPERTY_SIMPLE_S(inner_var, type, name) PU_CLASS_PROPERTY_S(inner_var, type, type, name)

#define PU_CLASS_PROPERTY_SIMPLE_GS(inner_var, type, name) PU_CLASS_PROPERTY_GS(inner_var, type, type, type, name)