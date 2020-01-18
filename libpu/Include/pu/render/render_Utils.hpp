
#pragma once
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/ui/ui_Types.hpp>
#include <utility>

namespace pu::render {

    void DisposeTexture(sdl2::Texture texture);
    std::pair<u32, u32> GetTextureSize(sdl2::Texture texture);
    sdl2::Texture ConvertToTexture(sdl2::Surface surface);

    #if _PU_SDL2_IMAGE

    sdl2::Texture LoadImage(const std::string &path);

    #endif

    void DrawRectangle(ui::Color color, i32 x, i32 y, u32 w, u32 h, bool fill);
    
    inline void DrawRectangleOutline(ui::Color color, i32 x, i32 y, u32 w, u32 h, i32 border_w) {
        DrawRectangle(color, x - border_w, y - border_w, w + (border_w * 2), h + (border_w * 2), true);
    }
    
    #if _PU_SDL2_GFX

    void DrawRoundedRectangle(ui::Color color, i32 x, i32 y, u32 w, u32 h, i32 rad, bool fill);
    void DrawCircle(ui::Color color, i32 x, i32 y, i32 rad, bool fill);

    #endif

    void SetBasePosition(ui::Position pos);
    void ResetBasePosition();

    void SetForcedAlphaValue(u8 val);
    bool IsForcedAlphaValueSet();
    void ResetForcedAlphaValue();
    
}