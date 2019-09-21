
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

namespace pu::ui::render
{
    struct RendererInitOptions
    {
        bool InitTTF;
        bool InitMixer;
        u32 MixerFlags;
        bool InitIMG;
        u32 IMGFlags;
        bool InitPL;
        bool InitRomFs;

        // Only plain SDL2
        static const RendererInitOptions RendererSDLOnly;

        // SDL2, PL, RomFs, TTF, Mixer and IMG
        static const RendererInitOptions RendererEverything;

        // SDL2, PL and RomFs
        static const RendererInitOptions RendererSimple;

        // Everything except Mixer (SDL2, PL, RomFs, TTF, Mixer)
        static const RendererInitOptions RendererNoSound;
    };

    static constexpr u32 MixerAllFlags = (MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
    static constexpr u32 IMGAllFlags = (IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);
    static constexpr u32 RendererSoftwareFlags = SDL_RENDERER_SOFTWARE;
    static constexpr u32 RendererHardwareFlags = (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    inline constexpr const RendererInitOptions RendererInitOptions::RendererSDLOnly = { false, false, 0, false, 0, false, false };
    inline constexpr const RendererInitOptions RendererInitOptions::RendererEverything = { true, true, MixerAllFlags, true, IMGAllFlags, true, true };
    inline constexpr const RendererInitOptions RendererInitOptions::RendererSimple = { false, false, 0, false, 0, true, true };
    inline constexpr const RendererInitOptions RendererInitOptions::RendererNoSound = { true, false, 0, true, IMGAllFlags, true, true };

    struct NativeTextureRenderOptions
    {
        int AlphaMod;
        s32 Width;
        s32 Height;
        float Angle;

        // No extra alpha, no custom size, no rotation
        static const NativeTextureRenderOptions Default;
    };

    inline constexpr const NativeTextureRenderOptions NativeTextureRenderOptions::Default = { .AlphaMod = -1, .Width = -1, .Height = -1, .Angle = -1.0f };

    class Renderer
    {
        public:
            Renderer(u32 SDLFlags, RendererInitOptions Options, u32 NativeRendererFlags, u32 Width = 1280, u32 Height = 720);
            PU_SMART_CTOR(Renderer)

            void Initialize();
            void Finalize();
            bool HasInitialized();
            bool HasRomFs();
            void InitializeRender(Color Color);
            void FinalizeRender();
            void RenderTexture(NativeTexture Texture, s32 X, s32 Y, NativeTextureRenderOptions Options = NativeTextureRenderOptions::Default);
            void RenderRectangle(Color Color, s32 X, s32 Y, s32 Width, s32 Height);
            void RenderRectangleFill(Color Color, s32 X, s32 Y, s32 Width, s32 Height);
            void RenderRectangleOutline(Color Color, u32 X, u32 Y, u32 Width, u32 Height, u32 BorderWidth);
            void RenderRoundedRectangle(Color Color, s32 X, s32 Y, s32 Width, s32 Height, s32 Radius);
            void RenderRoundedRectangleFill(Color Color, s32 X, s32 Y, s32 Width, s32 Height, s32 Radius);
            void RenderCircle(Color Color, s32 X, s32 Y, s32 Radius);
            void RenderCircleFill(Color Color, s32 X, s32 Y, s32 Radius);
            void RenderShadowSimple(s32 X, s32 Y, s32 Width, s32 Height, s32 BaseAlpha, u8 MainAlpha = 255);
            void SetBaseRenderPosition(s32 X, s32 Y);
            void UnsetBaseRenderPosition();
            void SetBaseRenderAlpha(u8 Alpha);
            void UnsetBaseRenderAlpha();
        private:
            RendererInitOptions initopts;
            u32 sdlflags;
            u32 nrendflags;
            bool okromfs;
            bool okpl;
            u32 ww;
            u32 wh;
            bool initialized;
            NativeWindow rendwd;
            NativeSurface rendsf;
            s32 basex;
            s32 basey;
            int basea;
    };

    NativeRenderer GetMainRenderer();
}
