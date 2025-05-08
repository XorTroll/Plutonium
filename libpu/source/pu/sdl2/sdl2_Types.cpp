#include <pu/sdl2/sdl2_Types.hpp>
#include <pu/ui/render/render_SDL2.hpp>

namespace pu::sdl2 {

    TextureHandle::~TextureHandle() {
        ui::render::DeleteTexture(this->tex);
    }

}
