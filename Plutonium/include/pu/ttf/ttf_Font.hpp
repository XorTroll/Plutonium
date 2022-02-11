
#pragma once
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/ui/ui_Types.hpp>
#include <vector>

namespace pu::ttf {

    class Font {
        private:
            using FontFaceDisposingFunction = void(*)(void*);

            struct FontFace {
                sdl2::Font font;
                void *ptr;
                size_t ptr_sz;
                FontFaceDisposingFunction dispose_fn;

                FontFace(void *buf, const size_t buf_size, FontFaceDisposingFunction disp_fn, const u32 font_sz, void *font_class_ptr) : font(nullptr), ptr(buf), ptr_sz(buf_size), dispose_fn(disp_fn) {
                    this->font = TTF_OpenFontRW(SDL_RWFromMem(this->ptr, this->ptr_sz), 1, font_sz);
                    if(this->font != nullptr) {
                        TTF_CppWrap_SetCppPtrRef(this->font, font_class_ptr);
                    }
                }

                FontFace() : font(nullptr), ptr(nullptr), ptr_sz(0), dispose_fn(EmptyFontFaceDisposingFunction) {}

                inline bool IsSourceValid() {
                    // AKA - is the base ptr and size valid?
                    return (this->ptr != nullptr) && (this->ptr_sz > 0);
                }

                void DisposeFont() {
                    if(this->font != nullptr) {
                        TTF_CloseFont(this->font);
                        this->font = nullptr;
                    }
                }

                void Dispose() {
                    this->DisposeFont();
                    if(this->IsSourceValid()) {
                        (this->dispose_fn)(this->ptr);
                        this->ptr = nullptr;
                        this->ptr_sz = 0;
                    }
                }

            };

            std::vector<std::pair<i32, std::unique_ptr<FontFace>>> font_faces;
            u32 font_size;

            inline sdl2::Font TryGetFirstFont() {
                if(!this->font_faces.empty()) {
                    return this->font_faces.begin()->second->font;
                }
                return nullptr;
            }

        public:
            static constexpr i32 InvalidFontFaceIndex = -1;
            static constexpr u32 DefaultFontSize = 25;

            static void EmptyFontFaceDisposingFunction(void*) {}

            static inline constexpr bool IsValidFontFaceIndex(const i32 index) {
                return index != InvalidFontFaceIndex;
            }

            Font(const u32 font_sz) : font_size(font_sz) {}
            ~Font();

            i32 LoadFromMemory(void *ptr, const size_t size, FontFaceDisposingFunction disp_fn);
            i32 LoadFromFile(const std::string &path);
            void Unload(const i32 font_idx);

            inline u32 GetFontSize() {
                return this->font_size;
            }

            sdl2::Font FindValidFontFor(const Uint16 ch);
            std::pair<u32, u32> GetTextDimensions(const std::string &str);
            sdl2::Texture RenderText(const std::string &str, const ui::Color clr);
    };

}