
/*

    Plutonium library

    @file render_Renderer.hpp
    @brief A Renderer is the object performing basic rendering. (simply, a SDL2 wrapper)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Color.hpp>
#include <pu/ui/render/render_SDL2.hpp>
#include <string>
#include <fstream>

namespace pu::ui::render
{
    class Renderer
    {
        public:
            void Initialize(u32 SdlFlags, bool RenderAccel = true);
            void Finalize();
            bool HasInitialized();
            bool HasRomFs();
            void InitializeRender(Color Color);
            void FinalizeRender();
            void RenderTexture(NativeTexture Texture, s32 X, s32 Y, int AlphaMod = -1);
            void RenderTextureScaled(NativeTexture Texture, s32 X, s32 Y, s32 Width, s32 Height, int AlphaMod = -1);
            void RenderRectangle(Color Color, s32 X, s32 Y, s32 Width, s32 Height);
            void RenderRectangleFill(Color Color, s32 X, s32 Y, s32 Width, s32 Height);
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
            bool okromfs;
            bool initialized;
            NativeWindow rendwd;
            NativeSurface rendsf;
            s32 basex;
            s32 basey;
            int basea;
    };

    NativeRenderer GetMainRenderer();
}
