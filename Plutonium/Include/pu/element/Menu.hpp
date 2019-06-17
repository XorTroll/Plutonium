
/*

    Plutonium library

    @file Menu.hpp
    @brief A Menu is a very useful Element for option browsing or selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/element/Element.hpp>
#include <vector>
#include <functional>

namespace pu::element
{
    class MenuItem
    {
        public:
            MenuItem(std::string Name);
            ~MenuItem();
            std::string GetName();
            void SetName(std::string Name);
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            void AddOnClick(std::function<void()> Callback, u64 Key = KEY_A);
            s32 GetCallbackCount();
            std::function<void()> GetCallback(s32 Index);
            u64 GetCallbackKey(s32 Index);
            std::string GetIcon();
            void SetIcon(std::string Icon);
            bool HasIcon();
            render::NativeFont GetFont();
            render::NativeTexture GetNameTexture();
            render::NativeTexture GetIconTexture();
        private:
            std::string name;
            draw::Color clr;
            bool hasicon;
            std::string icon;
            std::vector<std::function<void()>> cbs;
            std::vector<u64> cbipts;
            render::NativeFont font;
            render::NativeTexture itex;
            render::NativeTexture ntex;
    };

    class Menu : public Element
    {
        public:
            Menu(s32 X, s32 Y, s32 Width, draw::Color OptionColor, s32 ItemSize, s32 ItemsToShow);
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
            draw::Color GetColor();
            void SetColor(draw::Color Color);
            draw::Color GetOnFocusColor();
            void SetOnFocusColor(draw::Color Color);
            draw::Color GetScrollbarColor();
            void SetScrollbarColor(draw::Color Color);
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
            draw::Color scb;
            draw::Color clr;
            draw::Color fcs;
            bool icdown;
            std::function<void()> onselch;
            std::vector<MenuItem*> itms;
    };
}