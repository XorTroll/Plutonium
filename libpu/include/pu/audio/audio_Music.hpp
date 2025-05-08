/**
 * Plutonium library
 * @file audio_Music.hpp
 * @brief Music (BGM) support
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <SDL2/SDL_mixer.h>
#include <pu/pu_Include.hpp>

namespace pu::audio {

    /**
     * @brief Type representing a music file.
     */
    using Music = Mix_Music*;

    /**
     * @brief Opens a music file from the specified path.
     * @note pu::audio::Initialize must be called before using this function.
     * @note The music file must be manually freed with pu::audio::DestroyMusic when it is no longer needed.
     * @param path Path to the music file.
     * @return Music file opened, or NULL if an error occurred.
     */
    Music OpenMusic(const std::string &path);

    /**
     * @brief Plays a music file.
     * @note pu::audio::Initialize must be called before using this function.
     * @param mus Music file to play. If NULL is passed, nothing will happen.
     * @param loops Number of times to loop the music file.
     */
    void PlayMusic(Music mus, const s32 loops);

    /**
     * @brief Plays a music file with a fade-in effect.
     * @note pu::audio::Initialize must be called before using this function.
     * @param mus Music file to play. If NULL is passed, nothing will happen.
     * @param loops Number of times to loop the music file.
     * @param ms Time in milliseconds to fade in the music file.
     */
    void PlayMusicWithFadeIn(Music mus, const s32 loops, const s32 ms);

    /**
     * @brief Checks if music is currently playing.
     * @return Whether music is currently playing.
     */
    bool IsPlayingMusic();

    /**
     * @brief Pauses the currently playing music.
     */
    void PauseMusic();

    /**
     * @brief Resumes the currently paused music.
     */
    void ResumeMusic();

    /**
     * @brief Sets the volume of the currently playing music.
     * @note pu::audio::Initialize must be called before using this function.
     * @param vol Volume to set (0-128).
     */
    void SetMusicVolume(const s32 vol);

    /**
     * @brief Gets the volume of the currently playing music.
     * @note pu::audio::Initialize must be called before using this function.
     * @return Volume of the currently playing music.
     */
    s32 GetMusicVolume();

    /**
     * @brief Fades out the currently playing music.
     * @note pu::audio::Initialize must be called before using this function.
     * @param ms Time in milliseconds to fade out the music file.
     */
    void FadeOutMusic(const s32 ms);

    /**
     * @brief Rewinds the currently playing music.
     * @note pu::audio::Initialize must be called before using this function.
     */
    void RewindMusic();

    /**
     * @brief Stops the currently playing music.
     * @note pu::audio::Initialize must be called before using this function.
     */
    void StopMusic();

    /**
     * @brief Sets the position of the currently playing music.
     * @note pu::audio::Initialize must be called before using this function.
     * @param sec Position in seconds to set.
     */
    void SetMusicPosition(const double sec);

    /**
     * @brief Destroys a music file.
     * @param mus Music file to destroy. If NULL is passed, nothing will happen.
     */
    void DestroyMusic(Music &mus);

}
