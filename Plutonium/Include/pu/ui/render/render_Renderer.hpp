
/*

    Plutonium library

    @file render_Renderer.hpp
    @brief A Renderer is the object performing basic rendering. (simply, a SDL2 wrapper)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/ui/render/render_SDL2.hpp>
#include <string>
#include <fstream>
#include <vector>

namespace pu::ui::render
{
    struct RendererInitOptions
    {
        u32 SDLFlags;
        u32 RenderFlags;
        u32 Width;
        u32 Height;
        bool InitTTF;
        std::vector<u32> DefaultFontExtraSizes;
        String DefaultFontPath;
        bool InitMixer;
        u32 MixerFlags;
        bool InitIMG;
        u32 IMGFlags;
        bool InitPL;
        bool InitRomFs;

        RendererInitOptions(u32 sdl_flags, u32 render_flags, u32 w = 1280, u32 h = 720) : SDLFlags(sdl_flags), RenderFlags(render_flags), Width(w), Height(h) {}

        // Empty font path = using shared font
        inline RendererInitOptions WithTTF(String default_font_path = "")
        {
            this->InitTTF = true;
            if(default_font_path.HasAny()) this->DefaultFontPath = default_font_path;
            else this->InitPL = true;
            return *this;
        }

        inline RendererInitOptions WithDefaultFontSize(u32 font_size)
        {
            this->DefaultFontExtraSizes.push_back(font_size);
            return *this;
        }

        inline RendererInitOptions WithMixer(u32 flags)
        {
            this->InitMixer = true;
            this->MixerFlags = flags;
            return *this;
        }

        inline RendererInitOptions WithIMG(u32 flags)
        {
            this->InitIMG = true;
            this->IMGFlags = flags;
            return *this;
        }

        inline RendererInitOptions WithRomfs()
        {
            this->InitRomFs = true;
            return *this;
        }
    };

    static constexpr u32 MixerAllFlags = (MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
    static constexpr u32 IMGAllFlags = (IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);
    static constexpr u32 RendererSoftwareFlags = SDL_RENDERER_SOFTWARE;
    static constexpr u32 RendererHardwareFlags = (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    struct TextureRenderOptions
    {
        i32 AlphaMod;
        i32 Width;
        i32 Height;
        float Angle;

        // No extra alpha, no custom size, no rotation
        static const TextureRenderOptions Default;
    };

    inline constexpr const TextureRenderOptions TextureRenderOptions::Default = { .AlphaMod = -1, .Width = -1, .Height = -1, .Angle = -1.0f };

    class Renderer
    {
        public:
            Renderer(RendererInitOptions Options);
            PU_SMART_CTOR(Renderer)

            void Initialize();
            void Finalize();
            bool HasInitialized();
            bool HasRomFs();
            void InitializeRender(Color Color);
            void FinalizeRender();
            void RenderTexture(sdl2::Texture Texture, i32 X, i32 Y, TextureRenderOptions Options = TextureRenderOptions::Default);
            void RenderRectangle(Color Color, i32 X, i32 Y, i32 Width, i32 Height);
            void RenderRectangleFill(Color Color, i32 X, i32 Y, i32 Width, i32 Height);
            void RenderRectangleOutline(Color Color, u32 X, u32 Y, u32 Width, u32 Height, u32 BorderWidth);
            void RenderRoundedRectangle(Color Color, i32 X, i32 Y, i32 Width, i32 Height, i32 Radius);
            void RenderRoundedRectangleFill(Color Color, i32 X, i32 Y, i32 Width, i32 Height, i32 Radius);
            void RenderCircle(Color Color, i32 X, i32 Y, i32 Radius);
            void RenderCircleFill(Color Color, i32 X, i32 Y, i32 Radius);
            void RenderShadowSimple(i32 X, i32 Y, i32 Width, i32 Height, i32 BaseAlpha, u8 MainAlpha = 255);
            void SetBaseRenderPosition(i32 X, i32 Y);
            void UnsetBaseRenderPosition();
            void SetBaseRenderAlpha(u8 Alpha);
            void UnsetBaseRenderAlpha();
        private:
            RendererInitOptions initopts;
            bool okromfs;
            bool okpl;
            bool initialized;
            i32 basex;
            i32 basey;
            int basea;
    };

    // Global rendering

    sdl2::Renderer GetMainRenderer();
    sdl2::Window GetMainWindow();
    sdl2::Surface GetMainSurface();

    std::pair<u32, u32> GetDimensions();

    // Text rendering

    void AddSharedFont(String font_name, u32 font_size, PlSharedFontType type);
    void AddAllSharedFonts(String font_name, u32 font_size);
    void AddFontFile(String font_name, u32 font_size, String path);

    inline void AddDefaultFontFromShared(u32 font_size)
    {
        std::string font_name = "DefaultFont@" + std::to_string(font_size);
        AddAllSharedFonts(font_name, font_size);
    }

    inline void AddDefaultFontFromFile(u32 font_size, String path)
    {
        std::string font_name = "DefaultFont@" + std::to_string(font_size);
        AddFontFile(font_name, font_size, path);
    }

    sdl2::Texture RenderText(String font_name, String Text, Color Color);
    i32 GetTextWidth(String font_name, String Text);
    i32 GetTextHeight(String font_name, String Text);

}
