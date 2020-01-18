#include <pu/sdl2/sdl2_System.hpp>

namespace pu::sdl2 {

    namespace system {

        static bool g_initialized = false;

        Result Initialize(u32 flags) {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN(SDL_Init(flags), result::ResultSDLInitializationFailure)
                g_initialized = true;
            }
            return Success;
        }

        bool IsInitialized() {
            return g_initialized;
        }

        void Exit() {
            if(g_initialized) {
                SDL_Quit();
            }
        }

    }

    namespace ttf {

        static bool g_initialized = false;

        Result Initialize() {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN(TTF_Init(), result::ResultTTFInitializationFailure)
                g_initialized = true;
            }
            return Success;
        }

        bool IsInitialized() {
            return g_initialized;
        }

        void Exit() {
            if(g_initialized) {
                TTF_Quit();
            }
        }

    }

    #if _PU_SDL2_MIXER
    
    namespace audio {

        static bool g_initialized = false;

        Result Initialize(u32 flags) {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN(Mix_Init(flags), result::ResultSDLInitializationFailure)
                g_initialized = true;
            }
            return Success;
        }

        bool IsInitialized() {
            return g_initialized;
        }

        void Exit() {
            if(g_initialized) {
                Mix_Quit();
            }
        }

    }

    #endif

    #if _PU_SDL2_IMAGE
    
    namespace image {

        static bool g_initialized = false;

        Result Initialize(u32 flags) {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN(IMG_Init(flags), result::ResultSDLInitializationFailure)
            }
            return Success;
        }

        bool IsInitialized() {
            return g_initialized;
        }

        void Exit() {
            if(g_initialized) {
                IMG_Quit();
            }
        }

    }

    #endif

}