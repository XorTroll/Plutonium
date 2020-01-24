
#pragma once
#include <pu/sdl2/sdl2_System.hpp>

namespace pu::res {

    #if _PU_SDL2_IMAGE

    Result LoadMemoryImage(const std::string &name, void *buffer, size_t buf_size);
    Result LoadExternalImage(const std::string &name, const std::string &path);
    sdl2::Texture GetImageByName(const std::string &name);
    void UnloadImageByName(const std::string &name);

    #endif
    
}