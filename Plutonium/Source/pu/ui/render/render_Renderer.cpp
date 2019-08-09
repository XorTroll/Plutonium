#include <pu/ui/render/render_Renderer.hpp>
#include <unordered_map>

namespace pu::ui::render
{
    NativeRenderer purend = NULL;

    extern std::unordered_map<u32, std::pair<std::string, NativeFont>> filefonts;
    extern std::unordered_map<u32, std::pair<SharedFont, NativeFont>> shfonts;

    void Renderer::Initialize(u32 SdlFlags, bool RenderAccel)
    {
        if(!this->initialized)
        {
            Result rc = romfsInit();
            this->okromfs = (rc == 0);
            plInitialize();
            SDL_Init(SdlFlags);
            this->rendwd = SDL_CreateWindow("Plutonium", 0, 0, 1280, 720, 0);
            u32 flags = SDL_RENDERER_SOFTWARE;
            if(RenderAccel) flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            purend = SDL_CreateRenderer(this->rendwd, -1, flags);
            this->rendsf = SDL_GetWindowSurface(this->rendwd);
            SDL_SetRenderDrawBlendMode(purend, SDL_BLENDMODE_BLEND);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);
            TTF_Init();
            Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
            this->initialized = true;
            this->basea = -1;
            this->basex = 0;
            this->basey = 0;
        }
    }

    void Renderer::Finalize()
    {
        for(auto font: shfonts)
        {
            render::DeleteFont(font.second.second);
        }
        for(auto font: filefonts)
        {
            render::DeleteFont(font.second.second);
        }
        if(this->initialized)
        {
            TTF_Quit();
            IMG_Quit();
            SDL_DestroyRenderer(purend);
            SDL_FreeSurface(this->rendsf);
            SDL_DestroyWindow(this->rendwd);
            SDL_Quit();
            plExit();
            if(this->okromfs) romfsExit();
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

    void Renderer::InitializeRender(Color Color)
    {
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, Color.A);
        SDL_RenderClear(purend);
    }

    void Renderer::FinalizeRender()
    {
        SDL_RenderPresent(purend);
    }

    void Renderer::RenderTexture(NativeTexture Texture, s32 X, s32 Y, int AlphaMod)
    {
        SDL_Rect pos;
        pos.x = X + this->basex;
        pos.y = Y + this->basey;
        if(AlphaMod >= 0) SetAlphaValue(Texture, (u8)AlphaMod);
        if(this->basea >= 0) SetAlphaValue(Texture, (u8)this->basea);
        SDL_QueryTexture(Texture, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(purend, Texture, NULL, &pos);
    }

    void Renderer::RenderTextureScaled(NativeTexture Texture, s32 X, s32 Y, s32 Width, s32 Height, int AlphaMod)
    {
        SDL_Rect pos;
        pos.x = X + this->basex;
        pos.y = Y + this->basey;
        pos.w = Width;
        pos.h = Height;
        if(AlphaMod >= 0) SetAlphaValue(Texture, (u8)AlphaMod);
        if(this->basea >= 0) SetAlphaValue(Texture, (u8)this->basea);
        SDL_RenderCopyEx(purend, Texture, NULL, &pos, 0, NULL, SDL_FLIP_NONE);
    }

    void Renderer::RenderRectangle(Color Color, s32 X, s32 Y, s32 Width, s32 Height)
    {
        SDL_Rect rect;
        rect.x = X + this->basex;
        rect.y = Y + this->basey;
        rect.w = Width;
        rect.h = Height;
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, alpha);
        SDL_RenderDrawRect(purend, &rect);
    }

    void Renderer::RenderRectangleFill(Color Color, s32 X, s32 Y, s32 Width, s32 Height)
    {
        SDL_Rect rect;
        rect.x = X + this->basex;
        rect.y = Y + this->basey;
        rect.w = Width;
        rect.h = Height;
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, alpha);
        SDL_RenderFillRect(purend, &rect);
    }
	
    void Renderer::RenderRoundedRectangle(Color Color, s32 X, s32 Y, s32 Width, s32 Height, s32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        roundedRectangleRGBA(purend, X + this->basex, Y + this->basey, X + this->basex + Width, Y + this->basey + Height, Radius, Color.R, Color.G, Color.B, alpha);
        SDL_SetRenderDrawBlendMode(purend, SDL_BLENDMODE_BLEND);
    }

    void Renderer::RenderRoundedRectangleFill(Color Color, s32 X, s32 Y, s32 Width, s32 Height, s32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        roundedBoxRGBA(purend, X + this->basex, Y + this->basey, X + this->basex + Width, Y + this->basey + Height, Radius, Color.R, Color.G, Color.B, alpha);
        SDL_SetRenderDrawBlendMode(purend, SDL_BLENDMODE_BLEND);
    }

    void Renderer::RenderCircle(Color Color, s32 X, s32 Y, s32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        circleRGBA(purend, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
        aacircleRGBA(purend, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
    }

    void Renderer::RenderCircleFill(Color Color, s32 X, s32 Y, s32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        filledCircleRGBA(purend, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
        aacircleRGBA(purend, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
    }

    void Renderer::RenderShadowSimple(s32 X, s32 Y, s32 Width, s32 Height, s32 BaseAlpha, u8 MainAlpha)
    {
        bool crop = false;
        s32 shw = Width;
        s32 shx = X;
        s32 shy = Y;
        for(s32 al = BaseAlpha; al > 0; al -= (180 / Height))
        {
            this->RenderRectangleFill({ 130, 130, 130, (al * (MainAlpha / 255)) }, shx + this->basex, shy + this->basey, shw, 1);
            if(crop)
            {
                shw -= 2;
                shx++;
            }
            crop = !crop;
            shy++;
        }
    }

    void Renderer::SetBaseRenderPosition(s32 X, s32 Y)
    {
        this->basex = X;
        this->basey = Y;
    }

    void Renderer::UnsetBaseRenderPosition()
    {
        this->SetBaseRenderPosition(0, 0);
    }

    void Renderer::SetBaseRenderAlpha(u8 Alpha)
    {
        this->basea = (int)Alpha;
    }

    void Renderer::UnsetBaseRenderAlpha()
    {
        this->basea = -1;
    }

    NativeRenderer GetMainRenderer()
    {
        return purend;
    }
}
