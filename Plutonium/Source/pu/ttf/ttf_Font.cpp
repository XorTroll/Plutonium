#include <pu/ttf/ttf_Font.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <pu/ui/render/render_SDL2.hpp>

namespace pu::ttf
{

    Font::Font(u32 base_font_size) : font_size(base_font_size) {}

    Font::~Font()
    {
        for(auto &[idx, font] : this->font_faces)
        {
            font->DisposeAll();
        }
    }

    i32 Font::LoadFromMemory(void *ptr, size_t size, FontFaceDisposingFunction disp_fn)
    {
        i32 idx = rand();
        auto font = std::make_unique<FontFace>(ptr, size, disp_fn, this->font_size, reinterpret_cast<void*>(this));
        this->font_faces.insert(std::make_pair(idx, std::move(font)));
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
        auto it = this->font_faces.find(font_idx);
        if(it != this->font_faces.end()) this->font_faces.erase(it);
    }

    void Font::SetSize(u32 size)
    {
        this->font_size = size;
        for(auto &[idx, font]: this->font_faces)
        {
            font->Load(this->font_size, reinterpret_cast<void*>(this));
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

    std::pair<u32, u32> Font::GetTextDimensions(String str)
    {
        if(this->font_faces.empty()) return std::make_pair(0, 0);
        auto font = this->font_faces.begin()->second->font;
        if(font == nullptr) return std::make_pair(0, 0);
        i32 tw = 0;
        i32 th = 0;
        TTF_SizeUTF8(font, str.AsUTF8().c_str(), &tw, &th);
        return std::make_pair((u32)tw, (u32)th);
    }

    sdl2::Texture Font::RenderText(String str, ui::Color color)
    {
        if(this->font_faces.empty()) return nullptr;
        auto font = this->font_faces.begin()->second->font;
        if(font == nullptr) return nullptr;
        auto [w, _h] = ui::render::GetDimensions();
        auto srf = TTF_RenderUTF8_Blended_Wrapped(font, str.AsUTF8().c_str(), { color.R, color.G, color.B, color.A }, w);
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