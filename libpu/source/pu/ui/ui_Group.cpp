#include <pu/ui/ui_Group.hpp>

namespace pu::ui {

    void Group::CheckTouchScroll() {
        this->touch_scroller.SetXScrollEnabled(false);
        this->touch_scroller.SetYScrollEnabled(false);

        this->render_cur_x_rel = 0;
        this->render_cur_y_rel = 0;
        this->render_max_width = 0;
        this->render_max_height = 0;
        for(auto &elem: this->elems) {
            if(elem->GetVisible()) {
                s32 elem_x;
                s32 elem_y;
                this->ComputePosition(elem, elem_x, elem_y);
                const auto elem_width = this->ComputeWidth(elem);
                const auto elem_height = this->ComputeHeight(elem);

                if((elem_x + elem_width) > (this->GetRenderX() + this->margin_left + this->GetEffectiveWidth())) {
                    this->touch_scroller.SetXScrollEnabled(true);
                    const auto new_max_x = std::max(this->touch_scroller.GetMaximumScrollX(), (elem_x + elem_width + this->margin_right) - this->GetRenderWidth());
                    this->touch_scroller.SetMaximumScrollX(new_max_x);
                    this->render_max_width = std::max(this->render_max_width, elem_x + elem_width - this->GetRenderX() - this->margin_left);
                }
                if((elem_y + elem_height) > (this->GetRenderY() + this->margin_top + this->GetEffectiveHeight())) {
                    this->touch_scroller.SetYScrollEnabled(true);
                    const auto new_max_y = std::max(this->touch_scroller.GetMaximumScrollY(), (elem_y + elem_height + this->margin_bottom) - this->GetRenderHeight());
                    this->touch_scroller.SetMaximumScrollY(new_max_y);
                    this->render_max_height = std::max(this->render_max_height, elem_y + elem_height - this->GetRenderY() - this->margin_top);
                }
            }
        }

        if(this->touch_scroller.GetXScrollEnabled() && this->touch_scroller.GetYScrollEnabled()) {
            return;
        }

        for(auto &subgroup: this->subgroups) {
            if(subgroup->GetVisible()) {
                s32 elem_x;
                s32 elem_y;
                this->ComputePosition(subgroup, elem_x, elem_y);
                const auto elem_width = this->ComputeWidth(subgroup);
                const auto elem_height = this->ComputeHeight(subgroup);

                if((elem_x + elem_width) > (this->GetRenderX() + this->margin_left + this->GetEffectiveWidth())) {
                    this->touch_scroller.SetXScrollEnabled(true);
                }
                if((elem_y + elem_height) > (this->GetRenderY() + this->margin_top + this->GetEffectiveHeight())) {
                    this->touch_scroller.SetYScrollEnabled(true);
                }
            }
        }
    }

    void Group::ComputePosition(Renderizable::Ref elem, s32 &out_x, s32 &out_y) {
        const auto base_x = elem->GetX();
        const auto base_y = elem->GetY();
        const auto render_x = this->GetRenderX() + this->touch_scroller.GetScrollX();
        const auto render_y = this->GetRenderY() + this->touch_scroller.GetScrollY();

        if(base_x == PositionAuto) {
            auto auto_x = this->GetEffectiveX(render_x) + this->render_cur_x_rel;
            if(this->auto_render_strategy == AutoRenderStrategy::Horizontal) {
                this->render_cur_x_rel += elem->GetWidth() + this->inter_margin;
            }
            out_x = auto_x;
        }
        else if(elem->GetHorizontalAlign() == HorizontalAlign::Center) {
            out_x = this->GetEffectiveX(render_x) + (this->GetEffectiveWidth() - elem->GetWidth()) / 2;
        }
        else if(elem->GetHorizontalAlign() == HorizontalAlign::Right) {
            out_x = this->GetEffectiveX(render_x) + (this->GetEffectiveWidth() - elem->GetWidth());
        }
        else {
            out_x = this->GetEffectiveX(render_x) + base_x;
        }

        if(base_y == PositionAuto) {
            auto auto_y = this->GetEffectiveY(render_y) + this->render_cur_y_rel;
            if(this->auto_render_strategy == AutoRenderStrategy::Vertical) {
                this->render_cur_y_rel += elem->GetHeight() + this->inter_margin;
            }
            out_y = auto_y;
        }
        else if(elem->GetVerticalAlign() == VerticalAlign::Center) {
            out_y = this->GetEffectiveY(render_y) + (this->GetEffectiveHeight() - elem->GetHeight()) / 2;
        }
        else if(elem->GetVerticalAlign() == VerticalAlign::Down) {
            out_y = this->GetEffectiveY(render_y) + (this->GetEffectiveHeight() - elem->GetHeight());
        }
        else {
            out_y = this->GetEffectiveY(render_y) + base_y;
        }
    }

    /*
    void Group::ComputePosition(Renderizable::Ref elem, s32 &out_x, s32 &out_y) {
        const auto base_x = elem->GetX();
        const auto base_y = elem->GetY();
        const auto render_x = this->GetRenderX();
        const auto render_y = this->GetRenderY();

        if(base_x == PositionAuto) {
            auto auto_x = this->GetEffectiveX(render_x) + this->render_cur_x_rel;
            if(this->auto_render_strategy == AutoRenderStrategy::Horizontal) {
                if((auto_x + elem->GetWidth()) > this->GetEffectiveWidth()) {
                    this->render_cur_x_rel = 0;
                    auto_x = this->GetEffectiveX(render_x) + this->render_cur_x_rel;
                    this->render_cur_y_rel += this->render_max_height + this->inter_margin;
                }
                this->render_cur_x_rel += elem->GetWidth() + this->inter_margin;
            }
            out_x = auto_x;
        }
        else if(elem->GetHorizontalAlign() == HorizontalAlign::Center) {
            out_x = render_x + (this->GetEffectiveWidth() - elem->GetWidth()) / 2;
        }
        else if(elem->GetHorizontalAlign() == HorizontalAlign::Right) {
            out_x = render_x + (this->GetEffectiveWidth() - elem->GetWidth());
        }
        else {
            out_x = render_x + base_x + this->margin_left;
        }

        if(base_y == PositionAuto) {
            auto auto_y = this->GetEffectiveY(render_y) + this->render_cur_y_rel;
            if(this->auto_render_strategy == AutoRenderStrategy::Vertical) {
                if((auto_y + elem->GetHeight()) > this->GetEffectiveHeight()) {
                    this->render_cur_y_rel = 0;
                    auto_y = this->GetEffectiveY(render_y) + this->render_cur_y_rel;
                    this->render_cur_x_rel += this->render_max_width + this->inter_margin;

                    if(base_x == PositionAuto) {
                        out_x = this->GetEffectiveX(render_x) + this->render_cur_x_rel;
                    }
                }
                this->render_cur_y_rel += elem->GetHeight() + this->inter_margin;
            }
            out_y = auto_y;
        }
        else if(elem->GetHorizontalAlign() == HorizontalAlign::Center) {
            out_y = render_y + (this->GetEffectiveHeight() - elem->GetHeight()) / 2;
        }
        else if(elem->GetHorizontalAlign() == HorizontalAlign::Right) {
            out_y = render_y + (this->GetEffectiveHeight() - elem->GetHeight());
        }
        else {
            out_y = render_y + base_y + this->margin_top;
        }
    }
    */

    s32 Group::ComputeWidth(Renderizable::Ref elem) {
        const auto base_width = elem->GetWidth();
        if(base_width == DimensionMatchParent) {
            return this->GetEffectiveWidth();
        }

        return base_width;
    }

    s32 Group::ComputeHeight(Renderizable::Ref elem) {
        const auto base_height = elem->GetHeight();
        if(base_height == DimensionMatchParent) {
            return this->GetEffectiveHeight();
        }

        return base_height;
    }

    elm::Element::Ref Group::FindChildFocusable() {
        for(auto &elem: this->elems) {
            if(elem->GetVisible() && elem->SupportsFocus()) {
                s32 elem_x;
                s32 elem_y;
                this->ComputePosition(elem, elem_x, elem_y);
                const auto elem_width = this->ComputeWidth(elem);
                const auto elem_height = this->ComputeHeight(elem);
                if(SubregionInsideRegion(elem_x, elem_y, elem_width, elem_height, PU_UI_RENDER_XYWH)) {
                    elem->SetFocused(true);
                    return elem;
                }
            }
        }

        for(auto &subgroup: this->subgroups) {
            if(subgroup->GetVisible()) {
                auto elem = subgroup->FindChildFocusable();
                if(elem != nullptr) {
                    return elem;
                }
            }
        }

        return nullptr;
    }

    static void DebugLog(const std::string &msg) {
        FILE *fp = fopen("sdmc:/plutonium.log", "a");
        if(fp != nullptr) {
            fprintf(fp, "%s\n", msg.c_str());
            fclose(fp);
        }
    }

    void Group::HandleRender(render::Renderer::Ref &drawer) {
        if(this->needs_check_touch_scroll) {
            this->CheckTouchScroll();
            this->needs_check_touch_scroll = false;
        }

        drawer->PushRenderRegion(PU_UI_RENDER_XYWH);

        drawer->RenderRectangleFill(this->bg_clr, PU_UI_RENDER_XYWH);

        s32 focused_elem_x = 0;
        s32 focused_elem_y = 0;
        s32 focused_elem_width = 0;
        s32 focused_elem_height = 0;
        elm::Element::Ref focused_elem = nullptr;

        this->render_cur_x_rel = 0;
        this->render_cur_y_rel = 0;
        for(auto &elem: this->elems) {
            if(elem->GetVisible()) {
                s32 elem_x;
                s32 elem_y;
                this->ComputePosition(elem, elem_x, elem_y);
                const auto elem_width = this->ComputeWidth(elem);
                const auto elem_height = this->ComputeHeight(elem);
                elem->PrepareRender(elem_x, elem_y, elem_width, elem_height);

                if(elem->IsFocused()) {
                    focused_elem = elem;
                    focused_elem_x = elem_x;
                    focused_elem_y = elem_y;
                    focused_elem_width = elem_width;
                    focused_elem_height = elem_height;
                    GetStyle()->OnBeforeFocusedElementRendered(drawer, elem, elem_x, elem_y, elem_width, elem_height);
                }
                elem->OnRender(drawer);
            }
        }

        if(focused_elem != nullptr) {
            GetStyle()->OnAfterFocusedElementRendered(drawer, focused_elem, focused_elem_x, focused_elem_y, focused_elem_width, focused_elem_height);

            if(!this->touch_scroller.IsScrolling()) {
                if((focused_elem_x + focused_elem_width) > (this->GetRenderX() + this->GetRenderWidth())) {
                    DebugLog("Scrolling right -- current scroll X: " + std::to_string(this->touch_scroller.GetScrollX()) + " -- new scroll X: " + std::to_string(this->GetRenderWidth() - (focused_elem_x + focused_elem_width + this->margin_right)));
                    this->touch_scroller.SetScrollX(this->GetRenderWidth() - (focused_elem_x + focused_elem_width + this->margin_right));
                    focused_elem->SetFocused(false);
                }
            }
        }

        this->render_cur_x_rel = 0;
        this->render_cur_y_rel = 0;
        for(auto &subgroup: this->subgroups) {
            if(subgroup->GetVisible()) {
                s32 elem_x;
                s32 elem_y;
                this->ComputePosition(subgroup, elem_x, elem_y);
                const auto elem_width = this->ComputeWidth(subgroup);
                const auto elem_height = this->ComputeHeight(subgroup);

                subgroup->PrepareRender(elem_x, elem_y, elem_width, elem_height);
                subgroup->HandleRender(drawer);
            }
        }

        if(this->scrollbar_size > 0) {
            if(this->touch_scroller.GetYScrollEnabled()) {
                const auto scrollbar_v_base_x = this->GetRenderX() + this->GetRenderWidth() - this->scrollbar_size - this->scrollbar_margin;
                const auto scrollbar_v_base_y = this->GetRenderY() + this->scrollbar_margin;
                const auto scrollbar_v_x = scrollbar_v_base_x;
                const auto scrollbar_v_y = scrollbar_v_base_y - (s32)((double)(this->touch_scroller.GetScrollY() * this->GetEffectiveHeight()) / (double)this->render_max_height);

                const auto scrollbar_v_height = (s32)((double)(this->GetEffectiveHeight() * this->GetEffectiveHeight()) / (double)this->render_max_height);
                drawer->RenderRectangleFill(this->scrollbar_clr, scrollbar_v_x, scrollbar_v_y, this->scrollbar_size, scrollbar_v_height - (this->scrollbar_margin * 2));
            }

            if(this->touch_scroller.GetXScrollEnabled()) {
                const auto scrollbar_h_base_x = this->GetRenderX() + this->scrollbar_margin;
                const auto scrollbar_h_base_y = this->GetRenderY() + this->GetRenderHeight() - this->scrollbar_size - this->scrollbar_margin;
                const auto scrollbar_h_x = scrollbar_h_base_x - (s32)((double)(this->touch_scroller.GetScrollX() * this->GetEffectiveWidth()) / (double)this->render_max_width);
                const auto scrollbar_h_y = scrollbar_h_base_y;

                const auto scrollbar_h_width = (s32)((double)(this->GetEffectiveWidth() * this->GetEffectiveWidth()) / (double)this->render_max_width);
                drawer->RenderRectangleFill(this->scrollbar_clr, scrollbar_h_x, scrollbar_h_y, scrollbar_h_width - (this->scrollbar_margin * 2), this->scrollbar_size);
            }
        }

        // TODO: if scroll enabled, draw scrollbar!

        if(this->top_border_separator) {
            drawer->RenderRectangleFill(this->border_separator_clr, this->GetRenderX(), this->GetRenderY(), this->GetRenderWidth(), 1);
        }
        if(this->bottom_border_separator) {
            drawer->RenderRectangleFill(this->border_separator_clr, this->GetRenderX(), this->GetRenderY() + this->GetRenderHeight() - 1, this->GetRenderWidth(), 1);
        }
        if(this->left_border_separator) {
            drawer->RenderRectangleFill(this->border_separator_clr, this->GetRenderX(), this->GetRenderY(), 1, this->GetRenderHeight());
        }
        if(this->right_border_separator) {
            drawer->RenderRectangleFill(this->border_separator_clr, this->GetRenderX() + this->GetRenderWidth() - 1, this->GetRenderY(), 1, this->GetRenderHeight());
        }

        drawer->PopRenderRegion();
    }

    void Group::HandleInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos, elm::Element::RenderContext &ctx) {
        this->touch_scroller.Update(touch_pos, PU_UI_RENDER_XYWH);

        auto child_touch_pos = touch_pos;
        // If scrolling, we are the only ones dealing with touch input
        if(this->touch_scroller.IsScrolling()) {
            // child_touch_pos = {};
            child_touch_pos.is_scrolling = true;
            // If we have some element focused and are scrolling, we need to unfocus it
            ctx.any_group_scrolling = true;
        }

        bool input_consumed = false;
        for(auto &elem: this->elems) {
            if(elem->GetVisible()) {
                if(!input_consumed) {
                    input_consumed |= elem->PerformInput(keys_down, keys_up, keys_held, child_touch_pos, ctx);
                }

                if(elem->IsFocused()) {
                    // Keep track of the focused element, avoiding iterative loops if we had to find it and unfocus it
                    ctx.elem_focused = elem;
                }
                // TODO: is the second check even needed?
                else if(elem->ConsumeFocusRequested() && elem->SupportsFocus()) {
                    ctx.elem_requesting_focus = elem;
                }
            }
        }

        for(auto &subgroup: this->subgroups) {
            if(subgroup->GetVisible()) {
                subgroup->HandleInput(keys_down, keys_up, keys_held, child_touch_pos, ctx);
            }
        }
    }

}
