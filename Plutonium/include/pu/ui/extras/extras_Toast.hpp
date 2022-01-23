
/*

    Plutonium library

    @file extras_Toast.hpp
    @brief An Overlay similar to Android's toast notifications
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Overlay.hpp>
#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::extras {

    class Toast final : public Overlay {
        public:
            static constexpr i32 DefaultY = 550;
            static constexpr i32 HeightAndTextHeightFactor = 3;
            static constexpr i32 HorizontalMargin = 50;
            static constexpr u8 BaseAlpha = 200;

        private:
            pu::ui::elm::TextBlock::Ref text;

            void AdjustDimensions();

        public:
            Toast(const std::string &text, const std::string &font_name, const Color text_clr, const Color bg_clr);
            PU_SMART_CTOR(Toast)

            void SetText(const std::string &text);
            void OnPreRender(render::Renderer::Ref &drawer) override;
            void OnPostRender(render::Renderer::Ref &drawer) override;
    };

}