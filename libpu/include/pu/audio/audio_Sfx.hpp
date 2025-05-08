/**
 * Plutonium library
 * @file audio_Sfx.hpp
 * @brief Sfx (sound effects) support
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <SDL2/SDL_mixer.h>
#include <pu/pu_Include.hpp> 

namespace pu::audio {

    /**
     * @brief Type representing a sound effect.
     */
    using Sfx = Mix_Chunk*;

    /**
     * @brief Loads a sound effect from the specified path.
     * @note pu::audio::Initialize must be called before using this function.
     * @note The sound effect must be manually freed with pu::audio::DestroySfx when it is no longer needed.
     * @param path Path to the sound effect file.
     * @return Sound effect loaded, or NULL if an error occurred.
     */
    Sfx LoadSfx(const std::string &path);

    /**
     * @brief Plays a sound effect.
     * @note pu::audio::Initialize must be called before using this function.
     * @param sfx Sound effect to play. If NULL is passed, nothing will happen.
     */
    void PlaySfx(Sfx sfx);

    /**
     * @brief Destroys a sound effect.
     * @param sfx Sound effect to destroy. If NULL is passed, nothing will happen.
     */
    void DestroySfx(Sfx &sfx);

}
