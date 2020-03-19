#include <pu/audio/audio_Music.hpp>

namespace pu::audio
{
    Music Open(std::string Path)
    {
        return Mix_LoadMUS(Path.c_str());
    }

    void Play(Music Mus, int Loops)
    {
        Mix_PlayMusic(Mus, Loops);
    }

    void PlayWithFadeIn(Music Mus, int Loops, int Milli)
    {
        Mix_FadeInMusic(Mus, Loops, Milli);
    }

    bool IsPlaying()
    {
        return Mix_PlayingMusic();
    }

    void Pause()
    {
        Mix_PauseMusic();
    }

    void Resume()
    {
        Mix_ResumeMusic();   
    }

    void SetVolume(int Volume)
    {
        Mix_VolumeMusic(Volume);
    }

    int GetVolume()
    {
        return Mix_VolumeMusic(-1);
    }

    void FadeOut(int Milli)
    {
        Mix_FadeOutMusic(Milli);
    }

    void Rewind()
    {
        Mix_RewindMusic();
    }

    void Stop()
    {
        Mix_HaltMusic();
    }

    void SetPosition(double Sec)
    {
        Mix_SetMusicPosition(Sec);
    }

    void Delete(Music Mus)
    {
        Mix_FreeMusic(Mus);
        Mus = nullptr;
    }
}