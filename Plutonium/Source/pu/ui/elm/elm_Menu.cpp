#include <pu/ui/elm/elm_Menu.hpp>

namespace pu::ui::elm
{
    MenuItem::MenuItem(String Name)
    {
        this->font = render::LoadDefaultFont(25);
        this->clr = { 10, 10, 10, 255 };
        this->name = Name;
        this->ntex = render::RenderText(this->font, Name, this->clr);
        this->hasicon = false;
    }

    MenuItem::~MenuItem()
    {
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
        if(this->hasicon && (this->itex != NULL))
        {
            render::DeleteTexture(this->itex);
            this->itex = NULL;
        }
    }

    String MenuItem::GetName()
    {
        return this->name;
    }

    void MenuItem::SetName(String Name)
    {
        this->name = Name;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->font, Name, this->clr);
    }

    Color MenuItem::GetColor()
    {
        return this->clr;
    }

    void MenuItem::SetColor(Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->font, this->name, Color);
    }

    void MenuItem::AddOnClick(std::function<void()> Callback, u64 Key)
    {
        this->cbs.push_back(Callback);
        this->cbipts.push_back(Key);
    }

    s32 MenuItem::GetCallbackCount()
    {
        return this->cbs.size();
    }

    std::function<void()> MenuItem::GetCallback(s32 Index)
    {
        return this->cbs[Index];
    }

    u64 MenuItem::GetCallbackKey(s32 Index)
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
            this->icon = Icon;
            if(this->hasicon) render::DeleteTexture(this->itex);
            this->itex = render::LoadImage(Icon);
            this->hasicon = true;
        }
        ifs.close();
    }

    bool MenuItem::HasIcon()
    {
        return this->hasicon;
    }

    render::NativeFont MenuItem::GetFont()
    {
        return this->font;
    }

    render::NativeTexture MenuItem::GetNameTexture()
    {
        return this->ntex;
    }

    render::NativeTexture MenuItem::GetIconTexture()
    {
        return this->itex;
    }

    Menu::Menu(s32 X, s32 Y, s32 Width, Color OptionColor, s32 ItemSize, s32 ItemsToShow) : Element::Element()
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
        this->onselch = [&](){};
        this->icdown = false;
        this->dtouch = false;
        this->fcs = { 40, 40, 40, 255 };
        this->basestatus = 0;
    }

    Menu::~Menu()
    {
        this->ClearItems();
    }

    s32 Menu::GetX()
    {
        return this->x;
    }

    void Menu::SetX(s32 X)
    {
        this->x = X;
    }

    s32 Menu::GetY()
    {
        return this->y;
    }

    void Menu::SetY(s32 Y)
    {
        this->y = Y;
    }

    s32 Menu::GetWidth()
    {
        return this->w;
    }

    void Menu::SetWidth(s32 Width)
    {
        this->w = Width;
    }

    s32 Menu::GetHeight()
    {
        return (this->isize * this->ishow);
    }

    s32 Menu::GetItemSize()
    {
        return this->isize;
    }

    void Menu::SetItemSize(s32 ItemSize)
    {
        this->isize = ItemSize;
    }

    s32 Menu::GetNumberOfItemsToShow()
    {
        return this->ishow;
    }

    void Menu::SetNumberOfItemsToShow(s32 ItemsToShow)
    {
        this->ishow = ItemsToShow;
    }

    Color Menu::GetColor()
    {
        return this->clr;
    }

    void Menu::SetColor(Color Color)
    {
        this->clr = Color;
    }
    
    Color Menu::GetOnFocusColor()
    {
        return this->fcs;
    }

    void Menu::SetOnFocusColor(Color Color)
    {
        this->fcs = Color;
    }

    Color Menu::GetScrollbarColor()
    {
        return this->scb;
    }

    void Menu::SetScrollbarColor(Color Color)
    {
        this->scb = Color;
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
        if(!this->itms.empty()) for(s32 i = 0; i < this->itms.size(); i++) delete this->itms[i];
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

    s32 Menu::GetSelectedIndex()
    {
        return this->isel;
    }

    void Menu::SetSelectedIndex(s32 Index)
    {
        if(this->itms.size() > Index)
        {
            this->isel = Index;
            this->fisel = 0;
            if(this->isel > 0)
            {
                u32 div = (this->itms.size() + this->ishow - 1) / this->ishow;
                for(u32 i = 0; i < div; i++)
                {
                    if((this->ishow * i) > this->isel)
                    {
                        this->fisel = this->ishow * (i - 1);
                        break;
                    }
                }
            }
            this->selfact = 255;
            this->pselfact = 0;
        }
    }

    void Menu::OnRender(render::Renderer *Drawer)
    {
        if(!this->itms.empty())
        {
            s32 cx = this->x;
            s32 cy = this->y;
            s32 cw = this->w;
            s32 ch = this->isize;
            s32 its = this->ishow;
            if(its > this->itms.size()) its = this->itms.size();
            if((its + this->fisel) > this->itms.size()) its = this->itms.size() - this->fisel;
            for(s32 i = this->fisel; i < (its + this->fisel); i++)
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
                Color nclr(nr, ng, nb, this->clr.A);
                if(this->isel == i)
                {
                    Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->selfact < 255)
                    {
                        Drawer->RenderRectangleFill(Color(this->fcs.R, this->fcs.G, this->fcs.B, this->selfact), cx, cy, cw, ch);
                        this->selfact += 48;
                    }
                    else Drawer->RenderRectangleFill(this->fcs, cx, cy, cw, ch);
                }
                else if(this->previsel == i)
                {
                    Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->pselfact > 0)
                    {
                        Drawer->RenderRectangleFill(Color(this->fcs.R, this->fcs.G, this->fcs.B, this->pselfact), cx, cy, cw, ch);
                        this->pselfact -= 48;
                    }
                    else Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                }
                else Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                MenuItem *itm = this->itms[i];
                s32 xh = render::GetTextHeight(itm->GetFont(), itm->GetName());
                s32 tx = (cx + 25);
                s32 ty = ((ch - xh) / 2) + cy;
                if(itm->HasIcon())
                {
                    s32 icd = (this->isize - 10);
                    s32 icx = (cx + 25);
                    s32 icy = (cy + 5);
                    tx = (icx + icd + 25);
                    Drawer->RenderTextureScaled(itm->GetIconTexture(), icx, icy, icd, icd);
                }
                Drawer->RenderTexture(itm->GetNameTexture(), tx, ty);
                cy += ch;
            }
            if(this->ishow < this->itms.size())
            {
                s32 sccr = this->scb.R;
                s32 sccg = this->scb.G;
                s32 sccb = this->scb.B;
                s32 snr = sccr - 30;
                if(snr < 0) snr = 0;
                s32 sng = sccg - 30;
                if(sng < 0) sng = 0;
                s32 snb = sccb - 30;
                if(snb < 0) snb = 0;
                Color sclr(snr, sng, snb, this->scb.A);
                s32 scx = this->x + (this->w - 20);
                s32 scy = this->y;
                s32 scw = 20;
                s32 sch = (this->ishow * this->isize);
                Drawer->RenderRectangleFill(this->scb, scx, scy, scw, sch);
                s32 fch = ((this->ishow * sch) / this->itms.size());
                s32 fcy = scy + (this->fisel * (sch / this->itms.size()));
                Drawer->RenderRectangleFill(sclr, scx, fcy, scw, fch);
            }
            Drawer->RenderShadowSimple(cx, cy, cw, 5, 160);
        }
    }

    void Menu::OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus)
    {
        if(basestatus == 1)
        {
            auto curtime = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(curtime - basetime).count();
            if(diff >= 150)
            {
                basestatus = 2;
            }
        }
        if(Touch)
        {
            touchPosition tch;
            hidTouchRead(&tch, 0);
            s32 cx = this->x;
            s32 cy = this->y;
            s32 cw = this->w;
            s32 ch = this->isize;
            s32 its = this->ishow;
            if(its > this->itms.size()) its = this->itms.size();
            for(s32 i = this->fisel; i < (this->fisel + its); i++)
            {
                if(((cx + cw) > tch.px) && (tch.px > cx) && ((cy + ch) > tch.py) && (tch.py > cy))
                {
                    this->dtouch = true;
                    this->previsel = this->isel;
                    this->isel = i;
                    (this->onselch)();
                    if(i == this->isel) this->selfact = 255;
                    else if(i == this->previsel) this->pselfact = 0;
                    break;
                }
                cy += this->isize;
            }
        }
        else if(this->dtouch)
        {
            if((this->selfact >= 255) && (this->pselfact <= 0))
            {
                if(this->icdown) this->icdown = false;
                else (this->itms[this->isel]->GetCallback(0))();
                this->dtouch = false;
            }
        }
        else
        {
            if((Down & KEY_DDOWN) || (Down & KEY_LSTICK_DOWN) || (Held & KEY_RSTICK_DOWN))
            {
                bool move = true;
                if(Held & KEY_RSTICK_DOWN)
                {
                    move = false;
                    if(basestatus == 0)
                    {
                        basetime = std::chrono::steady_clock::now();
                        basestatus = 1;
                    }
                    else if(basestatus == 2)
                    {
                        basestatus = 0;
                        move = true;
                    }
                }
                if(move)
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
                            if(!this->itms.empty()) for(s32 i = 0; i < this->itms.size(); i++)
                            {
                                if(i == this->isel) this->selfact = 0;
                                else if(i == this->previsel) this->pselfact = 255;
                            }
                        }
                    }
                    else
                    {
                        this->isel = 0;
                        this->fisel = 0;
                    }
                }
            }
            else if((Down & KEY_DUP) || (Down & KEY_LSTICK_UP) || (Held & KEY_RSTICK_UP))
            {
                bool move = true;
                if(Held & KEY_RSTICK_UP)
                {
                    move = false;
                    if(basestatus == 0)
                    {
                        basetime = std::chrono::steady_clock::now();
                        basestatus = 1;
                    }
                    else if(basestatus == 2)
                    {
                        basestatus = 0;
                        move = true;
                    }
                }
                if(move)
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
                            if(!this->itms.empty()) for(s32 i = 0; i < this->itms.size(); i++)
                            {
                                if(i == this->isel) this->selfact = 0;
                                else if(i == this->previsel) this->pselfact = 255;
                            }
                        }
                    }
                    else
                    {
                        this->isel = this->itms.size() - 1;
                        this->fisel = 0;
                        if(this->itms.size() >= this->ishow) this->fisel = this->itms.size() - this->ishow;
                    }
                }
            }
            else
            {
                s32 ipc = this->itms[this->isel]->GetCallbackCount();
                if(ipc > 0) for(s32 i = 0; i < ipc; i++)
                {
                    if(Down & this->itms[this->isel]->GetCallbackKey(i))
                    {
                        if(this->icdown) this->icdown = false;
                        else (this->itms[this->isel]->GetCallback(i))();
                    }
                }
            }
        }
    }
}