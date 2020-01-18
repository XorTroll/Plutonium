
#pragma once
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/render/render_Renderer.hpp>
#include <pu/ui/ui_Types.hpp>
#include <utility>
#include <map>

namespace pu::render {

    void DisposeTexture(sdl2::Texture texture);

    #if _PU_SDL2_IMAGE

    sdl2::Texture LoadImage(const std::string &path);

    #endif

    std::pair<s32, s32> GetTextureSize(sdl2::Texture texture);

    // These below require a renderer

    sdl2::Texture ConvertToTexture(render::Renderer &renderer, sdl2::Surface surface);
    void DrawRectangle(ui::Color color, s32 x, s32 y, s32 w, s32 h, bool fill);
    void DrawRectangleOutline(ui::Color color, s32 x, s32 y, s32 w, s32 h, s32 border_w);
    void DrawRoundedRectangle(ui::Color color, s32 x, s32 y, s32 w, s32 h, s32 rad, bool fill);
    void DrawCircle(ui::Color, s32 x, s32 y, s32 rad, bool fill);
    
}