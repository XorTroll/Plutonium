#include <pu/ttf/ttf_Font.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <pu/ui/render/render_SDL2.hpp>

namespace pu::ttf
{

    Font::Font(u32 font_sz) : font_size(font_sz) {}

    Font::~Font()
    {
        for(auto &[idx, font] : this->font_faces)
        {
            font->Dispose();
        }
    }

    i32 Font::LoadFromMemory(void *ptr, size_t size, FontFaceDisposingFunction disp_fn)
    {
        i32 idx = rand();
        auto font = std::make_unique<FontFace>(ptr, size, disp_fn, this->font_size, reinterpret_cast<void*>(this));
        this->font_faces.push_back(std::make_pair(idx, std::move(font)));
        return idx;
    }

    i32 Font::LoadFromFile(String path)
    {
        FILE *f = fopen(path.AsUTF8().c_str(), "rb");
        if(f)
        {
            fseek(f, 0, SEEK_END);
            auto size = ftell(f);
            rewind(f);
            if(size > 0)
            {
                auto fontbuf = new u8[size]();
                fread(fontbuf, 1, size, f);
                fclose(f);
                return this->LoadFromMemory(fontbuf, size, [](void *ptr)
                {
                    if(ptr != nullptr)
                    {
                        u8 *file_buf = reinterpret_cast<u8*>(ptr);
                        delete[] file_buf;
                    }
                });
            }
            fclose(f);
        }

        return InvalidFontFaceIndex;
    }

    void Font::Unload(i32 font_idx)
    {
        u32 i = 0;
        for(auto &[idx, font]: this->font_faces)
        {
            if(idx == font_idx)
            {
                this->font_faces.erase(this->font_faces.begin() + i);
                break;
            }
            i++;
        }
    }

    sdl2::Font Font::FindValidFontFor(char16_t ch)
    {
        for(auto &[idx, font] : this->font_faces)
        {
            if(TTF_GlyphIsProvided(font->font, ch))
            {
                return font->font;
            }
        }
        return nullptr;
    }

    static void ProcessStringImpl(sdl2::Font font, std::u16string &str, u32 &w, u32 &h)
    {
        if(str.empty()) return;
        int tw = 0;
        int th = 0;
        TTF_SizeUNICODE(font, reinterpret_cast<const u16*>(str.c_str()), &tw, &th);
        u32 tuw = static_cast<u32>(tw);
        u32 tuh = static_cast<u32>(th);
        if(tuw > w) w = tuw;
        h += tuh;
        str = u"";
    }

    #define _PU_TTF_PROCESS_TMP_STR_IMPL(font, str, w, h) { \
        i32 tw = 0; \
        i32 th = 0; \
        TTF_SizeUNICODE(font, reinterpret_cast<const u16*>(str.c_str()), &tw, &th); \
        u32 uw = static_cast<u32>(tw); \
        u32 uh = static_cast<u32>(th); \
        if(uw > w) w = uw; \
        h += uh; \
        str = u""; \
    }

    std::pair<u32, u32> Font::GetTextDimensions(String str)
    {
        u32 w = 0;
        u32 h = 0;
        auto font = this->TryGetFirstFont();
        if(font != nullptr)
        {
            std::u16string tmp_str;
            for(auto &ch: str.AsUTF16())
            {
                if(ch == u'\n') _PU_TTF_PROCESS_TMP_STR_IMPL(font, tmp_str, w, h)
                else tmp_str += ch;
            }
            if(!tmp_str.empty()) _PU_TTF_PROCESS_TMP_STR_IMPL(font, tmp_str, w, h)
        }
        return std::make_pair(w, h);
    }

    sdl2::Texture Font::RenderText(String str, ui::Color color)
    {
        auto font = this->TryGetFirstFont();
        if(font == nullptr) return nullptr;
        auto [w, _h] = ui::render::GetDimensions();
        auto srf = TTF_RenderUNICODE_Blended_Wrapped(font, reinterpret_cast<const u16*>(str.AsUTF16().c_str()), { color.R, color.G, color.B, color.A }, w);
        return ui::render::ConvertToTexture(srf);
    }
}

extern "C"
{
    pu::sdl2::Font TTF_CppWrap_FindValidFont(pu::sdl2::Font font, Uint16 ch)
    {
        if(font != nullptr)
        {
            auto raw_font_ptr = TTF_CppWrap_GetCppPtrRef(font);
            if(raw_font_ptr != nullptr)
            {
                auto font_ptr = reinterpret_cast<pu::ttf::Font*>(raw_font_ptr);
                auto nfont = font_ptr->FindValidFontFor(ch);
                if(nfont == nullptr) return font;
                return nfont;
            }
        }
        return font;
    }
}