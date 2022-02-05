
/*

    Plutonium library

    @file Menu.hpp
    @brief A Menu is a very useful Element for option browsing or selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <chrono>
#include <functional>

namespace pu::ui::elm {

    class MenuItem {
        public:
            using OnKeyCallback = std::function<void()>;
            static constexpr Color DefaultColor = { 10, 10, 10, 0xFF };

        private:
            std::string name;
            Color items_clr;
            std::string icon_path;
            std::vector<OnKeyCallback> on_key_cbs;
            std::vector<u64> on_key_cb_keys;

        public:
            MenuItem(const std::string &name) : name(name), items_clr(DefaultColor) {}
            PU_SMART_CTOR(MenuItem)

            inline std::string GetName() {
                return this->name;
            }
            
            inline void SetName(const std::string &name) {
                this->name = name;
            }

            inline Color GetColor() {
                return this->items_clr;
            }

            inline void SetColor(const Color items_clr) {
                this->items_clr = items_clr;
            }

            void AddOnKey(OnKeyCallback on_key_cb, const u64 key = HidNpadButton_A);
            
            inline u32 GetOnKeyCallbackCount() {
                return this->on_key_cbs.size();
            }

            inline OnKeyCallback GetOnKeyCallback(const u32 idx) {
                if(idx < this->on_key_cbs.size()) {
                    return this->on_key_cbs.at(idx);
                }
                else {
                    return {};
                }
            }

            inline u64 GetOnKeyCallbackKey(const u32 idx) {
                if(idx < this->on_key_cb_keys.size()) {
                    return this->on_key_cb_keys.at(idx);
                }
                else {
                    return {};
                }
            }

            inline std::string GetIconPath() {
                return this->icon_path;
            }

            void SetIcon(const std::string &icon_path);

            inline bool HasIcon() {
                return !this->icon_path.empty();
            }
    };

    class Menu : public Element {
        public:
            static constexpr Color DefaultScrollbarColor = { 110, 110, 110, 0xFF };

            static constexpr u8 ItemAlphaIncrement = 48;

            static constexpr float IconItemSizesFactor = 0.8f;

            static constexpr u32 IconMargin = 25;
            static constexpr u32 TextMargin = 25;

            static constexpr u8 LightScrollbarColorFactor = 30;

            static constexpr u32 ScrollbarWidth = 20;

            static constexpr u32 ShadowHeight = 5;
            static constexpr u8 ShadowBaseAlpha = 160;

            using OnSelectionChangedCallback = std::function<void()>;

        private:
            i32 x;
            i32 y;
            i32 w;
            i32 items_h;
            u32 items_to_show;
            u32 selected_item_idx;
            i32 selected_item_alpha;
            i32 prev_selected_item_idx;
            i32 prev_selected_item_alpha;
            u32 advanced_item_count;
            Color scrollbar_clr;
            Color items_clr;
            Color items_focus_clr;
            bool cooldown_enabled;
            bool item_touched;
            u8 move_mode;
            std::chrono::time_point<std::chrono::steady_clock> move_start_time;
            OnSelectionChangedCallback on_selection_changed_cb;
            std::vector<MenuItem::Ref> items;
            std::string font_name;
            std::vector<sdl2::Texture> loaded_name_texs;
            std::vector<sdl2::Texture> loaded_icon_texs;

            void ReloadItemRenders();

            inline Color MakeItemsFocusColor(const u8 alpha) {
                return { this->items_focus_clr.r, this->items_focus_clr.g, this->items_focus_clr.b, alpha };
            }

            inline constexpr Color MakeLighterScrollbarColor() {
                i32 base_r = this->scrollbar_clr.r - LightScrollbarColorFactor;
                if(base_r < 0) {
                    base_r = 0;
                }
                i32 base_g = this->scrollbar_clr.g - LightScrollbarColorFactor;
                if(base_g < 0) {
                    base_g = 0;
                }
                i32 base_b = this->scrollbar_clr.b - LightScrollbarColorFactor;
                if(base_b < 0) {
                    base_b = 0;
                }

                return { static_cast<u8>(base_r), static_cast<u8>(base_g), static_cast<u8>(base_b), this->scrollbar_clr.a };
            }

            inline void HandleOnSelectionChanged() {
                if(this->on_selection_changed_cb) {
                    (this->on_selection_changed_cb)();
                }
            }

            inline void RunSelectedItemCallback(const u64 keys) {
                auto item = this->items.at(this->selected_item_idx);
                const auto cb_count = item->GetOnKeyCallbackCount();
                for(u32 i = 0; i < cb_count; i++) {
                    if(keys & item->GetOnKeyCallbackKey(i)) {
                        if(!this->cooldown_enabled) {
                            auto cb = item->GetOnKeyCallback(i);
                            if(cb) {
                                cb();
                            }
                        }
                    }
                }
                this->cooldown_enabled = false;
            }

            inline u32 GetItemCount() {
                auto item_count = this->items_to_show;
                if(item_count > this->items.size()) {
                    item_count = this->items.size();
                }
                if((item_count + this->advanced_item_count) > this->items.size()) {
                    item_count = this->items.size() - this->advanced_item_count;
                }
                return item_count;
            }

        public:
            Menu(const i32 x, const i32 y, const i32 width, const Color items_clr, const Color items_focus_clr, const i32 items_height, const u32 items_to_show);
            PU_SMART_CTOR(Menu)

            inline i32 GetX() override {
                return this->x;
            }

            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetY() override {
                return this->y;
            }

            inline void SetY(const i32 y) {
                this->y = y;
            }

            inline i32 GetWidth() override {
                return this->w;
            }

            inline void SetWidth(const i32 width) {
                this->w = width;
            }

            inline i32 GetHeight() override {
                return this->items_h * this->items_to_show;
            }

            inline i32 GetItemsHeight() {
                return this->items_h;
            }

            inline void SetItemsHeight(const i32 items_height) {
                this->items_h = items_height;
            }

            inline i32 GetNumberOfItemsToShow() {
                return this->items_to_show;
            }

            inline void SetNumberOfItemsToShow(const i32 items_to_show) {
                this->items_to_show = items_to_show;
            }

            inline Color GetItemsColor() {
                return this->items_clr;
            }

            inline void SetItemsColor(const Color items_clr) {
                this->items_clr = items_clr;
            }

            inline Color GetItemsFocusColor() {
                return this->items_focus_clr;
            }

            inline void SetItemsFocusColor(const Color items_focus_clr) {
                this->items_focus_clr = items_focus_clr;
            }

            inline Color GetScrollbarColor() {
                return this->scrollbar_clr;
            }

            inline void SetScrollbarColor(const Color scrollbar_clr) {
                this->scrollbar_clr = scrollbar_clr;
            }

            inline void SetOnSelectionChanged(OnSelectionChangedCallback on_selection_changed_cb) {
                this->on_selection_changed_cb = on_selection_changed_cb;
            }

            inline void AddItem(MenuItem::Ref &item) {
                this->items.push_back(item);
            }

            void ClearItems();

            inline void SetCooldownEnabled(const bool enabled) {
                this->cooldown_enabled = enabled;
            }

            inline MenuItem::Ref &GetSelectedItem() {
                return this->items.at(this->selected_item_idx);
            }

            inline std::vector<MenuItem::Ref> &GetItems() {
                return this->items;
            }

            inline i32 GetSelectedIndex() {
                return this->selected_item_idx;
            }

            void SetSelectedIndex(const u32 idx);

            void OnRender(render::Renderer::Ref &drawer, const i32 x, const i32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };
}