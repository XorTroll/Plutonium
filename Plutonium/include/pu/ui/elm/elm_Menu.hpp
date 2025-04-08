/**
 * Plutonium library
 * @file elm_Menu.hpp
 * @brief Contains classes for creating UI menus.
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <chrono>
#include <functional>

namespace pu::ui::elm {

    /**
     * @brief Represents a menu item.
     */
    class MenuItem {
        public:
            /**
             * @brief Represents a function called when the specific key is pressed over a the MenuItem.
             */
            using OnKeyCallback = std::function<void()>;

            // Self-explanatory constants

            static constexpr Color DefaultColor = { 10, 10, 10, 0xFF };

        private:
            std::string name;
            Color clr;
            sdl2::TextureHandle::Ref icon;
            std::vector<OnKeyCallback> on_key_cbs;
            std::vector<u64> on_key_cb_keys;

        public:
            /**
             * @brief Creates a new instance of a MenuItem.
             * @param name Name of the MenuItem.
             */
            MenuItem(const std::string &name) : name(name), clr(DefaultColor) {}
            PU_SMART_CTOR(MenuItem)

            /**
             * @brief Gets the name of the MenuItem.
             * @return Name of the MenuItem.
             */
            inline std::string GetName() {
                return this->name;
            }

            /**
             * @brief Sets the name of the MenuItem.
             * @param name New name of the MenuItem.
             */
            inline void SetName(const std::string &name) {
                this->name = name;
            }

            PU_CLASS_POD_GETSET(Color, clr, Color)

            /**
             * @brief Adds a new OnKeyCallback to the MenuItem.
             * @param on_key_cb Function to call when the key is pressed.
             * @param key Key to call the function on. Default is A.
             */
            void AddOnKey(OnKeyCallback on_key_cb, const u64 key = HidNpadButton_A);

            /**
             * @brief Gets the amount of OnKeyCallbacks in the MenuItem.
             * @return Amount of OnKeyCallbacks in the MenuItem.
             */
            inline u32 GetOnKeyCallbackCount() {
                return this->on_key_cbs.size();
            }

            /**
             * @brief Gets the OnKeyCallback at the specified index.
             * @param idx Index of the OnKeyCallback.
             * @return OnKeyCallback at the specified index.
             */
            inline OnKeyCallback GetOnKeyCallback(const u32 idx) {
                if(idx < this->on_key_cbs.size()) {
                    return this->on_key_cbs.at(idx);
                }
                else {
                    return {};
                }
            }

            /**
             * @brief Gets the key of the OnKeyCallback at the specified index.
             * @param idx Index of the OnKeyCallback.
             * @return Key of the OnKeyCallback at the specified index.
             */
            inline u64 GetOnKeyCallbackKey(const u32 idx) {
                if(idx < this->on_key_cb_keys.size()) {
                    return this->on_key_cb_keys.at(idx);
                }
                else {
                    return {};
                }
            }

            /**
             * @brief Gets the icon of the MenuItem.
             * @return Icon of the MenuItem.
             */
            inline sdl2::TextureHandle::Ref GetIconTexture() {
                return this->icon;
            }

            /**
             * @brief Sets the icon of the MenuItem.
             * @param icon Icon to set.
             */
            void SetIcon(sdl2::TextureHandle::Ref icon);

            /**
             * @brief Gets whether the MenuItem has an icon.
             * @return Whether the MenuItem has an icon.
             */
            inline bool HasIcon() {
                return this->icon != nullptr;
            }
    };

    /**
     * @brief Represents a menu.
     */
    class Menu : public Element {
        public:
            // Self-explanatory constants

            static constexpr Color DefaultScrollbarColor = { 110, 110, 110, 0xFF };

            static constexpr u8 DefaultItemAlphaIncrementSteps = 15;

            static constexpr float DefaultIconItemSizesFactor = 0.8f;

            static constexpr u32 DefaultIconMargin = 37;
            static constexpr u32 DefaultTextMargin = 37;

            static constexpr u8 DefaultLightScrollbarColorFactor = 30;

            static constexpr u32 DefaultScrollbarWidth = 30;

            static constexpr u32 DefaultShadowHeight = 7;
            static constexpr u8 DefaultShadowBaseAlpha = 160;

            static constexpr s64 DefaultMoveWaitTimeMs = 150;

            /**
             * @brief Represents a function called when the selection of the Menu changes.
             */
            using OnSelectionChangedCallback = std::function<void()>;

        private:
            enum class MoveStatus : u8 {
                None = 0,
                WaitingUp = 1,
                WaitingDown = 2
            };

            s32 x;
            s32 y;
            s32 w;
            s32 items_h;
            u32 items_to_show;
            u32 selected_item_idx;
            s32 selected_item_alpha;
            SigmoidIncrementer<s32> selected_item_alpha_incr;
            s32 prev_selected_item_idx;
            s32 prev_selected_item_alpha;
            SigmoidIncrementer<s32> prev_selected_item_alpha_incr;
            u32 advanced_item_count;
            Color scrollbar_clr;
            Color items_clr;
            Color items_focus_clr;
            bool cooldown_enabled;
            bool item_touched;
            MoveStatus move_status;
            std::chrono::time_point<std::chrono::steady_clock> move_start_time;
            OnSelectionChangedCallback on_selection_changed_cb;
            std::vector<MenuItem::Ref> items;
            std::string font_name;
            std::vector<sdl2::Texture> loaded_name_texs;
            u8 item_alpha_incr_steps;
            float icon_item_sizes_factor;
            u32 icon_margin;
            u32 text_margin;
            u8 light_scrollbar_color_factor;
            u32 scrollbar_width;
            u32 shadow_height;
            u8 shadow_base_alpha;
            s64 move_wait_time_ms;

            void ReloadItemRenders();
            void MoveUp();
            void MoveDown();

            inline Color MakeItemsFocusColor(const u8 alpha) {
                return this->items_focus_clr.WithAlpha(alpha);
            }

            inline constexpr Color MakeLighterScrollbarColor() {
                s32 base_r = this->scrollbar_clr.r - this->light_scrollbar_color_factor;
                if(base_r < 0) {
                    base_r = 0;
                }
                s32 base_g = this->scrollbar_clr.g - this->light_scrollbar_color_factor;
                if(base_g < 0) {
                    base_g = 0;
                }
                s32 base_b = this->scrollbar_clr.b - this->light_scrollbar_color_factor;
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
            /**
             * @brief Creates a new instance of a Menu.
             * @param x X position of the Menu.
             * @param y Y position of the Menu.
             * @param width Width of the Menu.
             * @param items_clr Color of the items in the Menu.
             * @param items_focus_clr Color of the focused item in the Menu.
             * @param items_height Height of each shown item in the Menu.
             * @param items_to_show Number of items to show in the Menu.
             */
            Menu(const s32 x, const s32 y, const s32 width, const Color items_clr, const Color items_focus_clr, const s32 items_height, const u32 items_to_show);
            PU_SMART_CTOR(Menu)

            inline s32 GetX() override {
                return this->x;
            }

            /**
             * @brief Sets the X position of the Menu.
             * @param x New X position.
             */
            inline void SetX(const s32 x) {
                this->x = x;
            }

            inline s32 GetY() override {
                return this->y;
            }

            /**
             * @brief Sets the Y position of the Menu.
             * @param y New Y position.
             */
            inline void SetY(const s32 y) {
                this->y = y;
            }

            inline s32 GetWidth() override {
                return this->w;
            }

            /**
             * @brief Sets the width of the Menu.
             * @param width New width.
             */
            inline void SetWidth(const s32 width) {
                this->w = width;
            }

            inline s32 GetHeight() override {
                return this->items_h * this->items_to_show;
            }

            PU_CLASS_POD_GETSET(ItemsHeight, items_h, s32)
            PU_CLASS_POD_GETSET(NumberOfItemsToShow, items_to_show, s32)
            PU_CLASS_POD_GETSET(ItemsFocusColor, items_focus_clr, Color)
            PU_CLASS_POD_GETSET(ItemsColor, items_clr, Color)
            PU_CLASS_POD_GETSET(ScrollbarColor, scrollbar_clr, Color)
            PU_CLASS_POD_GETSET(ItemAlphaIncrementSteps, item_alpha_incr_steps, u8)
            PU_CLASS_POD_GETSET(IconItemSizesFactor, icon_item_sizes_factor, float)
            PU_CLASS_POD_GETSET(IconMargin, icon_margin, u32)
            PU_CLASS_POD_GETSET(TextMargin, text_margin, u32)
            PU_CLASS_POD_GETSET(LightScrollbarColorFactor, light_scrollbar_color_factor, u8)
            PU_CLASS_POD_GETSET(ScrollbarWidth, scrollbar_width, u32)
            PU_CLASS_POD_GETSET(ShadowHeight, shadow_height, u32)
            PU_CLASS_POD_GETSET(ShadowBaseAlpha, shadow_base_alpha, u8)
            PU_CLASS_POD_GETSET(MoveWaitTimeMs, move_wait_time_ms, s64)

            /**
             * @brief Sets the font name to use for the Menu.
             * @param font_name Name of the font to use.
             */
            inline void SetOnSelectionChanged(OnSelectionChangedCallback on_selection_changed_cb) {
                this->on_selection_changed_cb = on_selection_changed_cb;
            }

            /**
             * @brief Adds a new item to the Menu.
             * @param item Item to add.
             */
            inline void AddItem(MenuItem::Ref &item) {
                this->items.push_back(item);
            }

            /**
             * @brief Clears all items from the Menu.
             */
            void ClearItems();

            /**
             * @brief Forces the Menu to reload all items.
             */
            inline void ForceReloadItems() {
                this->ReloadItemRenders();
            }

            PU_CLASS_POD_SET(CooldownEnabled, cooldown_enabled, bool)

            /**
             * @brief Gets the selected item of the Menu.
             * @return Selected item of the Menu.
             */
            inline MenuItem::Ref &GetSelectedItem() {
                return this->items.at(this->selected_item_idx);
            }

            /**
             * @brief Gets the items of the Menu.
             * @return Items of the Menu.
             */
            inline std::vector<MenuItem::Ref> &GetItems() {
                return this->items;
            }

            PU_CLASS_POD_GET(SelectedIndex, selected_item_idx, s32)

            /**
             * @brief Sets the selected index of the Menu.
             * @param idx Index to set.
             */
            void SetSelectedIndex(const u32 idx);

            void OnRender(render::Renderer::Ref &drawer, const s32 x, const s32 y) override;
            void OnInput(const u64 keys_down, const u64 keys_up, const u64 keys_held, const TouchPoint touch_pos) override;
    };
}
