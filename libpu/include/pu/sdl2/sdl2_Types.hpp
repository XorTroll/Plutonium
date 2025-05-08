/**
 * Plutonium library
 * @file sdl2_Types.hpp
 * @brief Main SDL2 types header
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <pu/pu_Include.hpp>
#include <pu/sdl2/sdl2_CustomTtf.h>

namespace pu::sdl2 {

    /**
     * @brief Represents a handle to a texture in SDL2.
     */
    using Texture = SDL_Texture*;

    /**
     * @brief Represents a handle to a window in SDL2.
     */
    using Window = SDL_Window*;

    /**
     * @brief Represents a handle to a renderer in SDL2.
     */
    using Renderer = SDL_Renderer*;

    /**
     * @brief Represents a handle to a TTF font in SDL2.
     */
    using Font = TTF_Font*;

    /**
     * @brief Represents a handle to a surface in SDL2.
     */
    using Surface = SDL_Surface*;

    /**
     * @brief High-level handle wrapper to a texture in SDL2.
     */
    class TextureHandle {
        private:
            Texture tex;

        public:
            /**
             * @brief Creates a new empty TextureHandle.
             */
            constexpr TextureHandle() : tex(nullptr) {}

            /**
             * @brief Creates a new TextureHandle from an existing raw texture.
             * @param tex Raw texture to create the handle from.
             */
            constexpr TextureHandle(Texture tex) : tex(tex) {}

            PU_SMART_CTOR(TextureHandle)
            ~TextureHandle();

            /**
             * @brief Gets the raw texture handle.
             * @return Raw texture handle.
             */
            inline Texture Get() {
                return this->tex;
            }
    };

}
