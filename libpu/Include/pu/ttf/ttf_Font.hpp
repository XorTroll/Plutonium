
#pragma once
#include <pu/sdl2/sdl2_System.hpp>
#include <pu/ui/ui_Types.hpp>
#include <functional>
#include <map>

namespace pu::ttf {

    using FontFaceDisposingFunction = std::function<void(void*)>;

    inline void EmptyFontFaceDisposingFunction(void*) {
        // Just do nothing :P
    }

    struct FontFace {
        TTF_Font *font;
        void *ptr;
        size_t ptr_sz;
        FontFaceDisposingFunction dispose_fn;
        i32 font_size;

        FontFace() : font(nullptr), ptr(nullptr), ptr_sz(0), dispose_fn(&EmptyFontFaceDisposingFunction), font_size(0) {}

        inline bool IsSourceValid() {
            // AKA - is the base ptr and size valid?
            if(this->ptr != nullptr) {
                if(this->ptr_sz > 0) {
                    return true;
                }
            }
            return false;
        }

        void Prepare(void *ptr, size_t size, FontFaceDisposingFunction disp_fn) {
            this->ptr = ptr;
            this->ptr_sz = size;
            this->dispose_fn = disp_fn;
        }

        void Load(u32 f_size, void *font_class_ptr) {
            this->DisposeFont();
            this->font = TTF_OpenFontRW(SDL_RWFromMem(this->ptr, this->ptr_sz), 1, f_size);
            this->font_size = f_size;
            if(this->font != nullptr) {
                TTF_CppWrap_SetCppPtrRef(this->font, font_class_ptr);
            }
        }

        void DisposeFont() {
            if(this->font != nullptr) {
                TTF_CloseFont(this->font);
                this->font = nullptr;
            }
        }

        void DisposeAll() {
            this->DisposeFont();
            if(this->IsSourceValid()) {
                (this->dispose_fn)(this->ptr);
                this->ptr = nullptr;
                this->ptr_sz = 0;
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

            i32 LoadFromMemory(void *ptr, size_t size, FontFaceDisposingFunction disp_fn);
            i32 LoadFromFile(const std::string &path);
            void Unload(i32 font_idx);
            void SetSize(u32 size);

            sdl2::Font FindValidFontFor(char16_t ch);
            sdl2::Texture RenderText(const std::string &str, ui::Color color);
    };
}