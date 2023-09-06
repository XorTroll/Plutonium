
/*

    Plutonium library

    @file audio_Sfx.hpp
    @brief Sfx (sound effects) support
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <SDL2/SDL_mixer.h>
#include <pu/pu_Include.hpp> 

namespace pu::audio {

    using Sfx = Mix_Chunk*;

    Sfx LoadSfx(const std::string &path);
    void PlaySfx(Sfx sfx);
    void DestroySfx(Sfx &sfx);

}