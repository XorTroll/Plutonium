
#pragma once
#include <pn/fw/Element.hpp>
#include <vector>
#include <functional>

namespace pn::fw
{
    class MenuItem
    {
        public:
            MenuItem(std::string Name);
            std::string GetName();
            void SetName(std::string Name);
            void SetOnClick(std::function<void()> Callback);
            std::function<void()> GetCallback();
        private:
            std::string name;
            std::function<void()> cb;
    };

    class Menu : public Element
    {
        public:
            Menu(u32 X, u32 Y, u32 Width, draw::Color OptionColor, u32 ItemSize, u32 ItemsToShow);
            u32 GetX();
            void SetX(u32 X);
            u32 GetY();
            void SetY(u32 Y);
            u32 GetWidth();
            void SetWidth(u32 Width);
            u32 GetHeight();
            u32 GetItemSize();
            void SetItemSize(u32 ItemSize);
            u32 GetNumberOfItemsToShow();
            void SetNumberOfItemsToShow(u32 ItemsToShow);
            draw::Color GetColor();
            void SetColor(draw::Color OptionColor);
            void AddItem(MenuItem *Item);
            void ClearItems();
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Input);
        private:
            u32 x;
            u32 y;
            u32 w;
            u32 isize;
            u32 ishow;
            u32 previsel;
            u32 fisel;
            u32 isel;
            s32 pselfact;
            s32 selfact;
            draw::Color clr;
            std::vector<MenuItem*> itms;
    };
}