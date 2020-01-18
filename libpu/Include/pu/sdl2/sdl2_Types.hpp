
#pragma once
#include <pu/pu_Base.hpp>
#include <SDL2/SDL.h>

// Our custom SDL-ttf
#include <pu/ttf/ttf_SDL_ttf.h>

#if _PU_SDL2_MIXER
    #include <SDL2/SDL_mixer.h>
#endif

#if _PU_SDL2_GFX
    #include <SDL2/SDL2_gfxPrimitives.h>
#endif

#if _PU_SDL2_IMAGE
    #include <SDL2/SDL_image.h>
#endif

#define PU_TRY_SDL2_RETURN(val, rc) { \
    const auto _tmp_val = (val); \
    if(_tmp_val != 0) { \
        return rc; \
    } \
}

namespace pu::sdl2 {

    using Texture = SDL_Texture*;
    using Surface = SDL_Surface*;
    using Renderer = SDL_Renderer*;
    using Window = SDL_Window*;
    using Font = TTF_Font*;

}