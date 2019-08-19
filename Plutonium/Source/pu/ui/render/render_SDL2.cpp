#include <pu/ui/render/render_SDL2.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <utility>
#include <unordered_map>

namespace pu::ui::render
{
    std::unordered_map<u32, std::pair<std::string, NativeFont>> filefonts;
    std::unordered_map<u32, std::pair<SharedFont, NativeFont>> shfonts;

    static SharedFont shfont = SharedFont::Standard;
    static std::string fontpth;

    NativeTexture ConvertToTexture(NativeSurface Surface)
    {
        NativeTexture tex = SDL_CreateTextureFromSurface(GetMainRenderer(), Surface);
        SDL_FreeSurface(Surface);
        return tex;
    }

    NativeTexture RenderText(NativeFont Font, String Text, Color Color)
    {
        NativeSurface txsrf = TTF_RenderUNICODE_Blended_Wrapped(Font, (const u16*)Text.AsUTF16().c_str(), { Color.R, Color.G, Color.B, Color.A }, 1280);
        SDL_SetSurfaceAlphaMod(txsrf, 255);
        return ConvertToTexture(txsrf);
    }

    NativeTexture LoadImage(std::string Path)
    {
        return ConvertToTexture(IMG_Load(Path.c_str()));
    }

    NativeFont LoadSharedFont(SharedFont Type, s32 Size)
    {
        auto it = shfonts.find(Size);
        if((it != shfonts.end()) && (it->second.first == Type)) return it->second.second;
        PlFontData plfont;
        NativeFont font = NULL;
        SDL_RWops *mem = NULL;
        Result rc = plGetSharedFontByType(&plfont, static_cast<s32>(Type));
        if(rc == 0)
        {
            mem = SDL_RWFromMem(plfont.address, plfont.size);
            font = TTF_OpenFontRW(mem, 1, Size);
        }
        if(font != NULL) shfonts.insert(std::make_pair(Size, std::make_pair(Type, font)));
        return font;
    }

    NativeFont LoadFont(std::string Path, s32 Size)
    {
        auto it = filefonts.find(Size);
        if((it != filefonts.end()) && (it->second.first == Path)) return it->second.second;
        auto font = TTF_OpenFont(Path.c_str(), Size);
        if(font != NULL) filefonts.insert(std::make_pair(Size, std::make_pair(Path, font)));
        return font;
    }

    void SetDefaultFont(std::string Path)
    {
        fontpth = Path;
    }

    void SetDefaultFontFromShared(SharedFont Type)
    {
        shfont = Type;
    }

    NativeFont LoadDefaultFont(s32 Size)
    {
        if(!fontpth.empty()) return LoadFont(fontpth, Size);
        return LoadSharedFont(shfont, Size);
    }

    s32 GetTextureWidth(NativeTexture Texture)
    {
        int w = 0;
        SDL_QueryTexture(Texture, NULL, NULL, &w, NULL);
        return (s32)w;
    }

    s32 GetTextureHeight(NativeTexture Texture)
    {
        int h = 0;
        SDL_QueryTexture(Texture, NULL, NULL, NULL, &h);
        return (s32)h;
    }

    #define PROCESS_TMP_STR { \
        int tmpw = 0; \
        TTF_SizeUNICODE(Font, (const u16*)tmpstr.c_str(), &tmpw, NULL); \
        if(tmpw > tw) tw = tmpw; \
        int tmph = 0; \
        TTF_SizeUNICODE(Font, (const u16*)tmpstr.c_str(), NULL, &tmph); \
        th += tmph; \
        tmpstr = u""; \
    }

    #define TEXT_SIZE_BASE std::u16string tmpstr; \
        int tw = 0; \
        int th = 0; \
        for(auto &ch: Text.AsUTF16()) \
        { \
            if(ch == u'\n') \
            PROCESS_TMP_STR \
            else tmpstr += ch; \
        } \
        if(!tmpstr.empty()) \
        PROCESS_TMP_STR

    s32 GetTextWidth(NativeFont Font, String Text)
    {
        TEXT_SIZE_BASE

        return (s32)tw;
    }

    s32 GetTextHeight(NativeFont Font, String Text)
    {
        TEXT_SIZE_BASE

        return (s32)th;
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