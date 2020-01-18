
#pragma once
#include <pu/pu_Results.hpp>
#include <pu/sdl2/sdl2_Types.hpp>

namespace pu::sdl2 {

    namespace flags {

        static constexpr u32 None = UINT32_MAX;

        NX_CONSTEXPR bool IsEmpty(u32 flags) {
            return flags == None;
        }
    }

    namespace system {

        namespace flags {



        }

        Result Initialize(u32 flags);
        bool IsInitialized();
        void Exit();

    }

    namespace ttf {

        Result Initialize();
        bool IsInitialized();
        void Exit();

    }

    #if _PU_SDL2_MIXER

    namespace audio {

        namespace flags {



        }

        Result Initialize(u32 flags);
        bool IsInitialized();
        void Exit();

    }

    #endif

    #if _PU_SDL2_IMAGE

    namespace image {

        namespace flags {



        }

        Result Initialize(u32 flags);
        bool IsInitialized();
        void Exit();

    }

    #endif

    template<u32 SystemFlags, bool DoTTF, u32 AudioFlags, u32 ImageFlags>
    class ScopedInitializer {

        private:
            Result rc;

        public:
            ScopedInitializer() : rc(Success) {
                this->rc = system::Initialize(SystemFlags);

                if(DoTTF) {
                    if(R_SUCCEEDED(this->rc)) {
                        this->rc = ttf::Initialize();
                    }
                }

                #if _PU_SDL2_MIXER

                if(!flags::IsEmpty(AudioFlags)) {
                    if(R_SUCCEEDED(this->rc)) {
                        this->rc = audio::Initialize(AudioFlags);
                    }
                }

                #endif

                #if _PU_SDL2_IMAGE

                if(!flags::IsEmpty(ImageFlags)) {
                    if(R_SUCCEEDED(this->rc)) {
                        this->rc = image::Initialize(ImageFlags);
                    }
                }

                #endif
            }

            ~ScopedInitializer() {
                #if _PU_SDL2_MIXER

                audio::Exit();

                #endif

                #if _PU_SDL2_IMAGE

                image::Exit();

                #endif
                
                ttf::Exit();
                system::Exit();
            }

            operator bool() {
                return R_SUCCEEDED(this->rc);
            }

            Result GetResult() {
                return this->rc;
            }
    };

    template<u32 SystemFlags, bool DoTTF, u32 AudioFlags, u32 ImageFlags>
    inline ScopedInitializer<SystemFlags, DoTTF, AudioFlags, ImageFlags> InitializeAll() {
        return ScopedInitializer<SystemFlags, DoTTF, AudioFlags, ImageFlags>();
    }
}