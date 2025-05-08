/**
 * Plutonium library
 * @file ui_Layer.hpp
 * @brief Contains pu::ui::Layer class
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <vector>
#include <bits/stdc++.h>

namespace pu::ui {

    /**
     * @brief Type representing a Layer: Layers are the base objects for rendering, and are rendered on top of each other, where only the last (input-supporting) Layer will capture input.
     * @note Layout, Dialog and Toast all are implementations of this class.
     */
    class Layer {
        private:
            bool is_active;

        public:
            Layer() : is_active(false) {}
            virtual ~Layer() {}
            PU_SMART_CTOR(Layer)

            /**
             * @brief Returns whether the Layer captures input.
             * @return Whether the Layer captures input.
             */
            virtual bool CapturesInput() = 0;

            /**
             * @brief Function called when the Layer is added to the Application (aka when it becomes active).
             */
            virtual void OnStart() = 0;

            /**
             * @brief Function called when the Layer is removed from the Application (aka after it stops being active).
             */
            virtual void OnStop() = 0;

            /**
             * @brief Function called when the Layer is rendered.
             * @param drawer The Renderer instance to use for rendering.
             */
            virtual void OnRender(render::Renderer::Ref &drawer) = 0;

            /**
             * @brief Function called when Layer input is handled.
             * @param keys_down Keys that are currently being pressed.
             * @param keys_up Keys that are currently being released.
             * @param keys_held Keys that are currently held.
             * @param touch_pos Position of the touch on the screen.
             * @note This method is called internally. It should not be called manually under general circumstances.
             * @note This function will only be called (each rendering loop) for the topmost Layer that captures input.
             */
            virtual void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) = 0;

            /**
             * @brief Gets whether the Layer is active.
             * @return Whether the Layer is active.
             */
            inline bool IsActive() {
                return this->is_active;
            }

            /**
             * @brief Sets whether the Layer is active.
             * @param active Whether the Layer should be active.
             * @note This function should be used by the Layer itself to indicate it's finished (for instance, calling it from OnRender when it's done).
             */
            inline void SetActive(const bool active) {
                this->is_active = active;
            }
    };
 
}
 