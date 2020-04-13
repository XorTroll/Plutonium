
#pragma once
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/pu_String.hpp>
#include <pu/ui/ui_Types.hpp>
#include <functional>
#include <map>

namespace pu::ttf
{
    using FontFaceDisposingFunction = std::function<void(void*)>;

    inline void EmptyFontFaceDisposingFunction(void*)
    {
        // Just do nothing :P
    }

    class Font
    {

        private:

            struct FontFace
            {
                sdl2::Font font;
                void *ptr;
                size_t ptr_sz;
                FontFaceDisposingFunction dispose_fn;

                FontFace(void *buf, size_t buf_size, FontFaceDisposingFunction disp_fn, u32 font_sz, void *font_class_ptr) : font(nullptr), ptr(buf), ptr_sz(buf_size), dispose_fn(disp_fn)
                {
                    this->font = TTF_OpenFontRW(SDL_RWFromMem(this->ptr, this->ptr_sz), 1, font_sz);
                    if(this->font != nullptr) TTF_CppWrap_SetCppPtrRef(this->font, font_class_ptr);
                }

                FontFace() : font(nullptr), ptr(nullptr), ptr_sz(0), dispose_fn(&EmptyFontFaceDisposingFunction) {}

                inline bool IsSourceValid()
                {
                    // AKA - is the base ptr and size valid?
                    if(this->ptr != nullptr)
                    {
                        if(this->ptr_sz > 0) return true;
                    }
                    return false;
                }

                void DisposeFont()
                {
                    if(this->font != nullptr)
                    {
                        TTF_CloseFont(this->font);
                        this->font = nullptr;
                    }
                }

                void Dispose()
                {
                    this->DisposeFont();
                    if(this->IsSourceValid())
                    {
                        (this->dispose_fn)(this->ptr);
                        this->ptr = nullptr;
                        this->ptr_sz = 0;
                    }
                }

            };

            std::vector<std::pair<i32, std::unique_ptr<FontFace>>> font_faces;
            u32 font_size;

            inline sdl2::Font TryGetFirstFont()
            {
                if(!this->font_faces.empty())
                {
                    return this->font_faces.begin()->second->font;
                }
                return nullptr;
            }

        public:

            static constexpr i32 InvalidFontFaceIndex = -1;
            static constexpr u32 DefaultFontSize = 25;

            NX_CONSTEXPR bool IsValidFontFaceIndex(i32 index)
            {
                return index != InvalidFontFaceIndex;
            }

            Font(u32 font_sz);
            ~Font();

            i32 LoadFromMemory(void *ptr, size_t size, FontFaceDisposingFunction disp_fn);
            i32 LoadFromFile(String path);
            void Unload(i32 font_idx);

            u32 GetFontSize()
            {
                return this->font_size;
            }

            sdl2::Font FindValidFontFor(char16_t ch);
            std::pair<u32, u32> GetTextDimensions(String str);
            SDL_Texture *RenderText(String str, ui::Color color);

    };
}