
#pragma once
#include <pu/sdl2/sdl2_System.hpp>
#include <cstdio>
#include <map>

namespace pu::ttf {

    struct FontFace {
        TTF_Font *font;
        SDL_RWops *data;
        i32 font_size;

        FontFace() : font(nullptr), data(nullptr), font_size(0) {}

        void AssignData(void *ptr, size_t size) {
            this->Dispose();
            this->data = SDL_RWFromMem(ptr, size);
        }

        void Load(u32 f_size) {
            this->Dispose(false);
            this->font = TTF_OpenFontRW(this->data, 0, f_size);
            this->font_size = f_size;
        }

        void Dispose(bool dispose_data = true) {
            if(this->font != nullptr) {
                TTF_CloseFont(this->font);
                this->font = nullptr;
            }
            if(dispose_data && (this->data != nullptr)) {
                SDL_RWclose(this->data);
                this->data = nullptr;
            }
        }
    };

    class Font {

        private:
            std::map<i32, FontFace> font_faces;
            u32 base_fnt_size;

        public:
            static constexpr i32 InvalidFontFaceIndex = -1;

            NX_CONSTEXPR bool IsValidFontFaceIndex(i32 index) {
                return index != InvalidFontFaceIndex;
            }

            Font(u32 base_font_size = 20);
            ~Font();

            i32 LoadFromMemory(void *ptr, size_t size);
            i32 LoadFromFile(const std::string &path);
            void Unload(i32 font_idx);
            void SetSize(u32 size);

            sdl2::Font FindValidFontFor(char16_t ch);
            sdl2::Texture RenderText(const std::string &str, SDL_Color color);
    };
}