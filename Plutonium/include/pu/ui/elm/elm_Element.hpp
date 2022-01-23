
/*

    Plutonium library

    @file Element.hpp
    @brief An Element is the base of Plutonium UI's content.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

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

    class Element {
        protected:
            bool visible;
            HorizontalAlign h_align;
            VerticalAlign v_align;
            Container *parent_container;

        public:
            Element() : visible(true), h_align(HorizontalAlign::Left), v_align(VerticalAlign::Up), parent_container(nullptr) {}
            PU_SMART_CTOR(Element)
            virtual ~Element() {}

            virtual i32 GetX() = 0;
            virtual i32 GetY() = 0;
            virtual i32 GetWidth() = 0;
            virtual i32 GetHeight() = 0;
            virtual void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) = 0;
            virtual void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) = 0;

            inline bool IsVisible() {
                return this->visible;
            }

            inline void SetVisible(const bool visible) {
                this->visible = visible;
            }

            inline void SetHorizontalAlign(const HorizontalAlign align) {
                this->h_align = align;
            }

            inline HorizontalAlign GetHorizontalAlign() {
                return this->h_align;
            }

            inline void SetVerticalAlign(const VerticalAlign align) {
                this->v_align = align;
            }

            inline VerticalAlign GetVerticalAlign() {
                return this->v_align;
            }

            inline void SetParentContainer(Container *parent_container) {
                this->parent_container = parent_container;
            }
            
            i32 GetProcessedX();
            i32 GetProcessedY();
    };

}