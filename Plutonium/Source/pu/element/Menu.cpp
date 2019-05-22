#include <pu/element/Menu.hpp>

namespace pu::element
{
    MenuItem::MenuItem(std::string Name)
    {
        this->font = render::LoadSharedFont(render::SharedFont::Standard, 25);
        this->clr = { 10, 10, 10, 255 };
        this->name = Name;
        this->ntex = render::RenderText(this->font, Name, this->clr);
        this->hasicon = false;
    }

    MenuItem::~MenuItem()
    {
        if(this->font != NULL)
        {
            render::DeleteFont(this->font);
            this->font = NULL;
        }
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

    std::string MenuItem::GetName()
    {
        return this->name;
    }

    void MenuItem::SetName(std::string Name)
    {
        this->name = Name;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->font, Name, this->clr);
    }

    draw::Color MenuItem::GetColor()
    {
        return this->clr;
    }

    void MenuItem::SetColor(draw::Color Color)
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

    Menu::Menu(u32 X, u32 Y, u32 Width, draw::Color OptionColor, u32 ItemSize, u32 ItemsToShow) : Element::Element()
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
        this->uptime = false;
        this->uphold = false;
        this->downtime = false;
        this->downhold = false;
		this->drawShadow = true;
    }

    Menu::~Menu()
    {
        this->ClearItems();
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
        return this->ishow;
    }

    void Menu::SetNumberOfItemsToShow(u32 ItemsToShow)
    {
        this->ishow = ItemsToShow;
    }

    draw::Color Menu::GetColor()
    {
        return this->clr;
    }

    void Menu::SetColor(draw::Color Color)
    {
        this->clr = Color;
    }
    
    draw::Color Menu::GetOnFocusColor()
    {
        return this->fcs;
    }

    void Menu::SetOnFocusColor(draw::Color Color)
    {
        this->fcs = Color;
    }

    draw::Color Menu::GetScrollbarColor()
    {
        return this->scb;
    }

    void Menu::SetScrollbarColor(draw::Color Color)
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
        if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++) delete this->itms[i];
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

	void Menu::SetDrawShadow(bool drawShadow)
	{
		this->drawShadow = drawShadow;
	}

    void Menu::OnRender(render::Renderer *Drawer)
    {
        u32 rdx = this->GetProcessedX();
        u32 rdy = this->GetProcessedY();
        if(!this->itms.empty())
        {
            u32 cx = rdx;
            u32 cy = rdy;
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
                    Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->selfact < 255)
                    {
                        Drawer->RenderRectangleFill(draw::Color(this->fcs.R, this->fcs.G, this->fcs.B, this->selfact), cx, cy, cw, ch);
                        this->selfact += 48;
                    }
                    else Drawer->RenderRectangleFill(this->fcs, cx, cy, cw, ch);
                }
                else if(this->previsel == i)
                {
                    Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                    if(this->pselfact > 0)
                    {
                        Drawer->RenderRectangleFill(draw::Color(this->fcs.R, this->fcs.G, this->fcs.B, this->pselfact), cx, cy, cw, ch);
                        this->pselfact -= 48;
                    }
                    else Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                }
                else Drawer->RenderRectangleFill(this->clr, cx, cy, cw, ch);
                MenuItem *itm = this->itms[i];
                u32 xh = render::GetTextHeight(itm->GetFont(), itm->GetName());
                u32 tx = (cx + 25);
                u32 ty = ((ch - xh) / 2) + cy;
                if(itm->HasIcon())
                {
                    u32 icd = (this->isize - 10);
                    u32 icx = (cx + 25);
                    u32 icy = (cy + 5);
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
                draw::Color sclr(snr, sng, snb, this->scb.A);
                u32 scx = rdx + (this->w - 20);
                u32 scy = rdy;
                u32 scw = 20;
                u32 sch = (this->ishow * this->isize);
                Drawer->RenderRectangleFill(this->scb, scx, scy, scw, sch);
                u32 fch = ((this->ishow * sch) / this->itms.size());
                u32 fcy = scy + (this->fisel * (sch / this->itms.size()));
                Drawer->RenderRectangleFill(sclr, scx, fcy, scw, fch);
            }

			if(this->drawShadow)
				Drawer->RenderShadowSimple(cx, cy, cw, 5, 160);
        }
    }

    void Menu::OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus)
    {
        u32 rdx = this->GetProcessedX();
        u32 rdy = this->GetProcessedY();
        if(Touch)
        {
            touchPosition tch;
            hidTouchRead(&tch, 0);
            u32 cx = rdx;
            u32 cy = rdx;
            u32 cw = this->w;
            u32 ch = this->isize;
            u32 its = this->ishow;
            if(its > this->itms.size()) its = this->itms.size();
            for(u32 i = this->fisel; i < (this->fisel + its); i++)
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
            if(Down & KEY_DOWN)
            {
                if(!downtime) this->downtp = std::chrono::steady_clock::now();
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
                else
                {
                    this->isel = 0;
                    this->fisel = 0;
                    (this->onselch)();
                    if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++)
                    {
                        if(i == this->isel) this->selfact = 0;
                        else if(i == this->previsel) this->pselfact = 255;
                    }
                }
                downtime = !downtime;
            }
            else if(Down & KEY_UP)
            {
                if(!uptime) this->uptp = std::chrono::steady_clock::now();
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
                else
                {
                    this->isel = this->itms.size() - 1;
                    if(this->itms.size() > this->ishow) this->fisel = this->itms.size() - this->ishow;
                    else this->fisel = 0;
                    (this->onselch)();
                    if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++)
                    {
                        if(i == this->isel) this->selfact = 0;
                        else if(i == this->previsel) this->pselfact = 255;
                    }
                }
                uptime = !uptime;
            }
            else
            {
                u32 ipc = this->itms[this->isel]->GetCallbackCount();
                if(ipc > 0) for(u32 i = 0; i < ipc; i++)
                {
                    if(Down & this->itms[this->isel]->GetCallbackKey(i))
                    {
                        if(this->icdown) this->icdown = false;
                        else (this->itms[this->isel]->GetCallback(i))();
                    }
                }
            }
            auto curtp = std::chrono::steady_clock::now();
            if(downtime && !downhold)
            {
                u64 downdiff = std::chrono::duration_cast<std::chrono::milliseconds>(curtp - this->downtp).count();
                if(downdiff >= 500)
                {
                    downhold = true;
                }
            }
            else if(downhold)
            {
                if(Held & KEY_DOWN)
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
                    else
                    {
                        this->isel = 0;
                        this->fisel = 0;
                        (this->onselch)();
                        if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++)
                        {
                            if(i == this->isel) this->selfact = 0;
                            else if(i == this->previsel) this->pselfact = 255;
                        }
                    }
                }
                else
                {
                    downhold = false;
                    downtime = false;
                }
            }
            if(uptime && !uphold)
            {
                u64 updiff = std::chrono::duration_cast<std::chrono::milliseconds>(curtp - this->uptp).count();
                if(updiff >= 500)
                {
                    uphold = true;
                }
            }
            else if(uphold)
            {
                if(Held & KEY_UP)
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
                    else
                    {
                        this->isel = this->itms.size() - 1;
                        if(this->itms.size() > this->ishow) this->fisel = this->itms.size() - this->ishow;
                        else this->fisel = 0;
                        (this->onselch)();
                        if(!this->itms.empty()) for(u32 i = 0; i < this->itms.size(); i++)
                        {
                            if(i == this->isel) this->selfact = 0;
                            else if(i == this->previsel) this->pselfact = 255;
                        }
                    }
                }
                else
                {
                    uphold = false;
                    uptime = false;
                }
            }
        }
    }
}