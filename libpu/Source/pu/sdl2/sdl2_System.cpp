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
                g_initialized = false;
            }
        }

    }

    namespace ttf {

        static bool g_initialized = false;
        // TTF also initializes PL services for shared font handling

        Result Initialize() {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN(TTF_Init(), result::ResultTTFInitializationFailure)
                PU_RESULT_TRY(plInitialize())
                g_initialized = true;
            }
            return Success;
        }

        bool IsInitialized() {
            return g_initialized;
        }

        void Exit() {
            if(g_initialized) {
                plExit();
                TTF_Quit();
                g_initialized = false;
            }
        }

    }

    #if _PU_SDL2_MIXER
    
    namespace audio {

        static bool g_initialized = false;

        Result Initialize(u32 flags) {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN_VAL(Mix_Init(flags), flags, result::ResultMixerInitializationFailure)
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
                g_initialized = false;
            }
        }

    }

    #endif

    #if _PU_SDL2_IMAGE
    
    namespace image {

        static bool g_initialized = false;

        Result Initialize(u32 flags) {
            if(!g_initialized) {
                PU_TRY_SDL2_RETURN_VAL(IMG_Init(flags), flags, result::ResultImageInitializationFailure)
                g_initialized = true;
            }
            return Success;
        }

        bool IsInitialized() {
            return g_initialized;
        }

        void Exit() {
            if(g_initialized) {
                IMG_Quit();
                g_initialized = false;
            }
        }

    }

    #endif

}