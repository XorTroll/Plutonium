#include <pu/render/render_Utils.hpp>
#include <pu/ui/ui_Application.hpp>

namespace pu::render {

    #define _PU_RENDER_DO_WITH_RENDERER(...) { \
        auto app = ui::GetApplication(); \
        if(app) { \
            auto &renderer = app->GetRenderer(); \
            if(renderer.IsValid()) { \
                __VA_ARGS__ \
            } \
        } \
    }

    static ui::Position g_base_position = { 0, 0 };
    static u8 g_forced_alpha = 0;
    static bool g_forced_alpha_set = false;

    void DisposeTexture(sdl2::Texture texture) {
        if(texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }

    ui::Size GetTextureSize(sdl2::Texture texture) {
        i32 w = 0;
        i32 h = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        return { (u32)w, (u32)h };
    }

    sdl2::Texture ConvertToTexture(sdl2::Surface surface) {
        _PU_RENDER_DO_WITH_RENDERER({
            auto tex = SDL_CreateTextureFromSurface(renderer.renderer, surface);
            if(tex != nullptr) {
                SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
                SDL_FreeSurface(surface);
                return tex;
            }
        })
        return nullptr;
    }

    #if _PU_SDL2_IMAGE

    sdl2::Texture LoadImage(const std::string &path) {
        _PU_RENDER_DO_WITH_RENDERER({
            auto srf = IMG_Load(path.c_str());
            if(srf != nullptr) {
                return ConvertToTexture(srf);
            }
        })
        return nullptr;
    }

    #endif

    static inline ui::Color AdaptColor(ui::Color clr) {
        if(g_forced_alpha_set) {
            auto newclr = clr;
            newclr.a = g_forced_alpha;
            return newclr;
        }
        return clr;
    }

    static inline ui::Position MakePosition(i32 x, i32 y) {
        return { x + g_base_position.x, y + g_base_position.y };
    }

    static inline SDL_Rect MakeRect(i32 x, i32 y, u32 w, u32 h) {
        auto pos = MakePosition(x, y);
        return ui::PositionAndSize{ pos.x, pos.y, w, h }.ToSDLRect();
    }

    void DrawTexture(sdl2::Texture texture, i32 x, i32 y, TextureDrawing drawing) {
        if(texture != nullptr) {
            _PU_RENDER_DO_WITH_RENDERER({
                auto sz = GetTextureSize(texture);
                if(drawing.custom_size.IsValid()) {
                    sz.w = drawing.custom_size.w;
                    sz.h = drawing.custom_size.h;
                }
                auto rect = MakeRect(x, y, PU_UI_FORWARD_SIZE(sz));
                if(drawing.use_custom_alpha) {
                    SDL_SetTextureAlphaMod(texture, drawing.custom_alpha);
                }
                SDL_RenderCopyEx(renderer.renderer, texture, nullptr, &rect, drawing.angle, nullptr, SDL_FLIP_NONE);
            })
        }
    }

    void DrawRectangle(ui::Color color, i32 x, i32 y, u32 w, u32 h, bool fill) {
        _PU_RENDER_DO_WITH_RENDERER({
            auto rect = MakeRect(x, y, w, h);
            auto clr = AdaptColor(color);
            SDL_SetRenderDrawColor(renderer.renderer, clr.r, clr.g, clr.b, clr.a);
            if(fill) {
                SDL_RenderFillRect(renderer.renderer, &rect);
            }
            else {
                SDL_RenderDrawRect(renderer.renderer, &rect);
            }
        })
    }

    #if _PU_SDL2_GFX

    void DrawRoundedRectangle(ui::Color color, i32 x, i32 y, u32 w, u32 h, i32 rad, bool fill) {
        _PU_RENDER_DO_WITH_RENDERER({
            auto clr = AdaptColor(color);
            auto rect = MakeRect(x, y, w, h);
            roundedBoxRGBA(renderer.renderer, rect.x, rect.y, rect.x + w, rect.y + h, rad, clr.r, clr.g, clr.b, clr.a);
        })
    }

    void DrawCircle(ui::Color color, i32 x, i32 y, i32 rad, bool fill) {
        _PU_RENDER_DO_WITH_RENDERER({
            auto clr = AdaptColor(color);
            auto pos = MakePosition(x, y);
            if(fill) {
                filledCircleRGBA(renderer.renderer, pos.x, pos.y, rad - 1, clr.r, clr.g, clr.b, clr.a);
            }
            else {
                circleRGBA(renderer.renderer, pos.x, pos.y, rad - 1, clr.r, clr.g, clr.b, clr.a);
            }
            aacircleRGBA(renderer.renderer, pos.x, pos.y, rad - 1, clr.r, clr.g, clr.b, clr.a);
        })
    }

    #endif

    void SetBasePosition(ui::Position pos) {
        g_base_position = pos;
    }

    void ResetBasePosition() {
        g_base_position = { 0, 0 };
    }

    void SetForcedAlphaValue(u8 val) {
        g_forced_alpha = val;
        g_forced_alpha_set = true;
    }

    bool IsForcedAlphaValueSet() {
        return g_forced_alpha_set;
    }

    void ResetForcedAlphaValue() {
        g_forced_alpha_set = false;
    }

}