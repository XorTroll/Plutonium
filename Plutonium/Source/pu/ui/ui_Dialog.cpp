#include <pu/ui/ui_Dialog.hpp>
#include <pu/ui/ui_Application.hpp>
#include <cmath>

namespace pu::ui
{
    Dialog::Dialog(String Title, String Content)
    {
        this->tfont = render::LoadDefaultFont(30);
        this->cfont = render::LoadDefaultFont(20);
        this->ofont = render::LoadDefaultFont(18);
        this->stitle = Title;
        this->scnt = Content;
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
        for(auto &opt: this->opts) render::DeleteTexture(opt);
    }

    void Dialog::AddOption(String Name)
    {
        this->opts.push_back(render::RenderText(this->ofont, Name, { 10, 10, 10, 255 }));
        this->sopts.push_back(Name);
    }

    void Dialog::SetCancelOption(String Name)
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

    s32 Dialog::Show(render::Renderer::Ref &Drawer, void *App)
    {
        if(this->hcancel) this->AddOption(this->scancel);
        if(this->opts.empty()) return 0;
        s32 dw = (20 * (this->opts.size() - 1)) + 250;
        for(s32 i = 0; i < this->opts.size(); i++)
        {
            s32 tw = render::GetTextWidth(this->ofont, this->sopts[i]);
            dw += tw + 20;
        }
        if(dw > 1280) dw = 1280;
        s32 icm = 30;
        s32 elemh = 60;
        s32 tdw = render::GetTextWidth(this->cfont, this->scnt) + 90;
        if(tdw > dw) dw = tdw;
        tdw = render::GetTextWidth(this->tfont, this->stitle) + 90;
        if(tdw > dw) dw = tdw;
        s32 ely = render::GetTextHeight(this->tfont, this->stitle) + render::GetTextHeight(this->cfont, this->scnt) + 140;
        if(this->hicon)
        {
            s32 tely = render::GetTextureHeight(this->icon) + icm + 25;
            if(tely > ely) ely = tely;
            tdw = render::GetTextWidth(this->cfont, this->scnt) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
            tdw = render::GetTextWidth(this->tfont, this->stitle) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
        }
        if(dw > 1280) dw = 1280;
        s32 dh = ely + elemh + 30;
        if(dh > 720) dh = 720;
        s32 dx = (1280 - dw) / 2;
        s32 dy = (720 - dh) / 2;
        ely += dy;
        s32 elemw = ((dw - (20 * (this->opts.size() + 1))) / this->opts.size());
        s32 elx = dx + ((dw - ((elemw * this->opts.size()) + (20 * (this->opts.size() - 1)))) / 2);
        s32 r = 35;
        s32 nr = 180;
        s32 ng = 180;
        s32 nb = 200;
        bool end = false;
        s32 initfact = 0;
        while(true)
        {
            bool ok = ((Application*)App)->CallForRenderWithRenderOver([&](render::Renderer::Ref &Drawer) -> bool
            {
                u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
                u64 h = hidKeysHeld(CONTROLLER_P1_AUTO);
                if((k & KEY_DLEFT) || (k & KEY_LSTICK_LEFT) || (h & KEY_RSTICK_LEFT))
                {
                    if(this->osel > 0)
                    {
                        this->prevosel = this->osel;
                        this->osel--;
                        for(s32 i = 0; i < this->opts.size(); i++)
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
                        for(s32 i = 0; i < this->opts.size(); i++)
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
                    for(s32 i = 0; i < this->opts.size(); i++)
                    {
                        String txt = this->sopts[i];
                        s32 rx = elx + ((elemw + 20) * i);
                        s32 ry = ely;
                        if(((rx + elemw) > tch.px) && (tch.px > rx) && ((ry + elemh) > tch.py) && (tch.py > ry))
                        {
                            this->osel = i;
                            this->cancel = false;
                            end = true;
                        }
                    }
                }
                s32 bw = dw;
                s32 bh = dh;
                s32 fw = bw - (r * 2);
                s32 fh = bh - (r * 2);
                Color clr = { 225, 225, 225, initfact };
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
                    s32 icw = render::GetTextureWidth(this->icon);
                    s32 icx = dx + (dw - (icw + icm));
                    s32 icy = dy + icm;
                    Drawer->RenderTexture(this->icon, icx, icy, initfact);
                }
                for(s32 i = 0; i < this->opts.size(); i++)
                {
                    String txt = this->sopts[i];
                    s32 tw = render::GetTextWidth(this->ofont, txt);
                    s32 th = render::GetTextHeight(this->ofont, txt);
                    s32 tx = elx + ((elemw - tw) / 2) + ((elemw + 20) * i);
                    s32 ty = ely + ((elemh - th) / 2);
                    s32 rx = elx + ((elemw + 20) * i);
                    s32 ry = ely;
                    s32 rr = (elemh / 2);
                    Color dclr = { nr, ng, nb, initfact };
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
                ((Application*)App)->CallForRenderWithRenderOver([&](render::Renderer::Ref &Drawer) -> bool {});
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