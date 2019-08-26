#include <pu/ui/elm/elm_Image.hpp>

namespace pu::ui::elm
{
    Image::Image(s32 X, s32 Y, String Image) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = 0;
        this->h = 0;
        this->ntex = NULL;
        this->SetImage(Image);
    }

    Image::~Image()
    {
        if(this->ntex != NULL)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = NULL;
        }
    }

    s32 Image::GetX()
    {
        return this->x;
    }

    void Image::SetX(s32 X)
    {
        this->x = X;
    }

    s32 Image::GetY()
    {
        return this->y;
    }

    void Image::SetY(s32 Y)
    {
        this->y = Y;
    }

    s32 Image::GetWidth()
    {
        return this->w;
    }

    void Image::SetWidth(s32 Width)
    {
        this->w = Width;
    }

    s32 Image::GetHeight()
    {
        return this->h;
    }

    void Image::SetHeight(s32 Height)
    {
        this->h = Height;
    }

    String Image::GetImage()
    {
        return this->img;
    }

    void Image::SetImage(String Image)
    {
        if(this->ntex != NULL) render::DeleteTexture(this->ntex);
        this->ntex = NULL;
        std::ifstream ifs(Image.AsUTF8());
        if(ifs.good())
        {
            ifs.close();
            this->img = Image;
            this->ntex = render::LoadImage(Image.AsUTF8());
            this->w = render::GetTextureWidth(this->ntex);
            this->h = render::GetTextureHeight(this->ntex);
        }
        ifs.close();
    }

    bool Image::IsImageValid()
    {
        return ((ntex != NULL) && this->img.HasAny());
    }

    void Image::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
    {
        s32 rdx = X;
        s32 rdy = Y;
        Drawer->RenderTextureScaled(this->ntex, rdx, rdy, w, h);
    }

    void Image::OnInput(u64 Down, u64 Up, u64 Held, bool Touch)
    {
    }
}