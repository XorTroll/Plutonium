
#pragma once
#include <pu/pu_Base.hpp>
#include <pu/sdl2/sdl2_Types.hpp>

namespace pu::render {

    namespace flags {

        

    }

    struct Renderer {

        sdl2::Renderer renderer;
        sdl2::Window window;

        Renderer() : renderer(nullptr), window(nullptr) {}

        constexpr inline bool IsValid() {
            if(this->renderer != nullptr) {
                if(this->window != nullptr) {
                    return true;
                }
            }
            return false;
        }

    };

    Result CreateRenderer(Renderer &renderer, const std::string &window_title, s32 width, s32 height, u32 flags);
    void DisposeRenderer(Renderer &renderer);

}