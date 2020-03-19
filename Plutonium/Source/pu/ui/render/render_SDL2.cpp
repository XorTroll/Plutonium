#include <pu/ui/render/render_SDL2.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <utility>
#include <unordered_map>

namespace pu::ui::render
{
    sdl2::Texture ConvertToTexture(sdl2::Surface Surface)
    {
        sdl2::Texture tex = SDL_CreateTextureFromSurface(GetMainRenderer(), Surface);
        SDL_FreeSurface(Surface);
        return tex;
    }

    sdl2::Texture LoadImage(std::string Path)
    {
        return ConvertToTexture(IMG_Load(Path.c_str()));
    }

    i32 GetTextureWidth(sdl2::Texture Texture)
    {
        int w = 0;
        SDL_QueryTexture(Texture, nullptr, nullptr, &w, nullptr);
        return (i32)w;
    }

    i32 GetTextureHeight(sdl2::Texture Texture)
    {
        int h = 0;
        SDL_QueryTexture(Texture, nullptr, nullptr, nullptr, &h);
        return (i32)h;
    }

    void SetAlphaValue(sdl2::Texture Texture, u8 Alpha)
    {
        SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(Texture, Alpha);
    }

    void DeleteTexture(sdl2::Texture Texture)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
}