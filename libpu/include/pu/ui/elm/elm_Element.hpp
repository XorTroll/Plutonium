/**
 * Plutonium library
 * @file elm_Element.hpp
 * @brief Base class for all UI elements in Plutonium, providing basic functionality for all of them.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Renderizable.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <chrono>

namespace pu::ui::elm {

    /**
     * @brief Base class for all UI elements in Plutonium, providing basic functionality for all of them.
     */
    class Element : public Renderizable, public std::enable_shared_from_this<Element> {
        public:
            PU_SMART_CTOR(Element)

            struct RenderContext {
                bool focus_handled;
                std::chrono::steady_clock::time_point last_focus_switch_time;
                elm::Element::Ref elem_focused;
                elm::Element::Ref elem_requesting_focus;
                bool any_group_scrolling;
            };

        private:
            bool focused;
            bool focus_requested;
            Element::Ref up_elem;
            Element::Ref down_elem;
            Element::Ref left_elem;
            Element::Ref right_elem;

            void SwitchFocus(Element::Ref &elem, RenderContext &ctx);

        public:
            /**
             * @brief Creates a new instance of an Element.
             */
            Element();
            virtual ~Element() {
                this->up_elem = nullptr;
                this->down_elem = nullptr;
                this->left_elem = nullptr;
                this->right_elem = nullptr;
            }

        public:
            /**
             * @brief Gets whether the Element supports (is responsive to) the focus functionality.
             * @return Whether the Element supports focus functionality.
             * @note If the Element does not support focus functionality, it will not be able to be focused.
             */
            virtual bool SupportsFocus() {
                return true;
            }

            /**
             * @brief Gets the keys to be pressed to move up the focus away from this Element.
             * @return Keys to be pressed to move up the focus away from this Element.
             * @note By default, any up keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusUpChangeKeysDown() {
                return HidNpadButton_AnyUp;
            }

            /**
             * @brief Gets the keys to be pressed to move down the focus away from this Element.
             * @return Keys to be pressed to move down the focus away from this Element.
             * @note By default, any down keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusDownChangeKeysDown() {
                return HidNpadButton_AnyDown;
            }

            /**
             * @brief Gets the keys to be pressed to move left the focus away from this Element.
             * @return Keys to be pressed to move left the focus away from this Element.
             * @note By default, any left keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusLeftChangeKeysDown() {
                return HidNpadButton_AnyLeft;
            }

            /**
             * @brief Gets the keys to be pressed to move right the focus away from this Element.
             * @return Keys to be pressed to move right the focus away from this Element.
             * @note By default, any right keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusRightChangeKeysDown() {
                return HidNpadButton_AnyRight;
            }

            /**
             * @brief Gets the keys to be pressed to move up the focus away from this Element.
             * @return Keys to be pressed to move up the focus away from this Element.
             * @note By default, any up keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusUpChangeKeysHeld() {
                return HidNpadButton_StickLUp | HidNpadButton_StickRUp;
            }

            /**
             * @brief Gets the keys to be pressed to move down the focus away from this Element.
             * @return Keys to be pressed to move down the focus away from this Element.
             * @note By default, any down keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusDownChangeKeysHeld() {
                return HidNpadButton_StickLDown | HidNpadButton_StickRDown;
            }

            /**
             * @brief Gets the keys to be pressed to move left the focus away from this Element.
             * @return Keys to be pressed to move left the focus away from this Element.
             * @note By default, any left keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusLeftChangeKeysHeld() {
                return HidNpadButton_StickLLeft | HidNpadButton_StickRLeft;
            }

            /**
             * @brief Gets the keys to be pressed to move right the focus away from this Element.
             * @return Keys to be pressed to move right the focus away from this Element.
             * @note By default, any right keys (D-pad or joysticks) are used.
             */
            virtual u64 GetFocusRightChangeKeysHeld() {
                return HidNpadButton_StickLRight | HidNpadButton_StickRRight;
            }

            /**
             * @brief Renders the Element on the screen at a given position.
             * @param drawer Renderer to use for rendering.
             * @param x X position to render the Element.
             * @param y Y position to render the Element.
             * @note This method is called internally. It should not be called manually under general circumstances.
             */
            virtual void OnRender(render::Renderer::Ref &drawer) = 0;

            /**
             * @brief Called in order to handle input.
             * @param keys_down Keys that are currently being pressed.
             * @param keys_up Keys that are currently being released.
             * @param keys_held Keys that are currently held.
             * @param touch_pos Position of the touch on the screen.
             * @return Whether the input was handled by the Element.
             * @note This method is called by internally. It should not be called manually under general circumstances.
             */
            virtual bool OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) = 0;

            /**
             * @brief Called in order to handle input.
             * @param keys_down Keys that are currently being pressed.
             * @param keys_up Keys that are currently being released.
             * @param keys_held Keys that are currently held.
             * @param touch_pos Position of the touch on the screen.
             * @param ctx Internal render context.
             * @return Whether the input was handled by the Element.
             * @note This method is called by internally. It should not be called manually under general circumstances.
             */
            bool PerformInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos, RenderContext &ctx);

            /**
             * @brief Gets whether the Element is focused.
             * @return Whether the Element is focused.
             */
            inline bool IsFocused() {
                return this->focused;
            }

            /**
             * @brief Sets whether the Element is focused.
             * @param focused Whether the Element should be focused.
             * @note This is used internally to handle focus changes. It should not be called manually under general circumstances.
             */
            inline void SetFocused(const bool focused) {
                this->focused = focused;
            }

            inline void RequestFocus() {
                if(this->focused) {
                    return;
                }
                this->focus_requested = true;
            }

            inline bool ConsumeFocusRequested() {
                const auto requested = this->focus_requested;
                this->focus_requested = false;
                return requested;
            }

            /**
             * @brief Sets the Element that will become focused when the focus moves up from this Element.
             * @param up_elem Element to set as the up Element.
             */
            inline void SetUpElement(Element::Ref up_elem) {
                this->up_elem = up_elem;
            }

            /**
             * @brief Resets the Element that will become focused when the focus moves up from this Element.
             */
            inline void ResetUpElement() {
                this->up_elem = nullptr;
            }

            /**
             * @brief Sets the Element that will become focused when the focus moves down from this Element.
             * @param down_elem Element to set as the down Element.
             */
            inline void SetDownElement(Element::Ref down_elem) {
                this->down_elem = down_elem;
            }

            /**
             * @brief Resets the Element that will become focused when the focus moves down from this Element.
             */
            inline void ResetDownElement() {
                this->down_elem = nullptr;
            }

            /**
             * @brief Sets the Element that will become focused when the focus moves left from this Element.
             * @param left_elem Element to set as the left Element.
             */
            inline void SetLeftElement(Element::Ref left_elem) {
                this->left_elem = left_elem;
            }

            /**
             * @brief Resets the Element that will become focused when the focus moves left from this Element.
             */
            inline void ResetLeftElement() {
                this->left_elem = nullptr;
            }

            /**
             * @brief Sets the Element that will become focused when the focus moves right from this Element.
             * @param right_elem Element to set as the right Element.
             */
            inline void SetRightElement(Element::Ref right_elem) {
                this->right_elem = right_elem;
            }

            /**
             * @brief Resets the Element that will become focused when the focus moves right from this Element.
             */
            inline void ResetRightElement() {
                this->right_elem = nullptr;
            }
    };

}
