#include <pu/audio/audio_Audio.hpp>

namespace pu::audio {

    bool Initialize(i32 mix_flags) {
        if(Mix_Init(mix_flags) != mix_flags) {
            return false;
        }

        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
            return false;
        }   
    
        return true;
    }

    void Finalize() {
        Mix_CloseAudio();
        Mix_Quit();
    }

}
