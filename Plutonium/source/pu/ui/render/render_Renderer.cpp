#include <pu/ui/render/render_Renderer.hpp>
#include <pu/ttf/ttf_Font.hpp>
#include <unordered_map>

namespace pu::ui::render
{
    // Global rendering vars
    static sdl2::Renderer g_renderer = nullptr;
    static sdl2::Window g_window = nullptr;
    static sdl2::Surface g_windowsrf = nullptr;

    // Global font object
    static std::vector<std::pair<String, std::shared_ptr<ttf::Font>>> g_font_list;

    Renderer::Renderer(RendererInitOptions Options) : initopts(Options), initialized(false) {}

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
                Result rc = plInitialize(PlServiceType_User);
                this->okpl = R_SUCCEEDED(rc);
            }

            SDL_Init(this->initopts.SDLFlags);
            g_window = SDL_CreateWindow("Plutonium-SDL2", 0, 0, this->initopts.Width, this->initopts.Height, 0);
            g_renderer = SDL_CreateRenderer(g_window, -1, this->initopts.RenderFlags);
            g_windowsrf = SDL_GetWindowSurface(g_window);
            SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

            if(this->initopts.InitIMG) IMG_Init(this->initopts.IMGFlags);

            if(this->initopts.InitTTF)
            {
                TTF_Init();
                if(this->initopts.DefaultFontPath.HasAny())
                {
                    for(auto size: DefaultFontSizes)
                    {
                        AddDefaultFontFromFile(size, this->initopts.DefaultFontPath);
                    }
                    for(auto size: this->initopts.DefaultFontExtraSizes)
                    {
                        AddDefaultFontFromFile(size, this->initopts.DefaultFontPath);
                    }
                }
                else
                {
                    for(auto size: DefaultFontSizes)
                    {
                        AddDefaultFontFromShared(size);
                    }
                    for(auto size: this->initopts.DefaultFontExtraSizes)
                    {
                        AddDefaultFontFromShared(size);
                    }
                }
            }

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
        if(this->initialized)
        {
            // Close all the fonts before closing TTF
            g_font_list.clear();
            if(this->initopts.InitTTF) TTF_Quit();
            if(this->initopts.InitIMG) IMG_Quit();
            if(this->initopts.InitMixer) Mix_CloseAudio();
            if(this->okpl) plExit();
            if(this->okromfs) romfsExit();
            SDL_DestroyRenderer(g_renderer);
            SDL_FreeSurface(g_windowsrf);
            SDL_DestroyWindow(g_window);
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
        SDL_SetRenderDrawColor(g_renderer, Color.R, Color.G, Color.B, Color.A);
        SDL_RenderClear(g_renderer);
    }

    void Renderer::FinalizeRender()
    {
        SDL_RenderPresent(g_renderer);
    }

    void Renderer::RenderTexture(sdl2::Texture Texture, i32 X, i32 Y, TextureRenderOptions Options)
    {
        SDL_Rect pos;
        pos.x = X + this->basex;
        pos.y = Y + this->basey;
        if((Options.Width >= 0) && (Options.Height >= 0))
        {
            pos.w = Options.Width;
            pos.h = Options.Height;
        }
        else SDL_QueryTexture(Texture, nullptr, nullptr, &pos.w, &pos.h);
        float angle = 0;
        if(Options.Angle >= 0) angle = Options.Angle;
        if(Options.AlphaMod >= 0) SetAlphaValue(Texture, (u8)Options.AlphaMod);
        if(this->basea >= 0) SetAlphaValue(Texture, (u8)this->basea);
        SDL_RenderCopyEx(g_renderer, Texture, nullptr, &pos, angle, nullptr, SDL_FLIP_NONE);
    }

    void Renderer::RenderRectangle(Color Color, i32 X, i32 Y, i32 Width, i32 Height)
    {
        SDL_Rect rect;
        rect.x = X + this->basex;
        rect.y = Y + this->basey;
        rect.w = Width;
        rect.h = Height;
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        SDL_SetRenderDrawColor(g_renderer, Color.R, Color.G, Color.B, alpha);
        SDL_RenderDrawRect(g_renderer, &rect);
    }

    void Renderer::RenderRectangleFill(Color Color, i32 X, i32 Y, i32 Width, i32 Height)
    {
        SDL_Rect rect;
        rect.x = X + this->basex;
        rect.y = Y + this->basey;
        rect.w = Width;
        rect.h = Height;
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        SDL_SetRenderDrawColor(g_renderer, Color.R, Color.G, Color.B, alpha);
        SDL_RenderFillRect(g_renderer, &rect);
    }

    void Renderer::RenderRectangleOutline(Color Color, u32 X, u32 Y, u32 Width, u32 Height, u32 BorderWidth)
    {
        this->RenderRectangleFill(Color, X - BorderWidth, Y - BorderWidth, Width + (BorderWidth * 2), Height + (BorderWidth * 2));
    }
	
    void Renderer::RenderRoundedRectangle(Color Color, i32 X, i32 Y, i32 Width, i32 Height, i32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        roundedRectangleRGBA(g_renderer, X + this->basex, Y + this->basey, X + this->basex + Width, Y + this->basey + Height, Radius, Color.R, Color.G, Color.B, alpha);
        SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
    }

    void Renderer::RenderRoundedRectangleFill(Color Color, i32 X, i32 Y, i32 Width, i32 Height, i32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        roundedBoxRGBA(g_renderer, X + this->basex, Y + this->basey, X + this->basex + Width, Y + this->basey + Height, Radius, Color.R, Color.G, Color.B, alpha);
        SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
    }

    void Renderer::RenderCircle(Color Color, i32 X, i32 Y, i32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        circleRGBA(g_renderer, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
        aacircleRGBA(g_renderer, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
    }

    void Renderer::RenderCircleFill(Color Color, i32 X, i32 Y, i32 Radius)
    {
        u8 alpha = Color.A;
        if(this->basea >= 0) alpha = (u8)this->basea;
        filledCircleRGBA(g_renderer, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
        aacircleRGBA(g_renderer, X + this->basex, Y + this->basey, Radius - 1, Color.R, Color.G, Color.B, alpha);
    }

    void Renderer::RenderShadowSimple(i32 X, i32 Y, i32 Width, i32 Height, i32 BaseAlpha, u8 MainAlpha)
    {
        bool crop = false;
        i32 shw = Width;
        i32 shx = X;
        i32 shy = Y;
        for(i32 al = BaseAlpha; al > 0; al -= (180 / Height))
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

    void Renderer::SetBaseRenderPosition(i32 X, i32 Y)
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

    sdl2::Renderer GetMainRenderer()
    {
        return g_renderer;
    }

    sdl2::Window GetMainWindow()
    {
        return g_window;
    }

    sdl2::Surface GetMainSurface()
    {
        return g_windowsrf;
    }

    std::pair<u32, u32> GetDimensions()
    {
        i32 w = 0;
        i32 h = 0;
        SDL_GetWindowSize(g_window, &w, &h);
        return std::make_pair(static_cast<u32>(w), static_cast<u32>(h));
    }

    static inline bool AddSharedFontImpl(std::shared_ptr<ttf::Font> &font, PlSharedFontType type)
    {
        // Let's assume pl services are initialized, and return if anything unexpected happens
        PlFontData data = {};
        auto rc = plGetSharedFontByType(&data, type);
        if(R_FAILED(rc)) return false;
        if(!ttf::Font::IsValidFontFaceIndex(font->LoadFromMemory(data.address, data.size, pu::ttf::EmptyFontFaceDisposingFunction))) return false;
        return true;
    }

    void AddSharedFont(String font_name, u32 font_size, PlSharedFontType type)
    {
        for(auto &[name, font]: g_font_list)
        {
            if(name == font_name)
            {
                return;
            }
        }
        
        auto font = std::make_shared<ttf::Font>(font_size);
        if(AddSharedFontImpl(font, type)) g_font_list.push_back(std::make_pair(font_name, std::move(font)));
    }

    void AddAllSharedFonts(String font_name, u32 font_size)
    {
        for(auto &[name, font]: g_font_list)
        {
            if(name == font_name)
            {
                return;
            }
        }
        
        auto font = std::make_shared<ttf::Font>(font_size);
        if(!AddSharedFontImpl(font, PlSharedFontType_Standard)) return;
        if(!AddSharedFontImpl(font, PlSharedFontType_NintendoExt)) return;
        if(!AddSharedFontImpl(font, PlSharedFontType_ChineseSimplified)) return;
        if(!AddSharedFontImpl(font, PlSharedFontType_ExtChineseSimplified)) return;
        if(!AddSharedFontImpl(font, PlSharedFontType_ChineseTraditional)) return;
        if(!AddSharedFontImpl(font, PlSharedFontType_KO)) return;
        g_font_list.push_back(std::make_pair(font_name, std::move(font)));
    }

    void AddFontFile(String font_name, u32 font_size, String path)
    {
        for(auto &[name, font]: g_font_list)
        {
            if(name == font_name)
            {
                return;
            }
        }
        auto font = std::make_shared<ttf::Font>(font_size);
        if(!ttf::Font::IsValidFontFaceIndex(font->LoadFromFile(path))) return;
        g_font_list.push_back(std::make_pair(font_name, std::move(font)));
    }

    sdl2::Texture RenderText(String font_name, String Text, Color Color)
    {
        for(auto &[name, font]: g_font_list)
        {
            if(name == font_name)
            {
                return font->RenderText(Text, Color);
            }
        }
        return nullptr;
    }

    i32 GetTextWidth(String font_name, String Text)
    {
        for(auto &[name, font]: g_font_list)
        {
            if(name == font_name)
            {
                auto [w, _h] = font->GetTextDimensions(Text);
                return static_cast<i32>(w);
            }
        }
        return 0;
    }

    i32 GetTextHeight(String font_name, String Text)
    {
        for(auto &[name, font]: g_font_list)
        {
            if(name == font_name)
            {
                auto [_w, h] = font->GetTextDimensions(Text);
                return static_cast<i32>(h);
            }
        }
        return 0;
    }

}
