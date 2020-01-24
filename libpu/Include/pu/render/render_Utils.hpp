
#pragma once
#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/ui/ui_Types.hpp>
#include <utility>

namespace pu::render {

    void DisposeTexture(sdl2::Texture texture);
    ui::Size GetTextureSize(sdl2::Texture texture);
    sdl2::Texture ConvertToTexture(sdl2::Surface surface);

    struct TextureDrawing {

        ui::Size custom_size;
        float angle;
        u8 custom_alpha;
        bool use_custom_alpha;

        TextureDrawing() : custom_size({ 0, 0 }), angle(0.0f), custom_alpha(0), use_custom_alpha(false) {}

        inline TextureDrawing WithCustomSize(u32 w, u32 h) {
            this->custom_size = { w, h };
            return *this;
        }

        inline TextureDrawing WithAngle(float angle) {
            this->angle = angle;
            return *this;
        }

        inline TextureDrawing WithCustomAlphaValue(u8 value) {
            this->custom_alpha = value;
            this->use_custom_alpha = true;
            return *this;
        }

    };

    void DrawTexture(sdl2::Texture texture, i32 x, i32 y, TextureDrawing drawing = {});
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