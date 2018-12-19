#include <pu/Dialog.hpp>

namespace pu
{
    Dialog::Dialog(std::string Title, std::string Content, draw::Font Font)
    {
        this->title = Title;
        this->cnt = Content;
        this->osel = 0;
        this->prevosel = 0;
        this->selfact = 255;
        this->pselfact = 0;
        this->fnt = Font;
        this->hicon = false;
        this->cancel = false;
    }

    void Dialog::AddOption(std::string Name)
    {
        this->opts.push_back(Name);
    }

    void Dialog::SetIcon(element::Image *Icon)
    {
        this->hicon = true;
        this->icon = Icon;
    }

    bool Dialog::Hasicon()
    {
        return this->hicon;
    }

    void Dialog::Show(render::Renderer *Drawer)
    {
        if(this->opts.empty()) return;
        u32 dx = 0;
        u32 dy = 0;
        u32 elemw = (1280 / this->opts.size());
        u32 elemh = 60;
        u32 nr = 180;
        u32 ng = 180;
        u32 nb = 200;
        bool end = false;
        s32 initfact = 0;
        while(true)
        {
            hidScanInput();
            u64 k = hidKeysDown(CONTROLLER_P1_AUTO);
            if(k & KEY_LEFT)
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
            else if(k & KEY_RIGHT)
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
            Drawer->DrawRectangleFill({ 225, 225, 225, initfact }, dx, dy, 1280, 720);
            Drawer->DrawText(this->title, this->fnt, 35, (dx + 45), (dy + 45), { 10, 10, 10, initfact });
            Drawer->DrawText(this->cnt, this->fnt, 25, (dx + 45), (dy + 100), { 10, 10, 10, initfact });
            if(this->hicon) this->icon->OnRender(Drawer);
            for(u32 i = 0; i < this->opts.size(); i++)
            {
                u32 tw = Drawer->GetTextWidth(this->fnt, opts[i], 20);
                u32 th = Drawer->GetTextHeight(this->fnt, opts[i], 20);
                u32 tx = dx + ((elemw - tw) / 2) + (elemw * i);
                u32 ty = dy + (720 - elemh) + ((elemh - th) / 2);
                u32 rx = dx + (elemw * i);
                u32 ry = dy + (720 - elemh);
                if(this->osel == i)
                {
                    if(this->selfact < 255)
                    {
                        Drawer->DrawRectangleFill(draw::Color(nr, ng, nb, this->selfact), rx, ry, elemw, elemh);
                        this->selfact += 48;
                    }
                    else Drawer->DrawRectangleFill({ nr, ng, nb, initfact }, rx, ry, elemw, elemh);
                }
                else if(this->prevosel == i)
                {
                    if(this->pselfact > 0)
                    {
                        Drawer->DrawRectangleFill(draw::Color(nr, ng, nb, this->pselfact), rx, ry, elemw, elemh);
                        this->pselfact -= 48;
                    }
                }
                Drawer->DrawText(opts[i], this->fnt, 20, tx, ty, { 10, 10, 10, initfact });
            }
            Drawer->Render();
            if(end)
            {
                if(initfact == 0) break;
                if(initfact > 0) initfact -= 25;
                if(initfact < 0) initfact = 0;
            }
            else
            {
                if(initfact < 255) initfact += 25;
                if(initfact > 255) initfact = 255;
            }
        }
    }

    bool Dialog::UserCancelled()
    {
        return this->cancel;
    }

    u32 Dialog::GetSelectedIndex()
    {
        return this->osel;
    }
}