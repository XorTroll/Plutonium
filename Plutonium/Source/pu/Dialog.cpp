#include <pu/Dialog.hpp>

namespace pu
{
    Dialog::Dialog(std::string Title, std::string Content)
    {
        this->tfont = render::LoadSharedFont(render::SharedFont::Standard, 35);
        this->cfont = render::LoadSharedFont(render::SharedFont::Standard, 25);
        this->ofont = render::LoadSharedFont(render::SharedFont::Standard, 20);
        this->title = render::RenderText(this->tfont, Title, { 10, 10, 10, 255 });
        this->cnt = render::RenderText(this->cfont, Content, { 20, 20, 20, 255 });
        this->osel = 0;
        this->prevosel = 0;
        this->selfact = 255;
        this->pselfact = 0;
        this->hicon = false;
        this->cancel = false;
        this->ix = 0;
        this->iy = 0;
    }

    Dialog::~Dialog()
    {
        render::DeleteFont(this->tfont);
        render::DeleteFont(this->cfont);
        render::DeleteFont(this->ofont);
        render::DeleteTexture(this->title);
        render::DeleteTexture(this->cnt);
        if(this->hicon) render::DeleteTexture(this->icon);
        if(!this->opts.empty()) for(u32 i = 0; i < this->opts.size(); i++) delete this->opts[i];
        this->opts.clear();
        this->sopts.clear();
    }

    void Dialog::AddOption(std::string Name)
    {
        this->opts.push_back(render::RenderText(this->ofont, Name, { 10, 10, 10, 255 }));
        this->sopts.push_back(Name);
    }

    void Dialog::SetIcon(std::string Icon, u32 IconX, u32 IconY)
    {
        if(this->hicon) render::DeleteTexture(this->icon);
        this->icon = render::LoadImage(Icon);
        this->ix = IconX;
        this->iy = IconY;
        this->hicon = true;
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
        u32 elemh = 80;
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
            Drawer->RenderRectangleFill({ 225, 225, 225, initfact }, dx, dy, 1280, 720);
            Drawer->RenderTexture(this->title, (dx + 45), (dy + 45));
            Drawer->RenderTexture(this->cnt, (dx + 45), (dy + 100));
            if(this->hicon) Drawer->RenderTexture(this->icon, this->ix, this->iy);
            for(u32 i = 0; i < this->opts.size(); i++)
            {
                u32 tw = render::GetTextWidth(this->ofont, sopts[i]);
                u32 th = render::GetTextHeight(this->ofont, sopts[i]);
                u32 tx = dx + ((elemw - tw) / 2) + (elemw * i);
                u32 ty = dy + (720 - elemh) + ((elemh - th) / 2);
                u32 rx = dx + (elemw * i);
                u32 ry = dy + (720 - elemh);
                if(this->osel == i)
                {
                    if(this->selfact < 255)
                    {
                        Drawer->RenderRectangleFill(draw::Color(nr, ng, nb, this->selfact), rx, ry, elemw, elemh);
                        this->selfact += 48;
                    }
                    else Drawer->RenderRectangleFill({ nr, ng, nb, initfact }, rx, ry, elemw, elemh);
                }
                else if(this->prevosel == i)
                {
                    if(this->pselfact > 0)
                    {
                        Drawer->RenderRectangleFill(draw::Color(nr, ng, nb, this->pselfact), rx, ry, elemw, elemh);
                        this->pselfact -= 48;
                    }
                }
                Drawer->RenderTexture(this->opts[i], tx, ty);
            }
            Drawer->FinalizeRender();
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