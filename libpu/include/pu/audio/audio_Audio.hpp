/**
 * Plutonium library
 * @file audio_Audio.hpp
 * @brief Main audio header
 * @author XorTroll
 * @copyright XorTroll
*/

#pragma once
#include <pu/audio/audio_Music.hpp>
#include <pu/audio/audio_Sfx.hpp>

namespace pu::audio {

    /**
     * @brief Complete set of flags to initialize the audio system with: supports FLAC, MOD, MP3 and OGG formats.
     */
    constexpr s32 MixerAllFlags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;

    /**
     * @brief Initializes the underlying audio system (SDL2-Mixer) with the specified flags.
     * @param mix_flags Flags to initialize the audio system with.
     * @return Whether the audio system was initialized successfully.
     */
    bool Initialize(s32 mix_flags);

    /**
     * @brief Finalizes the underlying audio system (SDL2-Mixer).
     */
    void Finalize();

}
