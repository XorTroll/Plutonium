/**
 * Plutonium library
 * @file elm_Separator.hpp
 * @brief Represents a simple single-pixel separator.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui::elm {

    enum class SeparatorOrientation {
        Horizontal,
        Vertical
    };

    /**
     * @brief Represents a simple single-pixel separator.
     */
    class Separator final : public Element {
        private:
            s32 x;
            s32 y;
            s32 length;
            SeparatorOrientation orientation;
            Color clr;

        public:
            /**
             * @brief Creates a new instance of a Separator.
             * @param x X position of the Separator.
             * @param y Y position of the Separator.
             * @param length Length of the Separator.
             * @param orientation Orientation of the Separator.
             * @note The Separator will be created with the color of the active Style.
             */
            Separator(const s32 x, const s32 y, const s32 length, const SeparatorOrientation orientation) : Element(), x(x), y(y), length(length), orientation(orientation), clr(GetStyle()->GetSeparatorColor()) {}
            PU_SMART_CTOR(Separator)

            inline bool SupportsFocus() override {
                return false;
            }

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Button.
             * @param x New X position to set.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the Button.
             * @param y New Y position to set.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            inline s32 GetWidth() override {
                switch(this->orientation) {
                    case SeparatorOrientation::Horizontal:
                        return this->length;
                    case SeparatorOrientation::Vertical:
                        return 1;
                    default:
                        return 0;
                }
            }

            inline s32 GetHeight() override {
                switch(this->orientation) {
                    case SeparatorOrientation::Horizontal:
                        return 1;
                    case SeparatorOrientation::Vertical:
                        return this->length;
                    default:
                        return 0;
                }
            }

            /**
             * @brief Sets the Length of the Separator.
             * @param length New length to set.
             */
            inline void SetLength(const s32 length) {
                this->length = length;
            }

            PU_CLASS_POD_GETSET(Orientation, orientation, SeparatorOrientation)
            PU_CLASS_POD_GETSET(Color, clr, Color)
            
            void OnRender(render::Renderer::Ref &drawer) override;

            bool OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override {
                return false;
            }
    };

}
