
#pragma once
#include <SDL2/SDL_mixer.h>
#include <pu/pu_Include.hpp> 

namespace pu::audio {

    using Sfx = Mix_Chunk*;

    Sfx LoadSfx(const std::string &path);
    void PlaySfx(Sfx sfx);
    void DestroySfx(Sfx &sfx);

}