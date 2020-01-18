#include <pu/ttf/ttf_Font.hpp>
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/ui/ui_Application.hpp>
#include <pu/render/render_Utils.hpp>

namespace pu::ttf {

    Font::Font(u32 base_font_size) : base_fnt_size(base_font_size) {}

    Font::~Font() {
        for(auto &[idx, font] : this->font_faces) {
            font.Dispose();
        }
    }

    i32 Font::LoadFromMemory(void *ptr, size_t size) {
        FontFace font;
        font.AssignData(ptr, size);
        font.Load(this->base_fnt_size);
        TTF_CppWrap_SetCppPtrRef(font.font, reinterpret_cast<void*>(this));
        i32 idx = rand();
        this->font_faces.insert(std::make_pair(idx, font));
        return idx;
    }

    i32 Font::LoadFromFile(const std::string &path) {
        FILE *f = fopen(path.c_str(), "rb");
        if(f) {
            fseek(f, 0, SEEK_END);
            auto size = ftell(f);
            rewind(f);

            if(size > 0) {
                // C malloc since SDL will call free()
                auto fontbuf = malloc(size);
                fread(fontbuf, 1, size, f);
                fclose(f);
                return this->LoadFromMemory(fontbuf, size);
            }
        }

        return InvalidFontFaceIndex;
    }

    void Font::Unload(i32 font_idx) {
        auto it = this->font_faces.find(font_idx);
        if(it != this->font_faces.end()) {
            this->font_faces.erase(it);
        }
    }

    void Font::SetSize(u32 size) {
        for(auto &[idx, font]: this->font_faces) {
            font.Load(size);
        }
    }

    sdl2::Font Font::FindValidFontFor(char16_t ch) {
        for(auto &[idx, font] : this->font_faces) {
            if(TTF_GlyphIsProvided(font.font, ch)) {
                return font.font;
            }
        }
        return nullptr;
    }

    sdl2::Texture Font::RenderText(const std::string &str, SDL_Color color) {
        if(this->font_faces.empty()) {
            return nullptr;
        }
        auto font = this->font_faces.begin()->second.font;
        if(font == nullptr) {
            return nullptr;
        }
        auto app = pu::ui::GetApplication();
        if(app) {
            auto [w, _h] = app->GetDimensions();
            auto srf = TTF_RenderUTF8_Blended_Wrapped(font, str.c_str(), color, w);
            return render::ConvertToTexture(srf);
        }
        return nullptr;
    }
}

extern "C" {
    pu::sdl2::Font TTF_CppWrap_FindValidFont(pu::sdl2::Font font, Uint16 ch) {
        if(font != nullptr) {
            auto font_ptr = reinterpret_cast<pu::ttf::Font*>(TTF_CppWrap_GetCppPtrRef(font));
            auto nfont = font_ptr->FindValidFontFor(ch);
            if(nfont == nullptr) {
                return font;
            }
            return nfont;
        }
        return font;
    }
}