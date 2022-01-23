#include <pu/audio/audio_Sfx.hpp>

namespace pu::audio {

    Sfx LoadSfx(const std::string &path) {
        return Mix_LoadWAV(path.c_str());
    }

    void PlaySfx(Sfx sfx) {
        Mix_PlayChannel(-1, sfx, 0);
    }

    void DestroySfx(Sfx &sfx) {
        Mix_FreeChunk(sfx);
        sfx = nullptr;
    }

}