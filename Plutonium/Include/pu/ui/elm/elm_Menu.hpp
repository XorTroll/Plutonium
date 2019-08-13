
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
            String GetName();
            void SetName(String Name);
            String GetExtend();
            void SetExtend(String Name);
            Color GetColor();
            void SetColor(Color Color);
            void AddOnClick(std::function<void()> Callback, u64 Key = KEY_A);
            s32 GetCallbackCount();
            std::function<void()> GetCallback(s32 Index);
            u64 GetCallbackKey(s32 Index);
            std::string GetIcon();
            void SetIcon(std::string Icon);
            std::string GetExtendIcon();
            void SetExtendIcon(std::string ExtendedIcon);
            bool HasIcon();
            bool HasExtend();
            bool HasExtendIcon();
        private:
            String name;
            String extend;
            Color clr;
            bool hasicon;
            bool hasextend;
            bool hasextendicon;
            std::string icon;
            std::string extendIcon;
            std::vector<std::function<void()>> cbs;
            std::vector<u64> cbipts;
    };

    class Menu : public Element
    {
        public:
            Menu(s32 X, s32 Y, s32 Width, Color OptionColor, s32 ItemSize, s32 ItemsToShow);
            ~Menu();
            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            void SetWidth(s32 Width);
            s32 GetHeight();
            s32 GetItemSize();
            void SetItemSize(s32 ItemSize);
            s32 GetNumberOfItemsToShow();
            void SetNumberOfItemsToShow(s32 ItemsToShow);
            Color GetColor();
            void SetColor(Color Color);
            Color GetOnFocusColor();
            void SetOnFocusColor(Color Color);
            Color GetScrollbarColor();
            void SetScrollbarColor(Color Color);
            void SetOnSelectionChanged(std::function<void()> Callback);
            void AddItem(MenuItem *Item);
            void ClearItems();
            void SetCooldownEnabled(bool Cooldown);
            MenuItem *GetSelectedItem();
            s32 GetSelectedIndex();
            void SetSelectedIndex(s32 Index);
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);
        private:
            void ReloadItemRenders();
            bool dtouch;
            s32 x;
            s32 y;
            s32 w;
            s32 isize;
            s32 ishow;
            s32 previsel;
            s32 fisel;
            s32 isel;
            s32 pselfact;
            s32 selfact;
            Color scb;
            Color clr;
            Color fcs;
            bool icdown;
            int basestatus;
            std::chrono::time_point<std::chrono::steady_clock> basetime;
            std::function<void()> onselch;
            std::vector<MenuItem*> itms;
            render::NativeFont font;
            std::vector<render::NativeTexture> loadednames;
            std::vector<render::NativeTexture> loadedicons;
            std::vector<render::NativeTexture> loadedext;
            std::vector<render::NativeTexture> loadedexticons;
    };
}