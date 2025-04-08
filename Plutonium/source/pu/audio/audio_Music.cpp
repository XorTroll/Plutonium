#include <pu/audio/audio_Music.hpp>

namespace pu::audio {

    Music OpenMusic(const std::string &path) {
        return Mix_LoadMUS(path.c_str());
    }

    void PlayMusic(Music mus, const s32 loops) {
        Mix_PlayMusic(mus, loops);
    }

    void PlayMusicWithFadeIn(Music mus, const s32 loops, const s32 ms) {
        Mix_FadeInMusic(mus, loops, ms);
    }

    bool IsPlayingMusic() {
        return Mix_PlayingMusic();
    }

    void PauseMusic() {
        Mix_PauseMusic();
    }

    void ResumeMusic() {
        Mix_ResumeMusic();   
    }

    void SetMusicVolume(const s32 vol) {
        Mix_VolumeMusic(vol);
    }

    s32 GetMusicVolume() {
        return Mix_VolumeMusic(-1);
    }

    void FadeOutMusic(const s32 ms) {
        Mix_FadeOutMusic(ms);
    }

    void RewindMusic() {
        Mix_RewindMusic();
    }

    void StopMusic() {
        Mix_HaltMusic();
    }

    void SetMusicPosition(const double sec) {
        Mix_SetMusicPosition(sec);
    }

    void DestroyMusic(Music &mus) {
        Mix_FreeMusic(mus);
        mus = nullptr;
    }

}
