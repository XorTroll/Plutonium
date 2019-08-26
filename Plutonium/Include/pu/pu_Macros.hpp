
#pragma once

#include <memory>

#define PU_SMART_CTOR(type) \
template<typename ...Args> \
static std::shared_ptr<type> New(Args &&...args) \
{ \
    return std::move(std::make_shared<type>(std::forward<Args>(args)...)); \
}
