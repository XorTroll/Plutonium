/**
 * Plutonium library
 * @file extras_Toast.hpp
 * @brief Toast class to show simple messages on the screen.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Overlay.hpp>
#include <pu/ui/elm/elm_TextBlock.hpp>

namespace pu::ui::extras {

    /**
     * @brief Overlay implementation that represents a simple message that appears on the screen.
     */
    class Toast final : public Overlay {
        public:
            // Self-explanatory constants

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
            /**
             * @brief Creates a new instance of a Toast.
             * @param text_block TextBlock to use for the Toast.
             * @param bg_clr Background color of the Toast.
             */
            Toast(elm::TextBlock::Ref &text_block, const Color bg_clr);
            PU_SMART_CTOR(Toast)

            PU_CLASS_POD_GETSET(HeightAndTextHeightFactor, height_and_text_height_factor, i32)
            PU_CLASS_POD_GETSET(HorizontalMargin, h_margin, i32)
            PU_CLASS_POD_GETSET(BaseAlpha, base_alpha, u8)

            /**
             * @brief Sets the text of the Toast.
             * @param text New text to set.
             */
            void SetText(const std::string &text);
            
            void OnPreRender(render::Renderer::Ref &drawer) override;
            void OnPostRender(render::Renderer::Ref &drawer) override;
    };

}
