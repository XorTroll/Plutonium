#include <pu/element/Menu.hpp>

namespace pu::element
{
    MenuItem::MenuItem(std::string Name)
    {
        this->name = Name;
        this->hasicon = false;
    }

    std::string MenuItem::GetName()
    {
        return this->name;
    }

    void MenuItem::SetName(std::string Name)
    {
        this->name = Name;
    }

    void MenuItem::AddOnClick(std::function<void()> Callback, u64 Key)
    {
        this->cbs.push_back(Callback);
        this->cbipts.push_back(Key);
    }

    u32 MenuItem::GetCallbackCount()
    {
        return this->cbs.size();
    }

    std::function<void()> MenuItem::GetCallback(u32 Index)
    {
        return this->cbs[Index];
    }

    u64 MenuItem::GetCallbackKey(u32 Index)
    {
        return this->cbipts[Index];
    }

    std::string MenuItem::GetIcon()
    {
        return this->icon;
    }

    void MenuItem::SetIcon(std::string Icon)
    {
        std::ifstream ifs(Icon);
        if(ifs.good())
        {
            this->hasicon = true;
            this->icon = Icon;
        }
        ifs.close();
    }

    bool MenuItem::HasIcon()
    {
        return this->hasicon;
    }

    Menu::Menu(u32 X, u32 Y, u32 Width, draw::Color OptionColor, u32 ItemSize, u32 ItemsToShow)
    {
        this->x = X;
        this->y = Y;
        this->w = Width;
        this->clr = OptionColor;
        this->scb = { 110, 110, 110, 255 };
        this->isize = ItemSize;
        this->ishow = ItemsToShow;
        this->previsel = 0;
        this->isel = 0;
        this->fisel = 0;
        this->selfact = 255;
        this->pselfact = 0;
        this->fnt = draw::Font::NintendoStandard;
        this->fsize = 25;
        this->onselch = [&](){};
        this->icdown = false;
    }

    u32 Menu::GetX()
    {
        return this->x;
    }

    void Menu::SetX(u32 X)
    {
        this->x = X;
    }

    u32 Menu::GetY()
    {
        return this->y;
    }

    void Menu::SetY(u32 Y)
    {
        this->y = Y;
    }

    u32 Menu::GetWidth()
    {
        return this->w;
    }

    void Menu::SetWidth(u32 Width)
    {
        this->w = Width;
    }

    u32 Menu::GetHeight()
    {
        return (this->isize * this->ishow);
    }

    u32 Menu::GetItemSize()
    {
        return this->isize;
    }

    void Menu::SetItemSize(u32 ItemSize)
    {
        this->isize = ItemSize;
    }

    u32 Menu::GetNumberOfItemsToShow()
    {
        return this->isize;
    }

    void Menu::SetNumberOfItemsToShow(u32 ItemsToShow)
    {
        this->isize = ItemsToShow;
    }

    draw::Font Menu::GetFont()
    {
        return this->fnt;
    }

    void Menu::SetFont(draw::Font Font)
    {
        this->fnt = Font;
    }

    u32 Menu::GetFontSize()
    {
        return this->fsize;
    }

    void Menu::SetFontSize(u32 Size)
    {
        this->fsize = Size;
    }

    draw::Color Menu::GetColor()
    {
        return this->clr;
    }

    void Menu::SetColor(draw::Color OptionColor)
    {
        this->clr = OptionColor;
    }

    draw::Color Menu::GetScrollbarColor()
    {
        return this->scb;
    }

    void Menu::SetScrollbarColor(draw::Color ScrollbarColor)
    {
        this->scb = ScrollbarColor;
    }

    void Menu::SetOnSelectionChanged(std::function<void()> Callback)
    {
        this->onselch = Callback;
    }

    void Menu::AddItem(MenuItem *Item)
    {
        this->itms.push_back(Item);
    }

    void Menu::ClearItems()
    {
        this->itms.clear();
    }

    void Menu::SetCooldownEnabled(bool Cooldown)
    {
        this->icdown = Cooldown;
    }

    MenuItem *Menu::GetSelectedItem()
    {
        return this->itms[this->isel];
    }

    u32 Menu::GetSelectedIndex()
    {
        return this->isel;
    }

    void Menu::SetSelectedIndex(u32 Index)
    {
        if(this->itms.size() > Index)
        {
            this->isel = Index;
            this->fisel = 0;
            this->selfact = 255;
            this->pselfact = 0;
        }
    }

    void Menu::OnRender(render::Renderer *Drawer)
    {
        if(!this->itms.empty())
        {
            u32 cx = this->x;
            u32 cy = this->y;
            u32 cw = this->w;
            u32 ch = this->isize;
            u32 its = this->ishow;
            if(its > this->itms.size()) its = this->itms.size();
            for(u32 i = this->fisel; i < (its + this->fisel); i++)
            {
                s32 clrr = this->clr.R;
                s32 clrg = this->clr.G;
                s32 clrb = this->clr.B;
                s32 nr = clrr - 70;
                if(nr < 0) nr = 0;
                s32 ng = clrg - 70;
                if(ng < 0) ng = 0;
                s32 nb = clrb - 70;
                if(nb < 0) nb = 0;
                draw::Color nclr(nr, ng, nb, this->clr.A);
                if(this->isel == i)
                {
                    Drawer->DrawRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->selfact < 255)
                    {
                        Drawer->DrawRectangleFill(draw::Color(nr, ng, nb, this->selfact), cx, cy, cw, ch);
                        this->selfact += 48;
                    }
                    else Drawer->DrawRectangleFill(nclr, cx, cy, cw, ch);
                }
                else if(this->previsel == i)
                {
                    Drawer->DrawRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->pselfact > 0)
                    {
                        Drawer->DrawRectangleFill(draw::Color(nr, ng, nb, this->pselfact), cx, cy, cw, ch);
                        this->pselfact -= 48;
                    }
                    else Drawer->DrawRectangleFill(this->clr, cx, cy, cw, ch);
                }
                else Drawer->DrawRectangleFill(this->clr, cx, cy, cw, ch);
                MenuItem *itm = this->itms[i];
                std::string cnt = itm->GetName();
                u32 xh = Drawer->GetTextHeight(this->fnt, cnt, this->fsize);
                u32 tx = (cx + 25);
                u32 ty = ((ch - xh) / 2) + cy;
                if(itm->HasIcon())
                {
                    u32 icd = (this->isize - 10);
                    u32 icx = (cx + 25);
                    u32 icy = (cy + 5);
                    tx = (icx + icd + 25);
                    Drawer->DrawImageScaled(itm->GetIcon(), icx, icy, icd, icd);
                }
                Drawer->DrawText(cnt, this->fnt, this->fsize, tx, ty, { 0, 0, 0, 255 });
                cy += ch;
            }
            if(this->ishow < this->itms.size())
            {
                s32 sccr = this->scb.R;
                s32 sccg = this->scb.G;
                s32 sccb = this->scb.B;
                s32 snr = sccr - 50;
                if(snr < 0) snr = 0;
                s32 sng = sccg - 50;
                if(sng < 0) sng = 0;
                s32 snb = sccb - 50;
                if(snb < 0) snb = 0;
                draw::Color sclr(snr, sng, snb, this->scb.A);
                u32 scx = this->x + (this->w - 20);
                u32 scy = this->y;
                u32 scw = 20;
                u32 sch = (this->ishow * this->isize);
                Drawer->DrawRectangleFill(this->scb, scx, scy, scw, sch);
                u32 fch = ((this->ishow * sch) / this->itms.size());
                u32 fcy = scy + (this->fisel * (sch / this->itms.size()));
                Drawer->DrawRectangleFill(sclr, scx, fcy, scw, fch);
            }
            Drawer->DrawHorizontalShadow(cx, cy, cw, 5, 160);
        }
    }

    void Menu::OnInput(u64 Input)
    {
        if(Input & KEY_DOWN)
        {
            if(this->isel < (this->itms.size() - 1))
            {
                if((this->isel - this->fisel) == (this->ishow - 1))
                {
                    this->fisel++;
                    this->isel++;
                    (this->onselch)();
                }
                else
                {
                    this->previsel = this->isel;
                    this->isel++;
                    (this->onselch)();
                    if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++)
                    {
                        if(i == this->isel) this->selfact = 0;
                        else if(i == this->previsel) this->pselfact = 255;
                    }
                }
            }
        }
        else if(Input & KEY_UP)
        {
            if(this->isel > 0)
            {
                if(this->isel == this->fisel)
                {
                    this->fisel--;
                    this->isel--;
                    (this->onselch)();
                }
                else
                {
                    this->previsel = this->isel;
                    this->isel--;
                    (this->onselch)();
                    if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++)
                    {
                        if(i == this->isel) this->selfact = 0;
                        else if(i == this->previsel) this->pselfact = 255;
                    }
                }
            }
        }
        else
        {
            u32 ipc = this->itms[this->isel]->GetCallbackCount();
            if(ipc > 0) for(u32 i = 0; i < ipc; i++)
            {
                if(Input & this->itms[this->isel]->GetCallbackKey(i))
                {
                    if(this->icdown) this->icdown = false;
                    else (this->itms[this->isel]->GetCallback(i))();
                }
            }
        }
    }
}