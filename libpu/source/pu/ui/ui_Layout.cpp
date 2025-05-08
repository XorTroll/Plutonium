#include <pu/ui/ui_Layout.hpp>

namespace pu::ui {

    Layout::Layout() : has_image(false), over_bg_color(GetStyle()->GetLayoutBackgroundColor()), over_bg_tex(), over_bg_tex_x_offset(0), on_ipt(), render_cbs(), ctx() {
        this->ctx.last_focus_switch_time = std::chrono::steady_clock::now();
        this->root = Group::New(0, 0, render::ScreenWidth, render::ScreenHeight);
        this->root->SetBackgroundColor({ 0, 0, 0, 0 }); // Transparent background for the root group
    }

    Layout::~Layout() {
        this->ResetBackgroundImage();
    }

    void Layout::SetBackgroundImage(sdl2::TextureHandle::Ref bg_tex) {
        this->ResetBackgroundImage();
        this->over_bg_tex = bg_tex;
    }

    void Layout::SetBackgroundColor(const Color clr) {
        this->ResetBackgroundImage();
        this->over_bg_color = clr;
    }

    void Layout::ResetBackgroundImage() {
        this->over_bg_tex = {};
    }

    void Layout::OnStart() {
    }

    void Layout::OnStop() {
    }

    void Layout::OnRender(render::Renderer::Ref &drawer) {
        for(auto &render_cb: this->render_cbs) {
            if(render_cb) {
                render_cb();
            }
        }

        if(this->over_bg_tex != nullptr) {
            if(over_bg_tex_x_offset == 0) {
                drawer->RenderTexture(this->over_bg_tex->Get(), 0, 0);
            }
            else if(over_bg_tex_x_offset > 0) {
                drawer->RenderTexture(this->over_bg_tex->Get(), over_bg_tex_x_offset, 0);
                drawer->RenderTexture(this->over_bg_tex->Get(), over_bg_tex_x_offset - render::ScreenWidth, 0);
            }
            else if(over_bg_tex_x_offset < 0) {
                drawer->RenderTexture(this->over_bg_tex->Get(), over_bg_tex_x_offset, 0);
                drawer->RenderTexture(this->over_bg_tex->Get(), over_bg_tex_x_offset + render::ScreenWidth, 0);
            }
        }

        this->root->PrepareRender(0, 0, render::ScreenWidth, render::ScreenHeight);
        this->root->HandleRender(drawer);
    }

    void Layout::OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) {
        if(this->on_ipt != nullptr) {
            this->on_ipt(keys_down, keys_up, keys_held, touch_pos);
        }

        const auto prev_any_group_scrolling = this->ctx.any_group_scrolling;
        this->ctx.focus_handled = false;
        this->ctx.elem_focused = nullptr;
        this->ctx.elem_requesting_focus = nullptr;
        this->ctx.any_group_scrolling = false;

        this->root->HandleInput(keys_down, keys_up, keys_held, touch_pos, this->ctx);

        if(this->ctx.elem_requesting_focus != nullptr) {
            if(this->ctx.elem_focused != nullptr) {
                this->ctx.elem_focused->SetFocused(false);
            }
            this->ctx.elem_requesting_focus->SetFocused(true);

            this->ctx.elem_focused = this->ctx.elem_requesting_focus;
            this->ctx.elem_requesting_focus = nullptr;
        }

        // Changed from not-scrolling to scrolling in some group, need to unfocus the focused element if any
        if(this->ctx.any_group_scrolling && !prev_any_group_scrolling) {
            if(this->ctx.elem_focused != nullptr) {
                this->ctx.elem_focused->SetFocused(false);
            }

            this->ctx.elem_focused = nullptr;
        }

        if(!this->ctx.any_group_scrolling && (this->ctx.elem_focused == nullptr) && (keys_down != 0)) {
            auto focused_elem = this->root->FindChildFocusable();
            if(focused_elem != nullptr) {
                GetStyle()->OnElementFocusChanged(nullptr, focused_elem);
            }
        }
    }

}
