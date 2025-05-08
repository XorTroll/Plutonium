/**
 * Plutonium library
 * @file pu_Include.hpp
 * @brief Basic Plutonium include header
 * @author XorTroll
 * @copyright XorTroll
*/

#pragma once
#include <switch.h>
#include <string>
#include <memory>
#include <cmath>
#include <optional>

/**
 * @brief Defines a static function (::New(...)) as a constructor for smart ptrs, also defines a custom type (::Ref) to simplify it
*/
#define PU_SMART_CTOR(type) \
/** @brief Alias for shared pointer to type */ \
using Ref = std::shared_ptr<type>; \
/** @brief Factory-style constructor for shared_ptr */ \
template<typename ...Args> \
inline static Ref New(Args &&...ctor_args) { \
    return std::make_shared<type>(std::forward<Args>(ctor_args)...); \
}

/**
 * @brief Automatically defines a getter function for a POD variable
*/
#define PU_CLASS_POD_GET(fn_name, var_name, type) \
inline type Get##fn_name() { \
    return this->var_name; \
}

/**
 * @brief Automatically defines a setter function for a POD variable
*/
#define PU_CLASS_POD_SET(fn_name, var_name, type) \
inline void Set##fn_name(const type new_val) { \
    this->var_name = new_val; \
}

/**
 * @brief Automatically defines a getter and setter function for a POD variable
*/
#define PU_CLASS_POD_GETSET(fn_name, var_name, type) \
PU_CLASS_POD_GET(fn_name, var_name, type) \
PU_CLASS_POD_SET(fn_name, var_name, type)

/**
 * @brief Checks if the specified result code is not successful, and if so, returns it and ends the function
*/
#define PU_RC_TRY(rc) { \
    const auto _tmp_rc = (rc); \
    if(R_FAILED(_tmp_rc)) { \
        return _tmp_rc; \
    } \
}

namespace pu {

    constexpr Result ResultSuccess = 0; // Success result code

    constexpr u32 Module = 493;

    // I guess these are self-explanatory

    constexpr auto ResultSdlInitFailed = MAKERESULT(Module, 1);
    constexpr auto ResultSdlCreateWindowFailed = MAKERESULT(Module, 2);
    constexpr auto ResultSdlCreateRendererFailed = MAKERESULT(Module, 3);
    constexpr auto ResultImgInitFailed = MAKERESULT(Module, 4);
    constexpr auto ResultTtfInitFailed = MAKERESULT(Module, 5);
    constexpr auto ResultApplicationNotReady = MAKERESULT(Module, 6);

}
