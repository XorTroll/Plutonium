
/*

    Plutonium library

    @file TextBlock.hpp
    @brief A TextBlock is a very useful Element which is used to draw text on the screen.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm {

    class TextBlock : public Element {
        public:
            static constexpr Color DefaultColor = { 0, 0, 0, 0xFF };

        private:
            i32 x;
            i32 y;
            Color clr;
            std::string text;
            sdl2::Texture text_tex;
            std::string fnt_name;
        
        public:
            TextBlock(const i32 x, const i32 y, const std::string &text);
            PU_SMART_CTOR(TextBlock)
            ~TextBlock();

            inline i32 GetX() override {
                return this->x;
            }

            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            inline void SetY(const i32 y) {
                this->y = y;
            }

            i32 GetWidth() override;
            i32 GetHeight() override;

            inline std::string GetText() {
                return this->text;
            }

            void SetText(const std::string &text);
            void SetFont(const std::string &font_name);
            
            inline Color GetColor() {
                return this->clr;
            }
            
            void SetColor(const Color clr);
            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {}
    };

}