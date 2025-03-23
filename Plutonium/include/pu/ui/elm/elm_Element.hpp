/**
 * Plutonium library
 * @file elm_Element.hpp
 * @brief Base class for all UI elements in Plutonium, providing basic functionality for all of them.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/render/render_Renderer.hpp>

namespace pu::ui {

    class Container;

}

namespace pu::ui::elm {

    enum class HorizontalAlign {
        Left,
        Center,
        Right
    };

    enum class VerticalAlign {
        Up,
        Center,
        Down
    };

    /**
     * @brief Base class for all UI elements in Plutonium, providing basic functionality for all of them.
     */
    class Element {
        protected:
            bool visible;
            HorizontalAlign h_align;
            VerticalAlign v_align;
            Container *parent_container;

        public:
            /**
             * @brief Creates a new instance of an Element.
             */
            Element() : visible(true), h_align(HorizontalAlign::Left), v_align(VerticalAlign::Up), parent_container(nullptr) {}
            PU_SMART_CTOR(Element)
            virtual ~Element() {}

            /**
             * @brief Gets the X position of the Element.
             * @return X position of the Element.
             */
            virtual i32 GetX() = 0;

            /**
             * @brief Gets the Y position of the Element.
             * @return Y position of the Element.
             */
            virtual i32 GetY() = 0;

            /**
             * @brief Gets the width of the Element.
             * @return Width of the Element.
             */
            virtual i32 GetWidth() = 0;

            /**
             * @brief Gets the height of the Element.
             * @return Height of the Element.
             */
            virtual i32 GetHeight() = 0;

            /**
             * @brief Renders the Element on the screen.
             * @param drawer Renderer to use for rendering.
             * @param x X position to render the Element.
             * @param y Y position to render the Element.
             * @note This method is called by the Application. It should not be called manually.
             */
            virtual void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) = 0;

            /**
             * @brief Called before rendering the Element in order to handle input.
             * @param keys_down Keys that are currently being pressed.
             * @param keys_up Keys that are currently being released.
             * @param keys_held Keys that are currently held.
             * @param touch_pos Position of the touch on the screen.
             * @note This method is called by the Application. It should not be called manually.
             */
            virtual void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) = 0;

            /**
             * @brief Gets whether the Element is visible.
             * @return Whether the Element is visible.
             */
            inline bool IsVisible() {
                return this->visible;
            }

            /**
             * @brief Sets whether the Element is visible.
             * @param visible Whether the Element should be visible.
             * @note If the Element is not visible, it will not be rendered and input will not be handled.
             */
            inline void SetVisible(const bool visible) {
                this->visible = visible;
            }

            /**
             * @brief Sets the horizontal alignment of the Element.
             * @param align New horizontal alignment to set.
             */
            inline void SetHorizontalAlign(const HorizontalAlign align) {
                this->h_align = align;
            }

            /**
             * @brief Gets the horizontal alignment of the Element.
             * @return Horizontal alignment of the Element.
             */
            inline HorizontalAlign GetHorizontalAlign() {
                return this->h_align;
            }

            /**
             * @brief Sets the vertical alignment of the Element.
             * @param align New vertical alignment to set.
             */
            inline void SetVerticalAlign(const VerticalAlign align) {
                this->v_align = align;
            }

            /**
             * @brief Gets the vertical alignment of the Element.
             * @return Vertical alignment of the Element.
             */
            inline VerticalAlign GetVerticalAlign() {
                return this->v_align;
            }

            /**
             * @brief Sets the parent Container of the Element.
             * @param parent_container New parent Container to set.
             * @note This method is called by the underlying Application when rendering. It should not be called manually.
             */
            inline void SetParentContainer(Container *parent_container) {
                this->parent_container = parent_container;
            }
            
            /**
             * @brief Gets the actual X position of the Element, considering the parent Container (depends on alignment).
             * @return Actual X position of the Element.
             * @note This is the X value actually used for rendering.
             */
            i32 GetProcessedX();

            /**
             * @brief Gets the actual Y position of the Element, considering the parent Container (depends on alignment).
             * @return Actual Y position of the Element.
             * @note This is the Y value actually used for rendering.
             */
            i32 GetProcessedY();
    };

}
