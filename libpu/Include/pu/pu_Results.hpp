
#pragma once
#include <switch.h>

#define PU_DEFINE_RESULT_MODULE(name, val) static constexpr u32 Module##name = val * 100;
#define PU_DEFINE_RESULT(module, name, val) static constexpr Result Result##name = MAKERESULT(Module, Module##module + val);

namespace pu {

    namespace result {

        static constexpr u32 Module = 399;

        PU_DEFINE_RESULT_MODULE(Base, 0)
        PU_DEFINE_RESULT(Base, InvalidResultTypeCast, 1)

        PU_DEFINE_RESULT_MODULE(Color, 1)
        PU_DEFINE_RESULT(Color, InvalidColorHexString, 1)

        PU_DEFINE_RESULT_MODULE(SDL, 2)
        PU_DEFINE_RESULT(SDL, SDLInitializationFailure, 1)
        PU_DEFINE_RESULT(SDL, SDLWindowCreationFailure, 2)
        PU_DEFINE_RESULT(SDL, SDLRendererCreationFailure, 3)

        PU_DEFINE_RESULT_MODULE(TTF, 3)
        PU_DEFINE_RESULT(TTF, TTFInitializationFailure, 1)
        PU_DEFINE_RESULT(TTF, TTFNotInitialized, 2)

    }

    static constexpr Result Success = 0;

}

#define PU_RESULT_TRY(r) { \
    auto _tmp_rc = (r); \
    if(!R_SUCCEEDED(_tmp_rc)) { \
        return _tmp_rc; \
    } \
}

#define PU_RESULT_UNLESS(cond, r) { \
    if(!(cond)) { \
        return r; \
    } \
}
