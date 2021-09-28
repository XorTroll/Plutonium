
/*

    Plutonium library

    @file render_SDL2.hpp
    @brief Wrapper code to simplify SDL2 usage
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <string>
#include <switch.h>
#include <pu/pu_String.hpp>
#include <pu/ui/ui_Types.hpp>
#include <pu/sdl2/sdl2_Types.hpp>

namespace pu::ui::render {

    enum class SharedFont
    {
        Standard,
        ChineseSimplified,
        ExtendedChineseSimplified,
        ChineseTraditional,
        Korean,
        NintendoExtended,
    };

    sdl2::Texture ConvertToTexture(sdl2::Surface Surface);
    sdl2::Texture LoadImage(std::string Path);
    i32 GetTextureWidth(sdl2::Texture Texture);
    i32 GetTextureHeight(sdl2::Texture Texture);
    void SetAlphaValue(sdl2::Texture Texture, u8 Alpha);
    void DeleteTexture(sdl2::Texture Texture);
}