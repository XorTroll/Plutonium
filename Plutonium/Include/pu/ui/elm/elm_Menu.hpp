
/*

    Plutonium library

    @file Menu.hpp
    @brief A Menu is a very useful Element for option browsing or selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_String.hpp>
#include <pu/ui/elm/elm_Element.hpp>
#include <vector>
#include <chrono>
#include <functional>

namespace pu::ui::elm
{
    class MenuItem
    {
        public:
            MenuItem(String Name);
            PU_SMART_CTOR(MenuItem)

            String GetName();
            void SetName(String Name);
            Color GetColor();
            void SetColor(Color Color);
            void AddOnClick(std::function<void()> Callback, u64 Key = HidNpadButton_A);
            i32 GetCallbackCount();
            std::function<void()> GetCallback(i32 Index);
            u64 GetCallbackKey(i32 Index);
            std::string GetIcon();
            void SetIcon(std::string Icon);
            bool HasIcon();
        private:
            String name;
            Color clr;
            bool hasicon;
            std::string icon;
            std::vector<std::function<void()>> cbs;
            std::vector<u64> cbipts;
    };

    class Menu : public Element
    {
        public:
            Menu(i32 X, i32 Y, i32 Width, Color OptionColor, i32 ItemSize, i32 ItemsToShow);
            PU_SMART_CTOR(Menu)

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            void SetWidth(i32 Width);
            i32 GetHeight();
            i32 GetItemSize();
            void SetItemSize(i32 ItemSize);
            i32 GetNumberOfItemsToShow();
            void SetNumberOfItemsToShow(i32 ItemsToShow);
            Color GetColor();
            void SetColor(Color Color);
            Color GetOnFocusColor();
            void SetOnFocusColor(Color Color);
            Color GetScrollbarColor();
            void SetScrollbarColor(Color Color);
            void SetOnSelectionChanged(std::function<void()> Callback);
            void AddItem(MenuItem::Ref &Item);
            void ClearItems();
            void SetCooldownEnabled(bool Cooldown);
            MenuItem::Ref &GetSelectedItem();
            std::vector<MenuItem::Ref> &GetItems();
            i32 GetSelectedIndex();
            void SetSelectedIndex(i32 Index);
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            void ReloadItemRenders();
            bool dtouch;
            i32 x;
            i32 y;
            i32 w;
            i32 isize;
            i32 ishow;
            i32 previsel;
            i32 fisel;
            i32 isel;
            i32 pselfact;
            i32 selfact;
            Color scb;
            Color clr;
            Color fcs;
            bool icdown;
            int basestatus;
            std::chrono::time_point<std::chrono::steady_clock> basetime;
            std::function<void()> onselch;
            std::vector<MenuItem::Ref> itms;
            String font_name;
            std::vector<sdl2::Texture> loadednames;
            std::vector<sdl2::Texture> loadedicons;
    };
}