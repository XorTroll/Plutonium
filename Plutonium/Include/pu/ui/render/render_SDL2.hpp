
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
#include <pu/ui/ui_Color.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>

namespace pu::ui::render
{
    typedef SDL_Window *NativeWindow;
    typedef SDL_Renderer *NativeRenderer;
    typedef SDL_Surface *NativeSurface;
    typedef SDL_Texture *NativeTexture;
    typedef TTF_Font *NativeFont;

    enum class SharedFont
    {
        Standard,
        ChineseSimplified,
        ExtendedChineseSimplified,
        ChineseTraditional,
        Korean,
        NintendoExtended,
    };

    NativeTexture ConvertToTexture(NativeSurface Surface);
    NativeTexture RenderText(NativeFont Font, String Text, Color Color);
    NativeTexture LoadImage(std::string Path);
    NativeFont LoadSharedFont(SharedFont Type, s32 Size);
    NativeFont LoadFont(std::string Path, s32 Size);
    void SetDefaultFont(std::string Path);
    void SetDefaultFontFromShared(SharedFont Type);
    NativeFont LoadDefaultFont(s32 Size);
    s32 GetTextureWidth(NativeTexture Texture);
    s32 GetTextureHeight(NativeTexture Texture);
    s32 GetTextWidth(NativeFont Font, String Text);
    s32 GetTextHeight(NativeFont Font, String Text);
    void SetAlphaValue(NativeTexture Texture, u8 Alpha);
    void DeleteFont(NativeFont Font);
    void DeleteTexture(NativeTexture Texture);
}