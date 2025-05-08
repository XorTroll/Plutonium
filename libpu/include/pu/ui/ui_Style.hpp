/**
 * Plutonium library
 * @file ui_Style.hpp
 * @brief Class for managing UI styles in Plutonium.
 * @author XorTroll
 * @copyright XorTroll
*/

#pragma once
#include <pu/ui/render/render_Renderer.hpp>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui {

    enum DefaultButtonFlavor : u32 {
        DefaultButtonFlavor_Default
    };

    enum DefaultTextFlavor : u32 {
        DefaultTextFlavor_Default
    };

    /**
     * @brief Class for managing general UI properties in Plutonium.
     * @note This class is used to manage the style of UI and elements in Plutonium.
     * @note It's recommended to inherit this class to create your own Style.
     */
    class Style {
        public:
            // Default style parameters

            static constexpr s64 DefaultFocusSwitchMinimumIntervalMs = 80;
            static constexpr u32 DefaultTouchScrollThreshold = 10;

            // Default layout parameters
            static constexpr Color DefaultLayoutBackgroundColor = { 225, 225, 225, 255 };

            // Default group parameters
            static constexpr Color DefaultGroupBackgroundColor = { 0, 0, 0, 0 };
            static constexpr Color DefaultGroupBorderSeparatorColor = { 0, 0, 0, 255 };
            static constexpr s32 DefaultGroupScrollbarMargin = 0;
            static constexpr s32 DefaultGroupScrollbarSize = 10;
            static constexpr Color DefaultGroupScrollbarColor = { 0, 0, 0, 255 };

            // Default color variation parameters
            static constexpr u32 DefaultColorVariateSpeedSteps = 30;

            // Default text parameters
            static constexpr Color DefaultTextColor = { 0, 0, 0, 255 };

            // Default button parameters
            static constexpr u32 DefaultButtonRadius = 0;
            static constexpr u32 DefaultButtonTextMarginLeft = 0;
            static constexpr u32 DefaultButtonTextMarginRight = 0;
            static constexpr u32 DefaultButtonBorderThickness = 0;
            static constexpr Color DefaultButtonBorderColor = { 0, 0, 0, 255 };
            static constexpr Color DefaultButtonBackgroundColor = {  50, 80, 240, 255 };
            static constexpr Color DefaultButtonBackgroundHeldColor = { 50, 100, 242, 255 };

            // Default progress bar parameters
            static constexpr Color DefaultProgressBarProgressColor = { 50, 80, 240, 255 };
            static constexpr Color DefaultProgressBarBackgroundColor = { 0, 0, 0, 0 };

            // Default separator parameters
            static constexpr Color DefaultSeparatorColor = { 0, 0, 0, 255 };

        private:
            s64 focus_switch_min_interval_ms;
            u32 touch_scroll_threshold;

            Color lyt_bg_clr;

            Color group_bg_clr;
            Color group_border_separator_clr;
            s32 group_scrollbar_margin;
            s32 group_scrollbar_size;
            Color group_scrollbar_clr;

            u32 color_variate_speed_steps;

            u32 button_radius;
            u32 button_text_margin_left;
            u32 button_text_margin_right;

            Color pbar_progress_clr;
            Color pbar_bg_clr;

            Color separator_clr;

        public:
            /**
             * @brief Creates a new instance of the default Style object.
             * @note This constructor initializes the style with default values.
             */
            Style() :   focus_switch_min_interval_ms(DefaultFocusSwitchMinimumIntervalMs),
                        touch_scroll_threshold(DefaultTouchScrollThreshold),
                        lyt_bg_clr(DefaultLayoutBackgroundColor),
                        group_bg_clr(DefaultGroupBackgroundColor),
                        group_border_separator_clr(DefaultGroupBorderSeparatorColor),
                        group_scrollbar_margin(DefaultGroupScrollbarMargin),
                        group_scrollbar_size(DefaultGroupScrollbarSize),
                        group_scrollbar_clr(DefaultGroupScrollbarColor),
                        color_variate_speed_steps(DefaultColorVariateSpeedSteps),
                        button_radius(DefaultButtonRadius),
                        button_text_margin_left(DefaultButtonTextMarginLeft),
                        button_text_margin_right(DefaultButtonTextMarginRight),
                        pbar_progress_clr(DefaultProgressBarProgressColor), 
                        pbar_bg_clr(DefaultProgressBarBackgroundColor),
                        separator_clr(DefaultSeparatorColor) {}
            virtual ~Style() {}
            PU_SMART_CTOR(Style)

            PU_CLASS_POD_GETSET(FocusSwitchMinimumInterval, focus_switch_min_interval_ms, s64)
            PU_CLASS_POD_GETSET(TouchScrollThreshold, touch_scroll_threshold, u32)

            PU_CLASS_POD_GETSET(LayoutBackgroundColor, lyt_bg_clr, Color)

            PU_CLASS_POD_GETSET(GroupBackgroundColor, group_bg_clr, Color)
            PU_CLASS_POD_GETSET(GroupBorderSeparatorColor, group_border_separator_clr, Color)
            PU_CLASS_POD_GETSET(GroupScrollbarMargin, group_scrollbar_margin, u32)
            PU_CLASS_POD_GETSET(GroupScrollbarSize, group_scrollbar_size, u32)
            PU_CLASS_POD_GETSET(GroupScrollbarColor, group_scrollbar_clr, Color)

            PU_CLASS_POD_GETSET(ColorVariateSpeedSteps, color_variate_speed_steps, u32)

            PU_CLASS_POD_GETSET(ButtonRadius, button_radius, u32)
            PU_CLASS_POD_GETSET(ButtonTextMarginLeft, button_text_margin_left, s32)
            PU_CLASS_POD_GETSET(ButtonTextMarginRight, button_text_margin_right, s32)

            virtual u32 GetButtonBorderThickness(const u32 _button_flavor) {
                return DefaultButtonBorderThickness;
            }

            virtual Color GetButtonBorderColor(const u32 _button_flavor) {
                return DefaultButtonBorderColor;
            }
            
            virtual Color GetButtonBackgroundColor(const u32 _button_flavor) {
                return DefaultButtonBackgroundColor;
            }

            virtual Color GetButtonBackgroundHeldColor(const u32 _button_flavor) {
                return DefaultButtonBackgroundHeldColor;
            }

            virtual Color GetTextColor(const u32 _text_flavor) {
                return DefaultTextColor;
            }

            PU_CLASS_POD_GETSET(ProgressBarProgressColor, pbar_progress_clr, Color)
            PU_CLASS_POD_GETSET(ProgressBarBackgroundColor, pbar_bg_clr, Color)

            PU_CLASS_POD_GETSET(SeparatorColor, separator_clr, Color)

            /**
             * @brief Function called every render cycle.
             * @note This function is called every render cycle, and can be used to update style parameters/values.
             */
            virtual void Update() {}

            /**
             * @brief Function called whenever an element is focused.
             */
            virtual void OnElementFocusChanged(elm::Element::Ref elem_lost_focus, elm::Element::Ref elem_gained_focus) {}

            /**
             * @brief Function called whenever an element fails to focus
             * @note This happens when the user tries to move the focus in some direction, but there is no element to move the focus to in that direction.
             */
            virtual void OnElementFocusFailed(elm::Element::Ref elem_failed_focus) {}

            /**
             * @brief Function called before the focused element is rendered.
             */
            virtual void OnBeforeFocusedElementRendered(render::Renderer::Ref &drawer, elm::Element::Ref elem_focused, const s32 elem_x, const s32 elem_y, const s32 elem_width, const s32 elem_height) {}
            
            /**
             * @brief Function called after the focused element is rendered.
             */
            virtual void OnAfterFocusedElementRendered(render::Renderer::Ref &drawer, elm::Element::Ref elem_focused, const s32 elem_x, const s32 elem_y, const s32 elem_width, const s32 elem_height) {}

            /**
             * @brief Function called whenever an element is clicked.
             * @note This happens when the user clicks on an element.
             */
            virtual void OnButtonClickDown(elm::Element::Ref elem_clicked) {}

            /**
             * @brief Function called whenever an element is released.
             * @note This happens when the user releases a click on an element.
             */
            virtual void OnButtonClickUp(elm::Element::Ref elem_clicked) {}
    };

    /**
     * @brief Sets the style for the UI.
     * @param style The style to set.
     * @note This function is used to set the style for the UI. Some properties are set when elements are created, so changing the style after creating elements may not affect them fully.
     */
    void SetStyle(Style::Ref style);

    /**
     * @brief Gets the current style for the UI.
     * @return The current style.
     * @note Note that the default Style is automatically created and set when an Application instance is created (prior to load), so custom styles should be set after the application is created (in the loading code, for instance) but before Elements are created and loaded.
     */
    Style::Ref GetStyle();

}
