
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <pu/sdl2/sdl2_CustomTtf.h>

namespace pu::sdl2 {

    using Texture = SDL_Texture*;
    using Window = SDL_Window*;
    using Renderer = SDL_Renderer*;
    using Font = TTF_Font*;
    using Surface = SDL_Surface*;

}