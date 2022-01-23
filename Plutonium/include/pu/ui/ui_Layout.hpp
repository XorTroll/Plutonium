
/*

    Plutonium library

    @file ui_Layout.hpp
    @brief Contains pu::Layout class, the object used to render within applications
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Container.hpp>
#include <functional>

namespace pu::ui {

    class Layout : public Container {
        public:
            using OnInputCallback = std::function<void(const u64, const u64, const u64, const TouchPoint)>;
            using RenderCallback = std::function<void()>;

            static constexpr Color DefaultBackgroundColor = { 0xE1, 0xE1, 0xE1, 0xFF };

        private:
            bool has_image;
            Color over_bg_color;
            TouchPoint sim_touch_pos;
            sdl2::Texture over_bg_tex;
            OnInputCallback on_ipt;
            std::vector<RenderCallback> render_cbs;

        public:
            Layout() : Container(0, 0, render::ScreenWidth, render::ScreenHeight), has_image(false), over_bg_color(DefaultBackgroundColor), sim_touch_pos(), over_bg_tex(), on_ipt(), render_cbs() {}
            PU_SMART_CTOR(Layout)
            ~Layout();

            inline bool HasChildren() {
                return !this->elems.empty();
            }

            inline void SetOnInput(OnInputCallback on_ipt_cb) {
                this->on_ipt = on_ipt_cb;
            }

            inline OnInputCallback GetOnInput() {
                return this->on_ipt;
            }

            inline void AddRenderCallback(RenderCallback render_cb) {
                this->render_cbs.push_back(render_cb);
            }

            inline std::vector<RenderCallback> &GetRenderCallbacks() {
                return this->render_cbs;
            }

            inline bool HasBackgroundImage() {
                return this->has_image;
            }
            
            inline sdl2::Texture GetBackgroundImageTexture() {
                return this->over_bg_tex;
            }

            inline Color GetBackgroundColor() {
                return this->over_bg_color;
            }

            void SetBackgroundImage(const std::string &path);
            void SetBackgroundColor(const Color clr);
            
            inline void SimulateTouchPosition(const TouchPoint sim_touch_pos) {
                this->sim_touch_pos = sim_touch_pos;
            }
            
            TouchPoint ConsumeSimulatedTouchPosition();
    };

}