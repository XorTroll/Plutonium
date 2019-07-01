#include <pu/ui/elm/elm_Image.hpp>

namespace pu::ui::elm
{
    Image::Image(s32 X, s32 Y, std::string Image) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->w = 0;
        this->h = 0;
        std::ifstream ifs(Image);
        if(ifs.good())
        {
            this->img = Image;
            this->ntex = render::LoadImage(Image);
            this->w = render::GetTextureWidth(this->ntex);
            this->h = render::GetTextureHeight(this->ntex);
        }
        ifs.close();
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

    std::string Image::GetImage()
    {
        return this->img;
    }

    void Image::SetImage(std::string Image)
    {
        std::ifstream ifs(Image);
        if(ifs.good())
        {
            this->img = Image;
            render::DeleteTexture(this->ntex);
            this->ntex = render::LoadImage(Image);
        }
        ifs.close();
    }

    bool Image::IsImageValid()
    {
        std::ifstream ifs(this->img);
        bool ok = ifs.good();
        ifs.close();
        return ok;
    }

    void Image::OnRender(render::Renderer *Drawer)
    {
        s32 rdx = this->GetProcessedX();
        s32 rdy = this->GetProcessedY();
        Drawer->RenderTextureScaled(this->ntex, rdx, rdy, w, h);
    }

    void Image::OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus)
    {
    }
}