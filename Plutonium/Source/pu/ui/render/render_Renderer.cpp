#include <pu/ui/render/render_Renderer.hpp>
#include <unordered_map>

namespace pu::ui::render
{
    NativeRenderer purend = NULL;

    extern std::unordered_map<u32, std::pair<std::string, NativeFont>> filefonts;
    extern std::unordered_map<u32, std::pair<SharedFont, NativeFont>> shfonts;

    Renderer::Renderer(u32 SDLFlags, RendererInitOptions Options, u32 NativeRendererFlags, u32 Width, u32 Height)
    {
        this->sdlflags = SDLFlags;
        this->nrendflags = NativeRendererFlags;
        this->initopts = Options;
        this->initialized = false;
        this->ww = Width;
        this->wh = Height;
    }

    void Renderer::Initialize()
    {
        if(!this->initialized)
        {

            this->okromfs = false;
            if(this->initopts.InitRomFs)
            {
                Result rc = romfsInit();
                this->okromfs = R_SUCCEEDED(rc);
            }

            this->okpl = false;
            if(this->initopts.InitPL)
            {
                Result rc = plInitialize();
                this->okpl = R_SUCCEEDED(rc);
            }

            SDL_Init(this->sdlflags);
            this->rendwd = SDL_CreateWindow("Plutonium-SDL2", 0, 0, this->ww, this->wh, 0);
            purend = SDL_CreateRenderer(this->rendwd, -1, this->nrendflags);
            this->rendsf = SDL_GetWindowSurface(this->rendwd);
            SDL_SetRenderDrawBlendMode(purend, SDL_BLENDMODE_BLEND);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

            if(this->initopts.InitIMG) IMG_Init(this->initopts.IMGFlags);

            if(this->initopts.InitTTF) TTF_Init();

            if(this->initopts.InitMixer)
            {
                Mix_Init(this->initopts.MixerFlags);
                Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
            }

            this->initialized = true;
            this->basea = -1;
            this->basex = 0;
            this->basey = 0;
        }
    }

    void Renderer::Finalize()
    {
        for(auto &font: shfonts)
        {
            render::DeleteFont(font.second.second);
        }
        for(auto &font: filefonts)
        {
            render::DeleteFont(font.second.second);
        }

        if(this->initialized)
        {
            if(this->initopts.InitTTF) TTF_Quit();
            if(this->initopts.InitIMG) IMG_Quit();
            if(this->initopts.InitMixer) Mix_CloseAudio();
            if(this->okpl) plExit();
            if(this->okromfs) romfsExit();
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

    void Renderer::InitializeRender(Color Color)
    {
        SDL_SetRenderDrawColor(purend, Color.R, Color.G, Color.B, Color.A);
        SDL_RenderClear(purend);
    }

    void Renderer::FinalizeRender()
    {
        SDL_RenderPresent(purend);
    }

    void Renderer::RenderTexture(NativeTexture Texture, s32 X, s32 Y, NativeTextureRenderOptions Options)
    {
        SDL_Rect pos;
        pos.x = X + this->basex;
        pos.y = Y + this->basey;
        if((Options.Width >= 0) && (Options.Height >= 0))
        {
            pos.w = Options.Width;
            pos.h = Options.Height;
        }
        else SDL_QueryTexture(Texture, NULL, NULL, &pos.w, &pos.h);
        float angle = 0;
        if(Options.Angle >= 0) angle = Options.Angle;
        if(Options.AlphaMod >= 0) SetAlphaValue(Texture, (u8)Options.AlphaMod);
        if(this->basea >= 0) SetAlphaValue(Texture, (u8)this->basea);
        SDL_RenderCopyEx(purend, Texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
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

    void Renderer::RenderRectangleOutline(Color Color, u32 X, u32 Y, u32 Width, u32 Height, u32 BorderWidth)
    {
        this->RenderRectangleFill(Color, X - BorderWidth, Y - BorderWidth, Width + (BorderWidth * 2), Height + (BorderWidth * 2));
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
