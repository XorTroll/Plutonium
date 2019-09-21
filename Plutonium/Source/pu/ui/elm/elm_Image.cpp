#include <pu/ui/elm/elm_Image.hpp>

namespace pu::ui::elm
{
    Image::Image(s32 X, s32 Y, String Image) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->ntex = NULL;
        this->rendopts = render::NativeTextureRenderOptions::Default;
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
        return this->rendopts.Width;
    }

    void Image::SetWidth(s32 Width)
    {
        this->rendopts.Width = Width;
    }

    s32 Image::GetHeight()
    {
        return this->rendopts.Height;
    }

    void Image::SetHeight(s32 Height)
    {
        this->rendopts.Height = Height;
    }

    float Image::GetRotation()
    {
        return this->rendopts.Angle;
    }

    void Image::SetRotation(float Angle)
    {
        this->rendopts.Angle = Angle;
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
        bool ok = ifs.good();
        ifs.close();
        if(ok)    
        {
            this->img = Image;
            this->ntex = render::LoadImage(Image.AsUTF8());
            this->rendopts.Width = render::GetTextureWidth(this->ntex);
            this->rendopts.Height = render::GetTextureHeight(this->ntex);
        }
    }

    bool Image::IsImageValid()
    {
        return ((ntex != NULL) && this->img.HasAny());
    }

    void Image::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
    {
        Drawer->RenderTexture(this->ntex, X, Y, this->rendopts);
    }

    void Image::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
    }
}