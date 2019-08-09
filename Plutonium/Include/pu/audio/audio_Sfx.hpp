
/*

    Plutonium library

    @file audio_Sfx.hpp
    @brief Sfx (sound effects) support
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <SDL2/SDL_mixer.h>
#include <string> 

namespace pu::audio
{
    typedef Mix_Chunk *Sfx;

    Sfx Load(std::string Path);
    void Play(Sfx Sfx);
    void DeleteSfx(Sfx Sfx);
}