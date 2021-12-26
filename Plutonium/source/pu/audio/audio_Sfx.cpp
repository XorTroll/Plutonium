#include <pu/audio/audio_Sfx.hpp>

namespace pu::audio
{
    Sfx Load(std::string Path)
    {
        return Mix_LoadWAV(Path.c_str());
    }

    void Play(Sfx Sfx)
    {
        Mix_PlayChannel(-1, Sfx, 0);
    }

    void DeleteSfx(Sfx Sfx)
    {
        Mix_FreeChunk(Sfx);
        Sfx = nullptr;
    }
}