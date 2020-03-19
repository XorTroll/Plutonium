
#pragma once

#include <memory>
#include <switch.h>

// Defines a static function (::New(...)) as a constructor for smart ptrs, also defines a custom type (::Ref) to simplify it
#define PU_SMART_CTOR(type) \
using Ref = std::shared_ptr<type>; \
template<typename ...Args> \
static Ref New(Args &&...CtorArgs) \
{ \
    return std::move(std::make_shared<type>(std::forward<Args>(CtorArgs)...)); \
}

// For convenience
using i32 = s32;
