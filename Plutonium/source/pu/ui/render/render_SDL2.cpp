#include <pu/ui/render/render_SDL2.hpp>
#include <pu/ui/render/render_Renderer.hpp>

namespace pu::ui::render {

    sdl2::Texture ConvertToTexture(sdl2::Surface surface) {
        if(surface == nullptr) {
            return nullptr;
        }

        auto tex = SDL_CreateTextureFromSurface(GetMainRenderer(), surface);
        SDL_FreeSurface(surface);
        return tex;
    }

    sdl2::Texture LoadImage(const std::string &path) {
        return ConvertToTexture(IMG_Load(path.c_str()));
    }

    i32 GetTextureWidth(sdl2::Texture texture) {
        if(texture == nullptr) {
            return 0;
        }

        i32 w = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, nullptr);
        return w;
    }

    i32 GetTextureHeight(sdl2::Texture texture) {
        if(texture == nullptr) {
            return 0;
        }

        i32 h = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &h);
        return h;
    }

    void SetAlphaValue(sdl2::Texture texture, const u8 alpha) {
        if(texture == nullptr) {
            return;
        }

        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, alpha);
    }

    void DeleteTexture(sdl2::Texture &texture) {
        if(texture != nullptr) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

}