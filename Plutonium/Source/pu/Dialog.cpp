#include <pu/Dialog.hpp>
#include <pu/Application.hpp>
#include <cmath>

namespace pu
{
    Dialog::Dialog(std::string Title, std::string Content)
    {
        this->tfont = render::LoadSharedFont(render::SharedFont::Standard, 30);
        this->cfont = render::LoadSharedFont(render::SharedFont::Standard, 20);
        this->ofont = render::LoadSharedFont(render::SharedFont::Standard, 18);
        this->title = render::RenderText(this->tfont, Title, { 10, 10, 10, 255 });
        this->cnt = render::RenderText(this->cfont, Content, { 20, 20, 20, 255 });
        this->osel = 0;
        this->prevosel = 0;
        this->selfact = 255;
        this->pselfact = 0;
        this->hicon = false;
        this->cancel = false;
        this->hcancel = false;
    }

    Dialog::~Dialog()
    {
        if(this->tfont != NULL)
        {
            render::DeleteFont(this->tfont);
            this->tfont = NULL;
        }
        if(this->cfont != NULL)
        {
            render::DeleteFont(this->cfont);
            this->cfont = NULL;
        }
        if(this->ofont != NULL)
        {
            render::DeleteFont(this->ofont);
            this->ofont = NULL;
        }
        if(this->title != NULL)
        {
            render::DeleteTexture(this->title);
            this->title = NULL;
        }
        if(this->cnt != NULL)
        {
            render::DeleteTexture(this->cnt);
            this->cnt = NULL;
        }
        if(this->hicon && (this->icon != NULL))
        {
            render::DeleteTexture(this->icon);
            this->icon = NULL;
            this->hicon = false;
        }
        if(!this->opts.empty()) for(u32 i = 0; i < this->opts.size(); i++) render::DeleteTexture(this->opts[i]);
        this->opts.clear();
        this->sopts.clear();
    }

    void Dialog::AddOption(std::string Name)
    {
        this->opts.push_back(render::RenderText(this->ofont, Name, { 10, 10, 10, 255 }));
        this->sopts.push_back(Name);
    }

    void Dialog::SetCancelOption(std::string Name)
    {
        this->hcancel = true;
        this->scancel = Name;
    }

    void Dialog::RemoveCancelOption()
    {
        this->hcancel = false;
        this->scancel = "";
    }

    bool Dialog::HasCancelOption()
    {
        return this->hcancel;
    }

    void Dialog::SetIcon(std::string Icon)
    {
        if(this->hicon) render::DeleteTexture(this->icon);
        this->icon = render::LoadImage(Icon);
        this->hicon = true;
    }

    bool Dialog::Hasicon()
    {
        return this->hicon;
    }

    u32 Dialog::Show(render::Renderer *Drawer, void *App)
    {
        if(this->hcancel) this->AddOption(this->scancel);
        if(this->opts.empty()) return 0;
        u32 dw = (20 * (this->opts.size() - 1)) + 250;
        for(u32 i = 0; i < this->opts.size(); i++)
        {
            u32 tw = render::GetTextWidth(this->ofont, this->sopts[i]);
            dw += tw + 20;
        }
        if(dw > 1280) dw = 1280;
        u32 icm = 30;
        u32 elemh = 60;
        u32 tdw = render::GetTextureWidth(this->cnt) + 90;
        if(tdw > dw) dw = tdw;
        tdw = render::GetTextureWidth(this->title) + 90;
        if(tdw > dw) dw = tdw;
        u32 ely = render::GetTextureHeight(this->title) + render::GetTextureHeight(this->cnt) + 140;
        if(this->hicon)
        {
            u32 tely = render::GetTextureHeight(this->icon) + icm + 25;
            if(tely > ely) ely = tely;
            tdw = render::GetTextureWidth(this->cnt) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
            tdw = render::GetTextureWidth(this->title) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
        }
        if(dw > 1280) dw = 1280;
        u32 dh = ely + elemh + 30;
        if(dh > 720) dh = 720;
        u32 dx = (1280 - dw) / 2;
        u32 dy = (720 - dh) / 2;
        ely += dy;
        u32 elemw = ((dw - (20 * (this->opts.size() + 1))) / this->opts.size());
        u32 elx = dx + ((dw - ((elemw * this->opts.size()) + (20 * (this->opts.size() - 1)))) / 2);
        u32 r = 35;
        u32 nr = 180;
        u32 ng = 180;
        u32 nb = 200;
        bool end = false;
        s32 initfact = 0;
        while(true)
        {
            bool ok = ((Application*)App)->CallForRenderWithRenderOver([&](render::Renderer *Drawer) -> bool
            {
                u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
                u64 h = hidKeysHeld(CONTROLLER_P1_AUTO);
                if((k & KEY_DLEFT) || (k & KEY_LSTICK_LEFT) || (h & KEY_RSTICK_LEFT))
                {
                    if(this->osel > 0)
                    {
                        this->prevosel = this->osel;
                        this->osel--;
                        for(u32 i = 0; i < this->opts.size(); i++)
                        {
                            if(i == this->osel) this->selfact = 0;
                            else if(i == this->prevosel) this->pselfact = 255;
                        }
                    }
                }
                else if((k & KEY_DRIGHT) || (k & KEY_LSTICK_RIGHT) || (h & KEY_RSTICK_RIGHT))
                {
                    if(this->osel < (this->opts.size() - 1))
                    {
                        this->prevosel = this->osel;
                        this->osel++;
                        for(u32 i = 0; i < this->opts.size(); i++)
                        {
                            if(i == this->osel) this->selfact = 0;
                            else if(i == this->prevosel) this->pselfact = 255;
                        }
                    }
                }
                else if(k & KEY_A)
                {
                    this->cancel = false;
                    end = true;
                }
                else if(k & KEY_B)
                {
                    this->cancel = true;
                    end = true;
                }
                else if(hidKeysDown(CONTROLLER_HANDHELD) & KEY_TOUCH)
                {
                    touchPosition tch;
                    hidTouchRead(&tch, 0);
                    for(u32 i = 0; i < this->opts.size(); i++)
                    {
                        std::string txt = this->sopts[i];
                        u32 rx = elx + ((elemw + 20) * i);
                        u32 ry = ely;
                        if(((rx + elemw) > tch.px) && (tch.px > rx) && ((ry + elemh) > tch.py) && (tch.py > ry))
                        {
                            this->osel = i;
                            this->cancel = false;
                            end = true;
                        }
                    }
                }
                u32 bw = dw;
                u32 bh = dh;
                u32 fw = bw - (r * 2);
                u32 fh = bh - (r * 2);
                draw::Color clr = { 225, 225, 225, initfact };
                s32 aclr = initfact;
                if(aclr < 0) aclr = 0;
                if(aclr > 125) aclr = 125;
                Drawer->RenderRectangleFill({ 0, 0, 0, (u8)aclr }, 0, 0, 1280, 720);
                Drawer->RenderRoundedRectangleFill(clr, dx, dy, bw, bh, r);
                render::SetAlphaValue(this->title, initfact);
                render::SetAlphaValue(this->cnt, initfact);
                Drawer->RenderTexture(this->title, (dx + 45), (dy + 55));
                Drawer->RenderTexture(this->cnt, (dx + 45), (dy + 140));
                if(this->hicon)
                {
                    u32 icw = render::GetTextureWidth(this->icon);
                    u32 icx = dx + (dw - (icw + icm));
                    u32 icy = dy + icm;
                    Drawer->RenderTexture(this->icon, icx, icy, initfact);
                }
                for(u32 i = 0; i < this->opts.size(); i++)
                {
                    std::string txt = this->sopts[i];
                    u32 tw = render::GetTextWidth(this->ofont, txt);
                    u32 th = render::GetTextHeight(this->ofont, txt);
                    u32 tx = elx + ((elemw - tw) / 2) + ((elemw + 20) * i);
                    u32 ty = ely + ((elemh - th) / 2);
                    u32 rx = elx + ((elemw + 20) * i);
                    u32 ry = ely;
                    u32 rr = (elemh / 2);
                    draw::Color dclr = { nr, ng, nb, initfact };
                    if(this->osel == i)
                    {
                        if(this->selfact < 255)
                        {
                            dclr = { nr, ng, nb, this->selfact };
                            Drawer->RenderRoundedRectangleFill(dclr, rx, ry, elemw, elemh, rr);
                            this->selfact += 48;
                        }
                        else
                        {
                            dclr = { nr, ng, nb, initfact };
                            Drawer->RenderRoundedRectangleFill(dclr, rx, ry, elemw, elemh, rr);
                        }
                    }
                    else if(this->prevosel == i)
                    {
                        if(this->pselfact > 0)
                        {
                            dclr = { nr, ng, nb, this->pselfact };
                            Drawer->RenderRoundedRectangleFill(dclr, rx, ry, elemw, elemh, rr);
                            this->pselfact -= 48;
                        }
                    }
                    render::SetAlphaValue(this->opts[i], initfact);
                    Drawer->RenderTexture(this->opts[i], tx, ty);
                }
                if(end)
                {
                    if(initfact == 0) return false;
                    if(initfact > 0) initfact -= 25;
                    if(initfact < 0) initfact = 0;
                }
                else
                {
                    if(initfact < 255) initfact += 25;
                    if(initfact > 255) initfact = 255;
                }
                return true;
            });
            if(!ok)
            {
                ((Application*)App)->CallForRenderWithRenderOver([&](render::Renderer *Drawer) -> bool {});
                break;
            }
        }
        return this->osel;
    }

    bool Dialog::UserCancelled()
    {
        return this->cancel;
    }

    bool Dialog::IsOk()
    {
        bool ok = true;
        if(this->cancel) ok = false;
        if(this->hcancel && (this->osel == (this->opts.size() - 1))) ok = false;
        return ok;
    }
}