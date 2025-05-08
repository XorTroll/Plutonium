#include <pu/ttf/ttf_Font.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <pu/ui/render/render_SDL2.hpp>
#include <sstream>

namespace pu::ttf {

    namespace {

        void FileBufferFontFaceDisposingFunction(void *ptr) {
            if(ptr != nullptr) {
                auto file_buf = reinterpret_cast<u8*>(ptr);
                delete[] file_buf;
            }
        }

        sdl2::Texture RenderMultilineText(sdl2::Font font, const std::string &text, const SDL_Color color) {
            std::istringstream stream(text);
            std::string line;
            std::vector<SDL_Surface*> line_srfs;

            s32 max_width = 0;
            s32 total_height = 0;
            while(std::getline(stream, line)) {
                if(line.empty()) {
                    line = " ";
                }

                auto surface = TTF_RenderUTF8_Blended(font, line.c_str(), color);
                if(surface == nullptr) {
                    continue;
                }
        
                line_srfs.push_back(surface);
                if(surface->w > max_width) {
                    max_width = surface->w;
                }
                total_height += surface->h;
            }
        
            // Initialize with fg and 0 alpha (like SDL_ttf does)
            auto final_srf = SDL_CreateRGBSurface(SDL_SWSURFACE, max_width, total_height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
            const auto pixel = (color.r << 16) | (color.g << 8) | color.b;
            SDL_FillRect(final_srf, nullptr, pixel);
        
            // Blit lines onto the final surface
            s32 y = 0;
            for(auto line_srf : line_srfs) {
                SDL_Rect dst = {
                    .x = 0,
                    .y = y,
                    .w = line_srf->w,
                    .h = line_srf->h
                };
                SDL_BlitSurface(line_srf, nullptr, final_srf, &dst);
                y += line_srf->h;
                SDL_FreeSurface(line_srf);
            }

            auto tex = ui::render::ConvertToTexture(final_srf);
            SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
            return tex;
        }

    }

    Font::~Font() {
        for(auto &[idx, font] : this->font_faces) {
            font->Dispose();
        }
    }

    s32 Font::LoadFromMemory(void *ptr, const size_t size, FontFaceDisposingFunction disp_fn) {
        const auto idx = rand();
        auto font = std::make_unique<FontFace>(ptr, size, disp_fn, this->font_size, reinterpret_cast<void*>(this));
        this->font_faces.push_back({ idx, std::move(font) });
        return idx;
    }

    s32 Font::LoadFromFile(const std::string &path) {
        auto f = fopen(path.c_str(), "rb");
        if(f) {
            fseek(f, 0, SEEK_END);
            const auto f_size = ftell(f);
            rewind(f);
            if(f_size > 0) {
                auto font_buf = new u8[f_size]();
                fread(font_buf, 1, f_size, f);
                fclose(f);
                return this->LoadFromMemory(font_buf, f_size, FileBufferFontFaceDisposingFunction);
            }
            fclose(f);
        }

        return InvalidFontFaceIndex;
    }

    void Font::Unload(const s32 font_idx) {
        u32 i = 0;
        for(auto &[idx, font]: this->font_faces) {
            if(idx == font_idx) {
                this->font_faces.erase(this->font_faces.begin() + i);
                break;
            }
            i++;
        }
    }

    sdl2::Font Font::FindValidFontFor(const Uint16 ch) {
        for(const auto &[idx, font] : this->font_faces) {
            if(TTF_GlyphIsProvided(font->font, ch)) {
                return font->font;
            }
        }

        return nullptr;
    }

    namespace {

        inline void ProcessLineDimensionsImpl(sdl2::Font font, std::string &str, u32 &w, u32 &h) {
            s32 str_w = 0;
            s32 str_h = 0;
            TTF_SizeUTF8(font, str.c_str(), &str_w, &str_h);

            const auto str_w_32 = static_cast<u32>(str_w);
            const auto str_h_32 = static_cast<u32>(str_h);
            if(str_w_32 > w) {
                w = str_w_32;
            }
            h += str_h_32;
            str = "";
        }

    }

    std::pair<u32, u32> Font::GetTextDimensions(const std::string &str) {
        u32 w = 0;
        u32 h = 0;
        auto font = this->TryGetFirstFont();
        if(font != nullptr) {
            std::string tmp_line;
            for(const auto &ch: str) {
                if(ch == '\n') {
                    ProcessLineDimensionsImpl(font, tmp_line, w, h);
                }
                else {
                    tmp_line += ch;
                }
            }
            if(!tmp_line.empty()) {
                ProcessLineDimensionsImpl(font, tmp_line, w, h);
            }
        }
        return { w, h };
    }

    sdl2::Texture Font::RenderText(const std::string &str, const ui::Color clr) {
        auto font = this->TryGetFirstFont();
        if(font != nullptr) {
            return RenderMultilineText(font, str, { clr.r, clr.g, clr.b, clr.a });
        }
        else {
            return nullptr;
        }
    }

}

extern "C" {

    pu::sdl2::Font TTF_CppWrap_FindValidFont(pu::sdl2::Font font, Uint16 ch) {
        if(font != nullptr) {
            auto raw_font_ptr = TTF_CppWrap_GetCppPtrRef(font);
            if(raw_font_ptr != nullptr) {
                auto font_ptr = reinterpret_cast<pu::ttf::Font*>(raw_font_ptr);
                auto find_font = font_ptr->FindValidFontFor(ch);
                if(find_font == nullptr) {
                    return font;
                }
                else {
                    return find_font;
                }
            }
        }
        return font;
    }

}
