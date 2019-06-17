
#pragma once
#include <SDL2/SDL_mixer.h>
#include <string> 

namespace pu::sfx
{
    typedef Mix_Chunk *Sfx;

    Sfx Load(std::string Path);
    void Play(Sfx Sfx);
    void DeleteSfx(Sfx Sfx);
}