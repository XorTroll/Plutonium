#include <pu/ui/ui_Overlay.hpp>
#include <pu/ui/ui_Application.hpp>
#include <cmath>

namespace pu::ui
{
    Overlay::Overlay(i32 X, i32 Y, i32 Width, i32 Height, Color Background, bool Rounded) : Container(X, Y, Width, Height)
    {
        this->bg = Background;
        this->round = Rounded;
        this->rad = 25;
        this->fadea = 0;
        this->end = false;
    }

    void Overlay::SetRadius(i32 Radius)
    {
        this->rad = Radius;
    }

    i32 Overlay::GetRadius()
    {
        return this->rad;
    }

    void Overlay::OnPreRender(render::Renderer::Ref &Drawer)
    {
    }

    void Overlay::OnPostRender(render::Renderer::Ref &Drawer)
    {
    }

    bool Overlay::Render(render::Renderer::Ref &Drawer)
    {
        this->OnPreRender(Drawer);
        Drawer->SetBaseRenderAlpha(this->fadea);
        if(this->round) Drawer->RenderRoundedRectangleFill(this->bg, this->x, this->y, this->w, this->h, this->rad);
        else Drawer->RenderRectangleFill(this->bg, this->x, this->y, this->w, this->h);
        this->PreRender();
        for(auto &elm: this->elms)
        {
            if(elm->IsVisible()) elm->OnRender(Drawer, elm->GetProcessedX(), elm->GetProcessedY());
        }
        Drawer->UnsetBaseRenderAlpha();
        if(this->end)
        {
            if(this->fadea > 0) this->fadea -= 25;
            else this->fadea = 0;
        }
        else
        {
            if(this->fadea < 200) this->fadea += 25;
            if(this->fadea > 200) this->fadea = 200;
        }
        this->OnPostRender(Drawer);
        bool fin = (this->end && (this->fadea == 0));
        if(fin)
        {
            this->end = false;
        }
        return !fin;
    }

    void Overlay::NotifyEnding(bool End)
    {
        this->end = End;
    }
}