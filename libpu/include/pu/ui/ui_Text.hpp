/**
 * Plutonium library
 * @file ui_Text.hpp
 * @brief Contains pu::ui::Text class
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/sdl2/sdl2_Types.hpp>
 
namespace pu::ui {
 
    /**
     * @brief Class that represents a text element to be rendered.
     * @note This class wraps text-rendering logic, and represents a text+color+font object that renders a corresponding Texture when any of them are changed.
     */
    class Text final {
        private:
            std::string text;
            std::string font_name;
            Color clr;
            sdl2::Texture text_tex;

            void UpdateTexture();

        public:
            /**
             * @brief Creates a new instance of a Text object.
             * @param text Text to render.
             * @param font_name Font name to use for rendering. Check the GetDefaultFont function for default font names.
             * @param flavor Flavor of the Text (per-style text type/kind).
             */
            Text(const std::string &text, const std::string &font_name, const u32 flavor);
            PU_SMART_CTOR(Text)
            ~Text();

            /**
             * @brief Gets the width of the text.
             * @return Width of the text.
             */
            s32 GetWidth();

            /**
             * @brief Gets the height of the text.
             * @return Height of the text.
             */
            s32 GetHeight();

            /**
             * @brief Sets the text to render.
             * @param text Text to render.
             * @note This will update the texture.
             */
            void SetText(const std::string &text);

            PU_CLASS_POD_GET(Text, text, std::string&)

            /**
             * @brief Sets the font to use for rendering.
             * @param font_name Font name to use for rendering. Check the GetDefaultFont function for default font names.
             * @note This will update the texture.
             */
            void SetFont(const std::string &font_name);

            PU_CLASS_POD_GET(Font, font_name, std::string&)

            /**
             * @brief Sets the color to use for rendering.
             * @param clr Color to use for rendering.
             * @note This will update the texture.
             */
            void SetColor(const Color &clr);

            PU_CLASS_POD_GET(Color, clr, Color)

            /**
             * @brief Gets the rendered Texture of the text.
             * @return Texture of the text.
             */
            inline sdl2::Texture GetTexture() {
                return this->text_tex;
            }
    };
 
}
 