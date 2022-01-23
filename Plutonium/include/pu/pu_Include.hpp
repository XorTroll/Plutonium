
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

// Defines a static function (::New(...)) as a constructor for smart ptrs, also defines a custom type (::Ref) to simplify it
#define PU_SMART_CTOR(type) \
using Ref = std::shared_ptr<type>; \
template<typename ...Args> \
inline static Ref New(Args &&...ctor_args) { \
    return std::move(std::make_shared<type>(std::forward<Args>(ctor_args)...)); \
}

namespace pu {

    using i32 = s32;

}