#include <pu/render/Renderer.hpp>

namespace pu::render
{
    NativeRenderer purend = NULL;

    void Renderer::Initialize()
    {
        if(!this->initialized)
        {
            Result rc = romfsInit();
            this->okromfs = (rc == 0);
            plInitialize();
            SDL_Init(SDL_INIT_EVERYTHING);
            this->rendwd = SDL_CreateWindow("Plutonium", 0, 0, 1280, 720, SDL_WINDOW_FULLSCREEN);
            purend = SDL_CreateRenderer(this->rendwd, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
            this->rendsf = SDL_GetWindowSurface(this->rendwd);
            SDL_SetRenderDrawBlendMode(purend, SDL_BLENDMODE_BLEND);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);
            TTF_Init();
            this->initialized = true;
        }
    }

    void Renderer::Finalize()
    {
        if(this->initialized)
        {
            plExit();
            if(this->okromfs) romfsExit();
            TTF_Quit();
            IMG_Quit();
            SDL_DestroyRenderer(purend);
            SDL_FreeSurface(this->rendsf);
            SDL_DestroyWindow(this->rendwd);
            SDL_Quit();
            this->initialized = false;
        }
    }

    bool Renderer::HasInitialized()
    {
        return this->initialized;
    }

    bool Renderer::HasRomFs()
    {
        return this->okromfs;
    }

    void Renderer::InitializeRender(draw::Color Color)
    {
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, Color.A);
        SDL_RenderClear(purend);
    }

    void Renderer::FinalizeRender()
    {
        SDL_RenderPresent(purend);
    }

    void Renderer::RenderTexture(NativeTexture Texture, u32 X, u32 Y)
    {
        SDL_Rect pos;
        pos.x = X;
        pos.y = Y;
        SDL_QueryTexture(Texture, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(purend, Texture, NULL, &pos);
    }

    void Renderer::RenderTextureScaled(NativeTexture Texture, u32 X, u32 Y, u32 Width, u32 Height)
    {
        SDL_Rect pos;
        pos.x = X;
        pos.y = Y;
        pos.w = Width;
        pos.h = Height;
        SDL_RenderCopyEx(purend, Texture, NULL, &pos, 0, NULL, SDL_FLIP_NONE);
    }

    void Renderer::RenderRectangle(draw::Color Color, u32 X, u32 Y, u32 Width, u32 Height)
    {
        SDL_Rect rect;
        rect.x = X;
        rect.y = Y;
        rect.w = Width;
        rect.h = Height;
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, Color.A);
        SDL_RenderDrawRect(purend, &rect);
    }

    void Renderer::RenderRectangleFill(draw::Color Color, u32 X, u32 Y, u32 Width, u32 Height)
    {
        SDL_Rect rect;
        rect.x = X;
        rect.y = Y;
        rect.w = Width;
        rect.h = Height;
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, Color.A);
        SDL_RenderFillRect(purend, &rect);
    }

    void Renderer::RenderCircle(draw::Color Color, u32 X, u32 Y, u32 Radius)
    {
        circleRGBA(purend, X, Y, Radius, Color.R, Color.G, Color.B, Color.A);
        aacircleRGBA(purend, X, Y, Radius, Color.R, Color.G, Color.B, Color.A);
    }

    void Renderer::RenderCircleFill(draw::Color Color, u32 X, u32 Y, u32 Radius)
    {
        filledCircleRGBA(purend, X, Y, Radius, Color.R, Color.G, Color.B, Color.A);
        aacircleRGBA(purend, X, Y, Radius, Color.R, Color.G, Color.B, Color.A);
    }

    void Renderer::RenderShadowSimple(u32 X, u32 Y, u32 Width, u32 Height, u32 BaseAlpha)
    {
        bool crop = false;
        u32 shw = Width;
        u32 shx = X;
        u32 shy = Y;
        for(s32 al = BaseAlpha; al > 0; al -= (180 / Height))
        {
            this->RenderRectangleFill({ 130, 130, 130, al }, shx, shy, shw, 1);
            if(crop)
            {
                shw -= 2;
                shx++;
            }
            crop = !crop;
            shy++;
        }
    }

    NativeRenderer GetMainRenderer()
    {
        return purend;
    }
}