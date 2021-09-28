#include <pu/ui/ui_Dialog.hpp>
#include <pu/ui/ui_Application.hpp>
#include <cmath>

namespace pu::ui
{
    Dialog::Dialog(String Title, String Content)
    {
        this->tfont_name = "DefaultFont@30";
        this->cfont_name = "DefaultFont@20";
        this->ofont_name = "DefaultFont@18";
        this->stitle = Title;
        this->scnt = Content;
        this->title = render::RenderText(this->tfont_name, Title, { 10, 10, 10, 255 });
        this->cnt = render::RenderText(this->cfont_name, Content, { 20, 20, 20, 255 });
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
        if(this->title != nullptr)
        {
            render::DeleteTexture(this->title);
            this->title = nullptr;
        }
        if(this->cnt != nullptr)
        {
            render::DeleteTexture(this->cnt);
            this->cnt = nullptr;
        }
        if(this->hicon && (this->icon != nullptr))
        {
            render::DeleteTexture(this->icon);
            this->icon = nullptr;
            this->hicon = false;
        }
        for(auto &opt: this->opts) render::DeleteTexture(opt);
    }

    void Dialog::AddOption(String Name)
    {
        this->opts.push_back(render::RenderText(this->ofont_name, Name, { 10, 10, 10, 255 }));
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

    i32 Dialog::Show(render::Renderer::Ref &Drawer, void *App)
    {
        if(this->hcancel) this->AddOption(this->scancel);
        if(this->opts.empty()) return 0;
        i32 dw = (20 * (this->opts.size() - 1)) + 250;
        for(i32 i = 0; i < this->opts.size(); i++)
        {
            i32 tw = render::GetTextWidth(this->ofont_name, this->sopts[i]);
            dw += tw + 20;
        }
        if(dw > 1280) dw = 1280;
        i32 icm = 30;
        i32 elemh = 60;
        i32 tdw = render::GetTextWidth(this->cfont_name, this->scnt) + 90;
        if(tdw > dw) dw = tdw;
        tdw = render::GetTextWidth(this->tfont_name, this->stitle) + 90;
        if(tdw > dw) dw = tdw;
        i32 ely = render::GetTextHeight(this->tfont_name, this->stitle) + render::GetTextHeight(this->cfont_name, this->scnt) + 140;
        if(this->hicon)
        {
            i32 tely = render::GetTextureHeight(this->icon) + icm + 25;
            if(tely > ely) ely = tely;
            tdw = render::GetTextWidth(this->cfont_name, this->scnt) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
            tdw = render::GetTextWidth(this->tfont_name, this->stitle) + 90 + render::GetTextureWidth(this->icon) + 20;
            if(tdw > dw) dw = tdw;
        }
        if(dw > 1280) dw = 1280;
        i32 dh = ely + elemh + 30;
        if(dh > 720) dh = 720;
        i32 dx = (1280 - dw) / 2;
        i32 dy = (720 - dh) / 2;
        ely += dy;
        i32 elemw = ((dw - (20 * (this->opts.size() + 1))) / this->opts.size());
        i32 elx = dx + ((dw - ((elemw * this->opts.size()) + (20 * (this->opts.size() - 1)))) / 2);
        i32 r = 35;
        i32 nr = 180;
        i32 ng = 180;
        i32 nb = 200;
        bool end = false;
        i32 initfact = 0;
        auto app_ref = reinterpret_cast<Application*>(App);
        while(true)
        {
            bool ok = app_ref->CallForRenderWithRenderOver([&](render::Renderer::Ref &Drawer) -> bool
            {
                const auto k = app_ref->GetButtonsDown();
                const auto h = app_ref->GetButtonsHeld();
                const auto tch_state = app_ref->GetTouchState();
                const auto tch_x = tch_state.touches[0].x;
                const auto tch_y = tch_state.touches[0].y;
                if(k & HidNpadButton_AnyLeft)
                {
                    if(this->osel > 0)
                    {
                        this->prevosel = this->osel;
                        this->osel--;
                        for(i32 i = 0; i < this->opts.size(); i++)
                        {
                            if(i == this->osel) this->selfact = 0;
                            else if(i == this->prevosel) this->pselfact = 255;
                        }
                    }
                }
                else if(k & HidNpadButton_AnyRight)
                {
                    if(this->osel < (this->opts.size() - 1))
                    {
                        this->prevosel = this->osel;
                        this->osel++;
                        for(i32 i = 0; i < this->opts.size(); i++)
                        {
                            if(i == this->osel) this->selfact = 0;
                            else if(i == this->prevosel) this->pselfact = 255;
                        }
                    }
                }
                if(k & HidNpadButton_A)
                {
                    this->cancel = false;
                    end = true;
                }
                if(k & HidNpadButton_B)
                {
                    this->cancel = true;
                    end = true;
                }
                if(tch_state.count > 0)
                {
                    for(i32 i = 0; i < this->opts.size(); i++)
                    {
                        String txt = this->sopts[i];
                        i32 rx = elx + ((elemw + 20) * i);
                        i32 ry = ely;
                        if(((rx + elemw) > tch_x) && (tch_x > rx) && ((ry + elemh) > tch_y) && (tch_y > ry))
                        {
                            this->osel = i;
                            this->cancel = false;
                            end = true;
                        }
                    }
                }
                i32 bw = dw;
                i32 bh = dh;
                i32 fw = bw - (r * 2);
                i32 fh = bh - (r * 2);
                Color clr = { 225, 225, 225, initfact };
                i32 aclr = initfact;
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
                    i32 icw = render::GetTextureWidth(this->icon);
                    i32 icx = dx + (dw - (icw + icm));
                    i32 icy = dy + icm;
                    Drawer->RenderTexture(this->icon, icx, icy, { initfact, -1, -1, -1.0f });
                }
                for(i32 i = 0; i < this->opts.size(); i++)
                {
                    String txt = this->sopts[i];
                    i32 tw = render::GetTextWidth(this->ofont_name, txt);
                    i32 th = render::GetTextHeight(this->ofont_name, txt);
                    i32 tx = elx + ((elemw - tw) / 2) + ((elemw + 20) * i);
                    i32 ty = ely + ((elemh - th) / 2);
                    i32 rx = elx + ((elemw + 20) * i);
                    i32 ry = ely;
                    i32 rr = (elemh / 2);
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
                app_ref->CallForRenderWithRenderOver([&](render::Renderer::Ref &Drawer) -> bool {});
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