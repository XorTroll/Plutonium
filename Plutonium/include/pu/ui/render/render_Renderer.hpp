
/*

    Plutonium library

    @file render_Renderer.hpp
    @brief A Renderer is the object performing basic rendering. (simply, a SDL2 wrapper)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/ui/render/render_SDL2.hpp>
#include <pu/ttf/ttf_Font.hpp>
#include <vector>

namespace pu::ui::render {

    constexpr u32 BaseScreenWidth = 1280;
    constexpr u32 BaseScreenHeight = 720;
    
    constexpr u32 ScreenWidth = 1920;
    constexpr u32 ScreenHeight = 1080;

    constexpr double ScreenFactor = (double)ScreenWidth / (double)BaseScreenWidth;

    struct RendererInitOptions {
        u32 sdl_flags;
        u32 sdl_render_flags;
        u32 width;
        u32 height;
        std::vector<PlSharedFontType> default_shared_fonts;
        std::vector<std::string> default_font_paths;
        std::vector<u32> extra_default_font_sizes;
        bool init_mixer;
        u32 audio_mixer_flags;
        bool init_img;
        u32 sdl_img_flags;
        bool init_romfs;
        u32 pad_player_count;
        u64 pad_id_mask;
        u32 pad_style_tag;

        RendererInitOptions(const u32 sdl_flags, const u32 sdl_render_flags, const u32 w = ScreenWidth, const u32 h = ScreenHeight) : sdl_flags(sdl_flags), sdl_render_flags(sdl_render_flags), width(w), height(h), default_shared_fonts(), default_font_paths(), extra_default_font_sizes(), init_mixer(false), audio_mixer_flags(0), init_img(false), sdl_img_flags(0), init_romfs(false), pad_player_count(1), pad_id_mask(0), pad_style_tag(0) {}

        inline void AddDefaultSharedFont(const PlSharedFontType type) {
            this->default_shared_fonts.push_back(type);
        }

        inline void AddDefaultAllSharedFonts() {
            for(u32 i = 0; i < PlSharedFontType_Total; i++) {
                this->default_shared_fonts.push_back(static_cast<PlSharedFontType>(i));
            }
        }

        inline void AddDefaultFontPath(const std::string &font_path) {
            this->default_font_paths.push_back(font_path);
        }

        inline void AddExtraDefaultFontSize(const u32 font_size) {
            this->extra_default_font_sizes.push_back(font_size);
        }

        inline void UseAudio(const u32 audio_mixer_flags) {
            this->init_mixer = true;
            this->audio_mixer_flags = audio_mixer_flags;
        }

        inline void UseImage(const u32 sdl_img_flags) {
            this->init_img = true;
            this->sdl_img_flags = sdl_img_flags;
        }

        inline void UseRomfs() {
            this->init_romfs = true;
        }

        inline void SetInputPlayerCount(const u32 count) {
            this->pad_player_count = count;
        }

        inline void AddInputNpadIdType(const u64 type) {
            this->pad_id_mask |= BITL(type);
        }

        inline void AddInputNpadStyleTag(const u32 tag) {
            this->pad_style_tag |= tag;
        }
    };

    constexpr u32 MixerAllFlags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    constexpr u32 IMGAllFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
    constexpr u32 RendererSoftwareFlags = SDL_RENDERER_SOFTWARE;
    constexpr u32 RendererHardwareFlags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;

    struct TextureRenderOptions {
        i32 alpha_mod;
        i32 width;
        i32 height;
        float rot_angle;

        static constexpr i32 NoAlpha = -1;
        static constexpr i32 NoWidth = -1;
        static constexpr i32 NoHeight = -1;
        static constexpr float NoRotation = -1.0f;

        static constexpr TextureRenderOptions Default() {
            return { NoAlpha, NoWidth, NoHeight, NoRotation };
        }
        
        static constexpr TextureRenderOptions WithCustomAlpha(const u8 alpha) {
            return { alpha, NoWidth, NoHeight, NoRotation };
        }

        static constexpr TextureRenderOptions WithCustomDimensions(const i32 width, const i32 height) {
            return { NoAlpha, width, height, NoRotation };
        }

        static constexpr TextureRenderOptions WithCustomAlphaAndDimensions(const u8 alpha, const i32 width, const i32 height) {
            return { alpha, width, height, NoRotation };
        }
    };

    class Renderer {
        private:
            RendererInitOptions init_opts;
            bool ttf_init;
            bool ok_romfs;
            bool ok_pl;
            bool initialized;
            i32 base_x;
            i32 base_y;
            i32 base_a;
            PadState input_pad;

            inline u8 GetActualAlpha(const u8 input_a) {
                if(this->base_a >= 0) {
                    return static_cast<u8>(this->base_a);
                }
                else {
                    return input_a;
                }
            }

        public:
            Renderer(const RendererInitOptions init_opts) : init_opts(init_opts), ok_romfs(false), ok_pl(false), initialized(false), base_x(0), base_y(0), base_a(0), input_pad() {}
            PU_SMART_CTOR(Renderer)

            void Initialize();
            void Finalize();
            
            inline bool HasInitialized() {
                return this->initialized;
            }

            inline bool HasRomFs() {
                return this->ok_romfs;
            }
            
            void InitializeRender(const Color clr);
            void FinalizeRender();
            void RenderTexture(sdl2::Texture texture, const i32 x, const i32 y, const TextureRenderOptions opts = TextureRenderOptions::Default());
            void RenderRectangle(const Color clr, const i32 x, const i32 y, const i32 width, const i32 height);
            void RenderRectangleFill(const Color clr, const i32 x, const i32 y, const i32 width, const i32 height);
            
            inline void RenderRectangleOutline(const Color clr, const i32 x, const i32 y, const i32 width, const i32 height, const i32 border_width) {
                this->RenderRectangleFill(clr, x - border_width, y - border_width, width + (border_width * 2), height + (border_width * 2));
            }
            
            void RenderRoundedRectangle(const Color clr, const i32 x, const i32 y, const i32 width, const i32 height, const i32 radius);
            void RenderRoundedRectangleFill(const Color clr, const i32 x, const i32 y, const i32 width, const i32 height, const i32 radius);
            void RenderCircle(const Color clr, const i32 x, const i32 y, const i32 radius);
            void RenderCircleFill(const Color clr, const i32 x, const i32 y, const i32 radius);
            void RenderShadowSimple(const i32 x, const i32 y, const i32 width, const i32 height, const i32 base_alpha, const u8 main_alpha = 0xFF);
            
            inline void SetBaseRenderPosition(const i32 x, const i32 y) {
                this->base_x = x;
                this->base_y = y;
            }
            
            inline void ResetBaseRenderPosition() {
                this->SetBaseRenderPosition(0, 0);
            }

            inline void SetBaseRenderAlpha(const u8 alpha) {
                this->base_a = alpha;
            }

            inline void ResetBaseRenderAlpha() {
                this->base_a = -1;
            }

            inline void UpdateInput() {
                padUpdate(&this->input_pad);
            }

            inline u64 GetButtonsDown() {
                return padGetButtonsDown(&this->input_pad);
            }

            inline u64 GetButtonsUp() {
                return padGetButtonsUp(&this->input_pad);
            }

            inline u64 GetButtonsHeld() {
                return padGetButtons(&this->input_pad);
            }
    };

    // Global rendering

    sdl2::Renderer GetMainRenderer();
    sdl2::Window GetMainWindow();
    sdl2::Surface GetMainSurface();

    std::pair<u32, u32> GetDimensions();

    // Font loading

    bool AddFont(const std::string &font_name, std::shared_ptr<ttf::Font> &font);

    bool LoadSingleSharedFontInFont(std::shared_ptr<ttf::Font> &font, const PlSharedFontType type);
    bool LoadAllSharedFontsInFont(std::shared_ptr<ttf::Font> &font);

    inline void AddDefaultFont(std::shared_ptr<ttf::Font> &font) {
        AddFont(MakeDefaultFontName(font->GetFontSize()), font);
    }

    // Text rendering

    bool GetTextDimensions(const std::string &font_name, const std::string &text, i32 &out_width, i32 &out_height);
    i32 GetTextWidth(const std::string &font_name, const std::string &text);
    i32 GetTextHeight(const std::string &font_name, const std::string &text);
    sdl2::Texture RenderText(const std::string &font_name, const std::string &text, const Color clr, const u32 max_width = 0, const u32 max_height = 0);

}
