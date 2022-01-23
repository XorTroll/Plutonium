
/*

    Plutonium library

    @file render_SDL2.hpp
    @brief Wrapper code to simplify SDL2 usage
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/sdl2/sdl2_Types.hpp>

namespace pu::ui::render {

    sdl2::Texture ConvertToTexture(sdl2::Surface surface);
    sdl2::Texture LoadImage(const std::string &path);
    i32 GetTextureWidth(sdl2::Texture texture);
    i32 GetTextureHeight(sdl2::Texture texture);
    void SetAlphaValue(sdl2::Texture texture, const u8 alpha);
    void DeleteTexture(sdl2::Texture &texture);

}