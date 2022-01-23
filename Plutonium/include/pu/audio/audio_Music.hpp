
/*

    Plutonium library

    @file audio_Music.hpp
    @brief Music (BGM) support
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <SDL2/SDL_mixer.h>
#include <pu/pu_Include.hpp>

namespace pu::audio {

    using Music = Mix_Music*;

    Music OpenMusic(const std::string &path);
    void PlayMusic(Music mus, const int loops);
    void PlayMusicWithFadeIn(Music mus, const i32 llops, const i32 ms);
    bool IsPlayingMusic();
    void PauseMusic();
    void ResumeMusic();
    void SetMusicVolume(const i32 vol);
    i32 GetMusicVolume();
    void FadeOutMusic(const i32 ms);
    void RewindMusic();
    void StopMusic();
    void SetMusicPosition(const double sec);
    void DestroyMusic(Music &mus);

}