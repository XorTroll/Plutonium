
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
            static constexpr i32 DefaulHeightAndTextHeightFactor = 3;
            static constexpr i32 DefaulHorizontalMargin = 50;
            static constexpr u8 DefaulBaseAlpha = 200;

        private:
            pu::ui::elm::TextBlock::Ref text;
            i32 height_and_text_height_factor;
            i32 h_margin;
            u8 base_alpha;

            void AdjustDimensions();

        public:
            Toast(elm::TextBlock::Ref &text_block, const Color bg_clr);
            PU_SMART_CTOR(Toast)

            PU_CLASS_POD_GETSET(HeightAndTextHeightFactor, height_and_text_height_factor, i32)
            PU_CLASS_POD_GETSET(HorizontalMargin, h_margin, i32)
            PU_CLASS_POD_GETSET(BaseAlpha, base_alpha, u8)

            void SetText(const std::string &text);
            void OnPreRender(render::Renderer::Ref &drawer) override;
            void OnPostRender(render::Renderer::Ref &drawer) override;
    };

}
