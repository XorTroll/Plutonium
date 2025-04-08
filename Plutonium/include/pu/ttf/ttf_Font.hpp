/**
 * Plutonium library
 * @file ttf_Font.hpp
 * @brief Font rendering support, high-level wrapper for SDL2_ttf
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/ui/ui_Types.hpp>
#include <vector>

namespace pu::ttf {

    /**
     * @brief High-level wrapper for SDL2_ttf font rendering.
     */
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

            std::vector<std::pair<s32, std::unique_ptr<FontFace>>> font_faces;
            u32 font_size;

            inline sdl2::Font TryGetFirstFont() {
                if(!this->font_faces.empty()) {
                    return this->font_faces.begin()->second->font;
                }
                return nullptr;
            }

        public:
            /**
             * @brief Constant representing an invalid font face index.
             */
            static constexpr s32 InvalidFontFaceIndex = -1;

            /**
             * @brief Default font size to use when creating a new font.
             */
            static constexpr u32 DefaultFontSize = 25;

            /**
             * @brief Function to use when disposing a font face that does not need to be disposed.
             */
            static void EmptyFontFaceDisposingFunction(void*) {}

            /**
             * @brief Checks if a font face index is valid.
             * @param index Index to check.
             * @return Whether the index is valid.
             */
            static inline constexpr bool IsValidFontFaceIndex(const s32 index) {
                return index != InvalidFontFaceIndex;
            }

            /**
             * @brief Creates a new Font instance with the specified font size.
             * @param font_sz Font size to use.
             */
            Font(const u32 font_sz) : font_size(font_sz) {}
            ~Font();

            /**
             * @brief Loads a font from memory data.
             * @param ptr Pointer to the font data.
             * @param size Size of the font data.
             * @param disp_fn Function to call when the font is no longer needed and needs disposing.
             * @return Index of the loaded font face.
             */
            s32 LoadFromMemory(void *ptr, const size_t size, FontFaceDisposingFunction disp_fn);

            /**
             * @brief Loads a font from a file.
             * @param path Path to the font file.
             * @return Index of the loaded font face.
             */
            s32 LoadFromFile(const std::string &path);

            /**
             * @brief Unloads a font face.
             * @param font_idx Index of the font face to unload.
             */
            void Unload(const s32 font_idx);

            /**
             * @brief Sets the font size used by the Font instance.
             * @param font_sz Font size used.
             */
            inline u32 GetFontSize() {
                return this->font_size;
            }

            /**
             * @brief Finds the first available font face that can render the specified character.
             * @param ch Character to find a font face for.
             */
            sdl2::Font FindValidFontFor(const Uint16 ch);

            /**
             * @brief Gets the dimensions of a text string rendered with the Font instance.
             * @param str Text string to get the dimensions of.
             * @return Dimension value pair with the width and height of the text string.
             */
            std::pair<u32, u32> GetTextDimensions(const std::string &str);

            /**
             * @brief Renders a text string with the Font instance.
             * @param str Text string to render.
             * @param clr Color to render the text with.
             * @return Raw SDL2 texture containing the rendered text.
             */
            sdl2::Texture RenderText(const std::string &str, const ui::Color clr);
    };

}
