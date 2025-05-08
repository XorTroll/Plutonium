/**
 * Plutonium library
 * @file elm_Button.hpp
 * @brief Represents a simple button that can be clicked and interacted with.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <functional>
#include <pu/ui/ui_Text.hpp>
#include <pu/ui/ui_TouchDetector.hpp>
#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui::elm {

    /**
     * @brief Represents a simple button that can be clicked and interacted with.
     */
    class Button final : public Element {
        public:
            /**
             * @brief Callback that is called when the Button is clicked.
             */
            using OnClickCallback = std::function<void()>;

            enum class TextPlacement {
                Center,
                Left,
                Right
            };

        private:
            s32 x;
            s32 y;
            s32 width;  
            s32 height;
            u32 radius;
            u32 border_thickness;
            Color border_clr;
            u32 text_margin_left;
            u32 text_margin_right;
            Text::Ref text;
            TextPlacement text_placement;
            Color bg_clr;
            Color bg_held_clr;
            OnClickCallback on_click_cb;
            TouchDetector touch_detector;
            u64 touch_key;

            void HandleClick();

        public:
            /**
             * @brief Creates a new instance of a Button.
             * @param x X position of the Button.
             * @param y Y position of the Button.
             * @param width Width of the Button.
             * @param height Height of the Button.
             * @param flavor Flavor of the Button (per-style button type/kind).
             * @param text Text of the Button.
             * @note The Button will be created with the background color / background held color of the active Style.
             */
            Button(const s32 x, const s32 y, const s32 width, const s32 height, const u32 flavor, Text::Ref text) : Element(), x(x), y(y), width(width), height(height), radius(GetStyle()->GetButtonRadius()), border_thickness(GetStyle()->GetButtonBorderThickness(flavor)), border_clr(GetStyle()->GetButtonBorderColor(flavor)), text_margin_left(GetStyle()->GetButtonTextMarginLeft()), text_margin_right(GetStyle()->GetButtonTextMarginRight()), text(text), text_placement(TextPlacement::Center), bg_clr(GetStyle()->GetButtonBackgroundColor(flavor)), bg_held_clr(GetStyle()->GetButtonBackgroundHeldColor(flavor)), on_click_cb(nullptr), touch_detector(), touch_key(0) {}
            PU_SMART_CTOR(Button)

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
                return this->width;
            }

            /**
             * @brief Sets the width of the Button.
             * @param width New width to set.
             */
            inline void SetWidth(const s32 width) {
                this->width = width;
            }

            inline s32 GetHeight() override {
                return this->height;
            }

            /**
             * @brief Sets the height of the Button.
             * @param height New height to set.
             */
            inline void SetHeight(const s32 height) {
                this->height = height;
            }

            PU_CLASS_POD_GETSET(TextMarginLeft, text_margin_left, u32)
            PU_CLASS_POD_GETSET(TextMarginRight, text_margin_right, u32)

            PU_CLASS_POD_GETSET(Text, text, Text::Ref)
            PU_CLASS_POD_GETSET(TextPlacement, text_placement, TextPlacement)
            PU_CLASS_POD_GETSET(Radius, radius, u32)
            PU_CLASS_POD_GETSET(TouchKey, touch_key, u64)

            /**
             * @brief Sets the font of the content of the Button.
             * @param font_name New font to set.
             */
            inline void SetOnClick(OnClickCallback on_click_cb) {
                this->on_click_cb = on_click_cb;
            }
            
            void OnRender(render::Renderer::Ref &drawer) override;
            bool OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };

}
