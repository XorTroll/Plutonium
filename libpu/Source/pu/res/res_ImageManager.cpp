#include <pu/res/res_ImageManager.hpp>
#include <pu/render/render_Utils.hpp>
#include <map>

namespace pu::res {

    #if _PU_SDL2_IMAGE

    static std::map<std::string, sdl2::Texture> g_image_table;

    static inline Result LoadImageSurface(sdl2::Surface srf, const std::string &name) {
        PU_RESULT_UNLESS(sdl2::image::IsInitialized(), result::ResultImageNotInitialized);

        if(srf == nullptr) {
            return result::ResultImageBadImageLoad;
        }

        auto tex = render::ConvertToTexture(srf);
        if(tex == nullptr) {
            return result::ResultSDLTextureConversionFailure;
        }
        auto f = g_image_table.find(name);
        if(f == g_image_table.end()) {
            g_image_table.insert(std::make_pair(name, tex));
        }
        return Success;
    }

    Result LoadMemoryImage(const std::string &name, void *buffer, size_t buf_size) {
        PU_RESULT_UNLESS(sdl2::image::IsInitialized(), result::ResultImageNotInitialized);

        auto srf = IMG_Load_RW(SDL_RWFromMem(buffer, buf_size), 1);
        return LoadImageSurface(srf, name);
    }

    Result LoadExternalImage(const std::string &name, const std::string &path) {
        PU_RESULT_UNLESS(sdl2::image::IsInitialized(), result::ResultImageNotInitialized);

        auto srf = IMG_Load(path.c_str());
        return LoadImageSurface(srf, name);
    }

    sdl2::Texture GetImageByName(const std::string &name) {
        auto f = g_image_table.find(name);
        if(f != g_image_table.end()) {
            return f->second;
        } 
        return nullptr;
    }

    void UnloadImageByName(const std::string &name) {
        auto f = g_image_table.find(name);
        if(f != g_image_table.end()) {
            g_image_table.erase(name);
        } 
    }

    #endif

}