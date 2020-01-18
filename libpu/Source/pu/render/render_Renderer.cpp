#include <pu/render/render_Renderer.hpp>

namespace pu::render {

    Result CreateRenderer(Renderer &renderer, const std::string &window_title, i32 width, i32 height, u32 flags) {
        auto window = SDL_CreateWindow(window_title.c_str(), 0, 0, width, height, 0);
        PU_RESULT_UNLESS(window != nullptr, result::ResultSDLWindowCreationFailure);

        auto render = SDL_CreateRenderer(window, -1, flags);
        PU_RESULT_UNLESS(render != nullptr, result::ResultSDLRendererCreationFailure);

        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

        renderer.window = window;
        renderer.renderer = render;

        return Success;
    }

    void DisposeRenderer(Renderer &renderer) {

        if(renderer.IsValid()) {
            SDL_DestroyRenderer(renderer.renderer);
            SDL_DestroyWindow(renderer.window);
            renderer.renderer = nullptr;
            renderer.window = nullptr;
        }

    }

}