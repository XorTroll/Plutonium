#include <pu/ui/elm/elm_Element.hpp>
#include <pu/ui/ui_Style.hpp>

namespace pu::ui::elm {

    void Element::SwitchFocus(Element::Ref &elem, RenderContext &ctx) {
        const auto now = std::chrono::steady_clock::now();
        const auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - ctx.last_focus_switch_time).count();
        if(time_diff < GetStyle()->GetFocusSwitchMinimumInterval()) {
            return;
        }
        ctx.last_focus_switch_time = now;

        if(elem != nullptr) {
            elem->focused = true;
            this->focused = false;
            ctx.focus_handled = true;
            ctx.elem_focused = elem;

            GetStyle()->OnElementFocusChanged(this->shared_from_this(), elem);
        }
        else {
            GetStyle()->OnElementFocusFailed(this->shared_from_this());
        }
    }

    Element::Element() : focused(false), focus_requested(false), up_elem(nullptr), down_elem(nullptr), left_elem(nullptr), right_elem(nullptr) {}

    bool Element::PerformInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos, RenderContext &ctx) {
        if(this->SupportsFocus() && !ctx.focus_handled && this->focused) {
            // Stop handling focus after we handle focus on the focused element

            if(!ctx.focus_handled && ((keys_down & this->GetFocusDownChangeKeysDown()) || (keys_held & this->GetFocusDownChangeKeysHeld()))) {
                this->SwitchFocus(this->down_elem, ctx);
            }

            if(!ctx.focus_handled && ((keys_down & this->GetFocusUpChangeKeysDown()) || (keys_held & this->GetFocusUpChangeKeysHeld()))) {
                this->SwitchFocus(this->up_elem, ctx);
            }

            if(!ctx.focus_handled && ((keys_down & this->GetFocusLeftChangeKeysDown()) || (keys_held & this->GetFocusLeftChangeKeysHeld()))) {
                this->SwitchFocus(this->left_elem, ctx);
            }

            if(!ctx.focus_handled && ((keys_down & this->GetFocusRightChangeKeysDown()) || (keys_held & this->GetFocusRightChangeKeysHeld()))) {
                this->SwitchFocus(this->right_elem, ctx);
            }
        }

        return this->OnInput(keys_down, keys_up, keys_held, touch_pos);
    }

}
