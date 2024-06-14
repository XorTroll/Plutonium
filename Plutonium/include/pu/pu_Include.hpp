
/*

    Plutonium library

    @file pu_Include.hpp
    @brief Basic includes and definitions for the library

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <switch.h>
#include <string>
#include <memory>
#include <cmath>

// Defines a static function (::New(...)) as a constructor for smart ptrs, also defines a custom type (::Ref) to simplify it
#define PU_SMART_CTOR(type) \
using Ref = std::shared_ptr<type>; \
template<typename ...Args> \
inline static Ref New(Args &&...ctor_args) { \
    return std::make_shared<type>(std::forward<Args>(ctor_args)...); \
}

#define PU_CLASS_POD_GET(fn_name, var_name, type) \
inline type Get##fn_name() { \
    return this->var_name; \
}

#define PU_CLASS_POD_SET(fn_name, var_name, type) \
inline void Set##fn_name(const type new_val) { \
    this->var_name = new_val; \
}

#define PU_CLASS_POD_GETSET(fn_name, var_name, type) \
PU_CLASS_POD_GET(fn_name, var_name, type) \
PU_CLASS_POD_SET(fn_name, var_name, type)

namespace pu {

    using i32 = s32;

}