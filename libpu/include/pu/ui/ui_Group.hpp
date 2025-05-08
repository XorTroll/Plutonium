/**
 * Plutonium library
 * @file ui_Group.hpp
 * @brief Contains pu::ui::Group class
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_TouchScroller.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

    /**
     * @brief Enum containing the auto-rendering strategy for a Group.
     * @note This enum is used to determine how the elements in a Group with X/Y positions set to PositionAuto are rendered.
     */
    enum class AutoRenderStrategy {
        /**
         * @brief Elements are rendered horizontally, and when the width is exceeded, the next elements are rendered below, and so on.
         */
        Horizontal,
        /**
         * @brief Elements are rendered vertically, and when the height is exceeded, the next elements are rendered to the right, and so on.
         */
        Vertical
    };

    /**
     * @brief A group of elements that can be rendered together.
     * @note Together with Element, this is a base class for all UI rendering in Plutonium.
     */
    class Group : public Renderizable {
        public:
            PU_SMART_CTOR(Group)

        private:
            s32 x;
            s32 y;
            s32 width;
            s32 height;
            s32 margin_left;
            s32 margin_top;
            s32 margin_right;
            s32 margin_bottom;
            s32 inter_margin;
            s32 scrollbar_margin;
            s32 scrollbar_size;
            Color scrollbar_clr;
            Color bg_clr;
            AutoRenderStrategy auto_render_strategy;
            std::vector<elm::Element::Ref> elems;
            std::vector<Group::Ref> subgroups;
            s32 render_cur_x_rel;
            s32 render_cur_y_rel;
            s32 render_max_width;
            s32 render_max_height;
            TouchScroller touch_scroller;
            bool needs_check_touch_scroll;
            bool top_border_separator;
            bool bottom_border_separator;
            bool left_border_separator;
            bool right_border_separator;
            Color border_separator_clr;

            void CheckTouchScroll();

            inline s32 GetEffectiveX(const s32 render_x) {
                return render_x + this->margin_left;
            }

            inline s32 GetEffectiveY(const s32 render_y) {
                return render_y + this->margin_top;
            }

            inline s32 GetEffectiveWidth() {
                return this->width - this->margin_left - this->margin_right;
            }

            inline s32 GetEffectiveHeight() {
                return this->height - this->margin_top - this->margin_bottom;
            }

            void ComputePosition(Renderizable::Ref elem, s32 &out_x, s32 &out_y);
            s32 ComputeWidth(Renderizable::Ref elem);
            s32 ComputeHeight(Renderizable::Ref elem);

        public:
            /**
             * @brief Creates a new instance of a Group.
             * @param x X position of the Group, or PositionAuto to locate it automatically in the parent group.
             * @param y Y position of the Group, or PositionAuto to locate it automatically in the parent group.
             * @param width Width of the Group, or DimensionMatchParent to extend it to the parent group size.
             * @param height Height of the Group, or DimensionMatchParent to extend it to the parent group size.
             */
            Group(const s32 x, const s32 y, const s32 width, const s32 height) : x(x), y(y), width(width), height(height), margin_left(0), margin_top(0), margin_right(0), margin_bottom(0), inter_margin(0), scrollbar_margin(GetStyle()->GetGroupScrollbarMargin()), scrollbar_size(GetStyle()->GetGroupScrollbarSize()), scrollbar_clr(GetStyle()->GetGroupScrollbarColor()), bg_clr(GetStyle()->GetGroupBackgroundColor()), auto_render_strategy(AutoRenderStrategy::Horizontal), elems(), render_cur_x_rel(0), render_cur_y_rel(0), render_max_width(0), render_max_height(0), touch_scroller(0, 0), needs_check_touch_scroll(true), top_border_separator(false), bottom_border_separator(false), left_border_separator(false), right_border_separator(false), border_separator_clr(GetStyle()->GetGroupBorderSeparatorColor()) {}

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Button.
             * @param x New X position to set.
             */
            inline void SetX(const s32 x) {
                this->x = x;
                this->touch_scroller.SetMaximumScrollX(x + this->width);
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
                this->touch_scroller.SetMaximumScrollY(y + this->height);
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
                this->touch_scroller.SetMaximumScrollX(this->x + width);
                this->needs_check_touch_scroll = true;
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
                this->touch_scroller.SetMaximumScrollY(this->y + height);
                this->needs_check_touch_scroll = true;
            }

            PU_CLASS_POD_GETSET(BackgroundColor, bg_clr, Color)

            PU_CLASS_POD_GETSET(TopBorderSeparator, top_border_separator, bool)
            PU_CLASS_POD_GETSET(BottomBorderSeparator, bottom_border_separator, bool)
            PU_CLASS_POD_GETSET(LeftBorderSeparator, left_border_separator, bool)
            PU_CLASS_POD_GETSET(RightBorderSeparator, right_border_separator, bool)
            PU_CLASS_POD_GETSET(BorderSeparatorColor, border_separator_clr, Color)
            PU_CLASS_POD_GETSET(ScrollbarMargin, scrollbar_margin, s32)
            PU_CLASS_POD_GETSET(ScrollbarSize, scrollbar_size, s32)

            inline void RemoveScrollbar() {
                this->scrollbar_size = -1;
            }

            /**
             * @brief Adds an Element to the Group.
             * @param elem Element to add.
             */
            inline void AddElement(elm::Element::Ref elem) {
                this->elems.push_back(elem);
                this->needs_check_touch_scroll = true;
            }

            inline void ClearElements() {
                this->elems.clear();
                this->needs_check_touch_scroll = true;
            }

            /**
             * @brief Adds a child Group to the Group.
             * @param group Group to add.
             */
            inline void AddSubgroup(Group::Ref group) {
                this->subgroups.push_back(group);
                this->needs_check_touch_scroll = true;
            }

            inline void ClearSubgroups() {
                this->subgroups.clear();
                this->needs_check_touch_scroll = true;
            }

            elm::Element::Ref FindChildFocusable();

            PU_CLASS_POD_GETSET(MarginLeft, margin_left, s32)
            PU_CLASS_POD_GETSET(MarginTop, margin_top, s32)
            PU_CLASS_POD_GETSET(MarginRight, margin_right, s32)
            PU_CLASS_POD_GETSET(MarginBottom, margin_bottom, s32)
            PU_CLASS_POD_GETSET(InterMargin, inter_margin, s32)
            PU_CLASS_POD_GETSET(AutoRenderStrategy, auto_render_strategy, AutoRenderStrategy)

            /**
             * @brief Call that performs the rendering of the Group and its elements/subgroups.
             * @param drawer The Renderer instance to use for rendering.
             * @note This method is called internally. It should not be called manually under general circumstances.
             */
            void HandleRender(render::Renderer::Ref &drawer);

            /**
             * @brief Call that performs the input handling of the Group and its elements/subgroups.
             * @param keys_down Keys that are currently being pressed.
             * @param keys_up Keys that are currently being released.
             * @param keys_held Keys that are currently held.
             * @param touch_pos Position of the touch on the screen.
             * @param ctx Internal render context.
             * @note This method is called internally. It should not be called manually under general circumstances.
             */
            void HandleInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos, elm::Element::RenderContext &ctx);
    };

}
