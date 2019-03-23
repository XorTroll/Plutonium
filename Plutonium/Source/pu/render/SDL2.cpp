#include <pu/render/SDL2.hpp>
#include <pu/render/Renderer.hpp>

namespace pu::render
{
    NativeTexture ConvertToTexture(NativeSurface Surface)
    {
        NativeTexture tex = SDL_CreateTextureFromSurface(GetMainRenderer(), Surface);
        SDL_FreeSurface(Surface);
        return tex;
    }

    NativeTexture RenderText(NativeFont Font, std::string Text, draw::Color Color)
    {
        NativeSurface txsrf = TTF_RenderUTF8_Blended_Wrapped(Font, Text.c_str(), { Color.R, Color.G, Color.B, Color.A }, 1280);
        SDL_SetSurfaceAlphaMod(txsrf, 255);
        return ConvertToTexture(txsrf);
    }

    NativeTexture LoadImage(std::string Path)
    {
        return ConvertToTexture(IMG_Load(Path.c_str()));
    }

    NativeFont LoadSharedFont(SharedFont Type, u32 Size)
    {
        PlFontData plfont;
        NativeFont font = NULL;
        SDL_RWops *mem = NULL;
        Result rc = plGetSharedFontByType(&plfont, static_cast<u32>(Type));
        if(rc == 0)
        {
            mem = SDL_RWFromMem(plfont.address, plfont.size);
            font = TTF_OpenFontRW(mem, 1, Size);
        }
        return font;
    }

    NativeFont LoadFont(std::string Path, u32 Size)
    {
        return TTF_OpenFont(Path.c_str(), Size);
    }

    u32 GetTextureWidth(NativeTexture Texture)
    {
        int w = 0;
        SDL_QueryTexture(Texture, NULL, NULL, &w, NULL);
        return (u32)w;
    }

    u32 GetTextureHeight(NativeTexture Texture)
    {
        int h = 0;
        SDL_QueryTexture(Texture, NULL, NULL, NULL, &h);
        return (u32)h;
    }

    u32 GetTextWidth(NativeFont Font, std::string Text)
    {
        int tw = 0;
        TTF_SizeUTF8(Font, Text.c_str(), &tw, NULL);
        return (u32)tw;
    }

    u32 GetTextHeight(NativeFont Font, std::string Text)
    {
        int th = 0;
        TTF_SizeUTF8(Font, Text.c_str(), NULL, &th);
        return (u32)th;
    }

    void SetAlphaValue(NativeTexture Texture, u8 Alpha)
    {
        SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(Texture, Alpha);
    }

    void DeleteFont(NativeFont Font)
    {
        TTF_CloseFont(Font);
        Font = NULL;
    }

    void DeleteTexture(NativeTexture Texture)
    {
        SDL_DestroyTexture(Texture);
        Texture = NULL;
    }
}