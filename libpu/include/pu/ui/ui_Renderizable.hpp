/**
 * Plutonium library
 * @file ui_Renderizable.hpp
 * @brief Base interface for all UI elements in Plutonium, providing basic functionality for Group and Element.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Types.hpp>

namespace pu::ui {

    /**
     * @brief Enum containing the possible horizontal alignments of a Renderizable.
     */
    enum class HorizontalAlign {
        Left,
        Center,
        Right
    };

    /**
     * @brief Enum containing the possible vertical alignments of a Renderizable.
     */
    enum class VerticalAlign {
        Up,
        Center,
        Down
    };

    /**
     * @brief Pseudo-dimension (width/height) value used to indicate that the dimension should be set to the maximum possible value within the parent group (extending to the edges of the parent group).
     * @note This is used for the width and height of a Renderizable. Elements may return this pseudo-value in their GetWidth and GetHeight functions, but render functions should not receive this value.
     */
    constexpr s32 DimensionMatchParent = INT32_MIN;

    /**
     * @brief Pseudo-position (X/Y) value used to indicate that the position should be automatically calculated based on the parent group and the already added elements/subgroups in the group.
     * @note This is used for the X and Y coordinates of a Renderizable. Elements may return this pseudo-value in their GetX and GetY functions, but render functions should not receive this value.
     */
    constexpr s32 PositionAuto = INT32_MIN;

    /**
     * @brief Base interface for all UI elements in Plutonium, providing basic functionality for Group and Element.
     */
    class Renderizable {
        private:
            s32 render_x;
            s32 render_y;
            s32 render_width;
            s32 render_height;

        protected:
            bool visible;
            HorizontalAlign h_align;
            VerticalAlign v_align;

        public:
            /**
             * @brief Creates a new instance of a Renderizable object.
             */
            Renderizable() : render_x(0), render_y(0), render_width(0), render_height(0), visible(true), h_align(HorizontalAlign::Left), v_align(VerticalAlign::Up) {}
            virtual ~Renderizable() {}
            PU_SMART_CTOR(Renderizable)

            /**
             * @brief Gets the X position of the Renderizable.
             * @return X position of the Renderizable.
             */
            virtual s32 GetX() = 0;

            /**
             * @brief Gets the Y position of the Renderizable.
             * @return Y position of the Renderizable.
             */
            virtual s32 GetY() = 0;

            /**
             * @brief Gets the width of the Renderizable.
             * @return Width of the Renderizable.
             */
            virtual s32 GetWidth() = 0;

            /**
             * @brief Gets the height of the Renderizable.
             * @return Height of the Renderizable.
             */
            virtual s32 GetHeight() = 0;

            /**
             * @brief Prepares the Renderizable for rendering, setting the X, Y, width and height to render at.
             * @param x X position to render at.
             * @param y Y position to render at.
             * @param width Width to render at.
             * @param height Height to render at.
             * @note This function is used internally prior to rendering the element. It should not be used directly under normal circumstances.
             */
            void PrepareRender(const s32 x, const s32 y, const s32 width, const s32 height) {
                this->render_x = x;
                this->render_y = y;
                this->render_width = width;
                this->render_height = height;
            }

            /**
             * @brief Gets the X position to render the Renderizable at.
             * @return X position to render the Renderizable at.
             */
            inline s32 GetRenderX() {
                return this->render_x;
            }

            /**
             * @brief Gets the Y position to render the Renderizable at.
             * @return Y position to render the Renderizable at.
             */
            inline s32 GetRenderY() {
                return this->render_y;
            }

            /**
             * @brief Gets the width of the Renderizable to render.
             * @return Width of the Renderizable to render.
             */
            inline s32 GetRenderWidth() {
                return this->render_width;
            }

            /**
             * @brief Gets the height of the Renderizable to render.
             * @return Height of the Renderizable to render.
             */
            inline s32 GetRenderHeight() {
                return this->render_height;
            }

            PU_CLASS_POD_GETSET(Visible, visible, bool)

            PU_CLASS_POD_GETSET(HorizontalAlign, h_align, HorizontalAlign)
            PU_CLASS_POD_GETSET(VerticalAlign, v_align, VerticalAlign)
    };

    /**
     * @brief Macro to expand the X and Y coordinates of a Renderizable to render, as arguments.
     * @note This is usable from a member function of a Renderizable or a derived class.
     */
    #define PU_UI_RENDER_XY this->GetRenderX(), this->GetRenderY()

    /**
     * @brief Macro to expand the width and height of a Renderizable to render, as arguments.
     * @note This is usable from a member function of a Renderizable or a derived class.
     */
    #define PU_UI_RENDER_WH this->GetRenderWidth(), this->GetRenderHeight()

    /**
     * @brief Macro to expand the X, Y, width and height of a Renderizable to render, as arguments.
     * @note This is usable from a member function of a Renderizable or a derived class.
     */
    #define PU_UI_RENDER_XYWH this->GetRenderX(), this->GetRenderY(), this->GetRenderWidth(), this->GetRenderHeight()

}
