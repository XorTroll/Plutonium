/**
 * Plutonium library
 * @file render_Renderer.hpp
 * @brief Main rendering header.
 * @author XorTroll
 * @copyright XorTroll
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

    /**
     * @brief Represents the options for initializing the Renderer.
     */
    struct RendererInitOptions {
        u32 sdl_flags;
        u32 sdl_render_flags;
        u32 width;
        u32 height;
        s32 pl_srv_type;
        std::vector<PlSharedFontType> default_shared_fonts;
        std::vector<std::string> default_font_paths;
        std::vector<u32> extra_default_font_sizes;
        bool init_img;
        s32 sdl_img_flags;
        bool init_romfs;
        u32 pad_player_count;
        u64 pad_id_mask;
        u32 pad_style_tag;

        /**
         * @brief Creates a new RendererInitOptions with the specified parameters.
         * @param sdl_flags The flags for initializing SDL2.
         * @param sdl_render_flags The flags for initializing the Renderer.
         * @param w The width of the screen. By default, it is set to 1920.
         * @param h The height of the screen. By default, it is set to 1080.
         */
        RendererInitOptions(const u32 sdl_flags, const u32 sdl_render_flags, const u32 w = ScreenWidth, const u32 h = ScreenHeight) : sdl_flags(sdl_flags), sdl_render_flags(sdl_render_flags), width(w), height(h), pl_srv_type(-1), default_shared_fonts(), default_font_paths(), extra_default_font_sizes(), init_img(false), sdl_img_flags(0), init_romfs(false), pad_player_count(1), pad_id_mask(0), pad_style_tag(0) {}

        /**
         * @brief Sets the pl: service type to use.
         * @param type The pl: service type to use.
         * @note This function must be called for the Rendere to initialize any text/TTF functionalities.
         * @note You should probably use PlServiceType_User for your purposes, only use other types if you know what you're doing.
         */
        inline void SetPlServiceType(const PlServiceType type = PlServiceType_User) {
            this->pl_srv_type = type;
        }

        /**
         * @brief Adds a default shared font to load.
         * @param type The shared font type to load.
         */
        inline void AddDefaultSharedFont(const PlSharedFontType type) {
            this->default_shared_fonts.push_back(type);
        }

        /**
         * @brief Adds all shared fonts to load.
         */
        inline void AddDefaultAllSharedFonts() {
            for(u32 i = 0; i < PlSharedFontType_Total; i++) {
                this->default_shared_fonts.push_back(static_cast<PlSharedFontType>(i));
            }
        }

        /**
         * @brief Adds a default font path to load.
         * @param font_path The path to the font to load.
         */
        inline void AddDefaultFontPath(const std::string &font_path) {
            this->default_font_paths.push_back(font_path);
        }

        /**
         * @brief Adds an extra default font size to load.
         * @param font_size The font size to load.
         */
        inline void AddExtraDefaultFontSize(const u32 font_size) {
            this->extra_default_font_sizes.push_back(font_size);
        }

        /**
         * @brief Enables the Renderer to use SDL2_image with the specified flags.
         * @param sdl_img_flags The flags to use for SDL2_image.
         */
        inline void UseImage(const s32 sdl_img_flags) {
            this->init_img = true;
            this->sdl_img_flags = sdl_img_flags;
        }

        /**
         * @brief Enables the Renderer to use RomFs.
         * @note If RomFs is enabled, Plutonium itself will handle RomFs initializing/exiting.
         */
        inline void UseRomfs() {
            this->init_romfs = true;
        }

        /**
         * @brief Sets the amount of players to use for input.
         * @param count The amount of players to use for input.
         */
        inline void SetInputPlayerCount(const u32 count) {
            this->pad_player_count = count;
        }

        /**
         * @brief Adds an input Npad ID type to use for input.
         * @param type The Npad ID type to use for input.
         * @note You will need to add at least one Npad ID type to have any input.
         */
        inline void AddInputNpadIdType(const u64 type) {
            this->pad_id_mask |= BITL(type);
        }

        /**
         * @brief Adds an input Npad style tag to use for input.
         * @param tag The Npad style tag to use for input.
         * @note You will need to add at least one Npad style tag to have any input.
         */
        inline void AddInputNpadStyleTag(const u32 tag) {
            this->pad_style_tag |= tag;
        }

        /**
         * @brief Checks if the Renderer has initialized / will initialize the pl: service.
         * @return true if the Renderer has initialized / will initialize the pl: service, false otherwise.
         */
        inline bool NeedsPlService() {
            return this->pl_srv_type >= 0;
        }

        /**
         * @brief Checks if the Renderer has initialized / will initialize SDL2-TTF.
         * @return true if the Renderer has initialized / will initialize SDL2-TTF, false otherwise.
         */
        inline bool NeedsTtf() {
            return !this->default_shared_fonts.empty() || !this->default_font_paths.empty();
        }
    };

    constexpr u32 ImgAllFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP; // IMG_INIT_TIF not included since they are not supported here
    constexpr u32 RendererSoftwareFlags = SDL_RENDERER_SOFTWARE;
    constexpr u32 RendererHardwareFlags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;

    /**
     * @brief Represents the options for rendering a texture.
     */
    struct TextureRenderOptions {
        s32 alpha_mod;
        s32 width;
        s32 height;
        float rot_angle;
        s32 src_x;
        s32 src_y;

        static constexpr s32 NoAlpha = -1;
        static constexpr s32 NoWidth = -1;
        static constexpr s32 NoHeight = -1;
        static constexpr float NoRotation = -1.0f;
        static constexpr s32 NoSourceX = -1;
        static constexpr s32 NoSourceY = -1;

        /**
         * @brief Creates a new TextureRenderOptions with the specified parameters.
         * @param alpha The alpha to use for the texture, or nothing to make no alpha modifications.
         * @param width The width to use for the texturem or nothing to use the texture's base width.
         * @param height The height to use for the texture, or nothing to use the texture's base height.
         * @param rot_angle The rotation angle to use for the texture, or nothing to make no rotation.
         * @param src_x The source X to use for the texture, or nothing to use the entire texture source (0).
         * @param src_y The source Y to use for the texture, or nothing to use the entire texture source (0).
         */
        constexpr TextureRenderOptions(std::optional<u8> alpha, std::optional<s32> width, std::optional<s32> height, std::optional<float> rot_angle, std::optional<s32> src_x, std::optional<s32> src_y) : alpha_mod(alpha.value_or(NoAlpha)), width(width.value_or(NoWidth)), height(height.value_or(NoHeight)), rot_angle(rot_angle.value_or(NoRotation)), src_x(src_x.value_or(NoSourceX)), src_y(src_y.value_or(NoSourceY)) {}

        /**
         * @brief Creates a new TextureRenderOptions with default parameters (no alpha modifications, no custom width, no custom height, no rotation, no custom source X, no custom source Y).
         */
        constexpr TextureRenderOptions() : alpha_mod(NoAlpha), width(NoWidth), height(NoHeight), rot_angle(NoRotation), src_x(NoSourceX), src_y(NoSourceY) {}
    };

    /**
     * @brief The main class dealing with rendering.
     */
    class Renderer {
        private:
            RendererInitOptions init_opts;
            bool initialized;
            s32 base_x;
            s32 base_y;
            s32 base_a;
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
            /**
             * @brief Creates a new Renderer with the specified initialization options.
             * @param init_opts The options to use for initializing the Renderer.
             */
            Renderer(const RendererInitOptions init_opts) : init_opts(init_opts), initialized(false), base_x(0), base_y(0), base_a(0), input_pad() {}
            PU_SMART_CTOR(Renderer)

            /**
             * @brief Initializes the Renderer.
             * @note This function should not be called manually, it is called by the Application using this Renderer.
             * @return The result of the initialization.
             */
            Result Initialize();

            /**
             * @brief Finalizes the Renderer.
             * @note This function should not be called manually, it is called by the Application using this Renderer.
             */
            void Finalize();
            
            /**
             * @brief Checks if the Renderer has been initialized.
             * @return true if the Renderer has been initialized, false otherwise.
             */
            inline bool HasInitialized() {
                return this->initialized;
            }
            
            /**
             * @brief Initializes the rendering process.
             * @param clr The color to use for the background.
             * @note This function is called internally by the Application using this Renderer.
             */
            void InitializeRender(const Color clr);

            /**
             * @brief Finalizes the rendering process.
             * @note This function is called internally by the Application using this Renderer.
             */
            void FinalizeRender();

            /**
             * @brief Renders a texture to the screen.
             * @param texture The texture to render.
             * @param x The X position to render the texture.
             * @param y The Y position to render the texture.
             * @param opts The options to use for rendering the texture.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderTexture(sdl2::Texture texture, const s32 x, const s32 y, const TextureRenderOptions opts = TextureRenderOptions());

            /**
             * @brief Renders a rectangle to the screen (only the border).
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param width The width of the rectangle.
             * @param height The height of the rectangle.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderRectangle(const Color clr, const s32 x, const s32 y, const s32 width, const s32 height);

            /**
             * @brief Renders a filled rectangle to the screen.
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param width The width of the rectangle.
             * @param height The height of the rectangle.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderRectangleFill(const Color clr, const s32 x, const s32 y, const s32 width, const s32 height);
            
            /**
             * @brief Renders a rectangle outline to the screen.
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param width The width of the rectangle.
             * @param height The height of the rectangle.
             * @param border_width The width of the border.
             * @note This function should be called each render loop / OnRender call.
             */
            inline void RenderRectangleOutline(const Color clr, const s32 x, const s32 y, const s32 width, const s32 height, const s32 border_width) {
                this->RenderRectangleFill(clr, x - border_width, y - border_width, width + (border_width * 2), height + (border_width * 2));
            }
            
            /**
             * @brief Renders a rounded rectangle to the screen (only the border).
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param width The width of the rectangle.
             * @param height The height of the rectangle.
             * @param radius The radius of the rounded corners.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderRoundedRectangle(const Color clr, const s32 x, const s32 y, const s32 width, const s32 height, const s32 radius);

            /**
             * @brief Renders a filled rounded rectangle to the screen.
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param width The width of the rectangle.
             * @param height The height of the rectangle.
             * @param radius The radius of the rounded corners.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderRoundedRectangleFill(const Color clr, const s32 x, const s32 y, const s32 width, const s32 height, const s32 radius);

            /**
             * @brief Renders a circle to the screen (only the border).
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param radius The radius of the circle.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderCircle(const Color clr, const s32 x, const s32 y, const s32 radius);

            /**
             * @brief Renders a filled circle to the screen.
             * @param clr The color to use for the rectangle.
             * @param x The X position to render the rectangle.
             * @param y The Y position to render the rectangle.
             * @param radius The radius of the circle.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderCircleFill(const Color clr, const s32 x, const s32 y, const s32 radius);

            /**
             * @brief Renders a simple shadow to the screen.
             * @param x The X position to render the shadow.
             * @param y The Y position to render the shadow.
             * @param width The width of the shadow.
             * @param height The height of the shadow.
             * @param base_alpha The base alpha to use for the shadow. This is the starting alpha value at the top of the shadow.
             * @param main_alpha The main alpha to use for the shadow. The shadow's alpha will be blended with this value.
             * @note This function should be called each render loop / OnRender call.
             */
            void RenderShadowSimple(const s32 x, const s32 y, const s32 width, const s32 height, const s32 base_alpha, const u8 main_alpha = 0xFF);
            
            /**
             * @brief Sets the base render position for all rendering functions.
             * @param x The X position to use as the base render position.
             * @param y The Y position to use as the base render position.
             * @note Every rendered shape/texture will be rendered with this base position added to their X and Y positions.
             */
            inline void SetBaseRenderPosition(const s32 x, const s32 y) {
                this->base_x = x;
                this->base_y = y;
            }
            
            /**
             * @brief Resets the base render position to (0, 0).
             */
            inline void ResetBaseRenderPosition() {
                this->SetBaseRenderPosition(0, 0);
            }

            /**
             * @brief Sets the base render alpha for all rendering functions.
             * @param alpha The alpha to use as the base render alpha.
             * @note Every rendered shape/texture will be rendered blended with this base alpha value.
             */
            inline void SetBaseRenderAlpha(const u8 alpha) {
                this->base_a = alpha;
            }

            /**
             * @brief Resets the base render alpha(no alpha modifications).
             */
            inline void ResetBaseRenderAlpha() {
                this->base_a = -1;
            }

            /**
             * @brief Updates the input state.
             * @note This function is internally called by the Application using this Renderer.
             */
            inline void UpdateInput() {
                padUpdate(&this->input_pad);
            }

            /**
             * @brief Gets the buttons that are currently pressed.
             * @return The buttons that are currently pressed.
             */
            inline u64 GetButtonsDown() {
                return padGetButtonsDown(&this->input_pad);
            }

            /**
             * @brief Gets the buttons that are currently released.
             * @return The buttons that are currently released.
             */
            inline u64 GetButtonsUp() {
                return padGetButtonsUp(&this->input_pad);
            }

            /**
             * @brief Gets the buttons that are currently held.
             * @return The buttons that are currently held.
             */
            inline u64 GetButtonsHeld() {
                return padGetButtons(&this->input_pad);
            }
    };

    /**
     * @brief Gets the underlying SDL2 renderer.
     * @return The underlying SDL2 renderer.
     */
    sdl2::Renderer GetMainRenderer();

    /**
     * @brief Gets the underlying SDL2 window.
     * @return The underlying SDL2 window.
     */
    sdl2::Window GetMainWindow();

    /**
     * @brief Gets the underlying SDL2 surface.
     * @return The underlying SDL2 surface.
     */
    sdl2::Surface GetMainSurface();

    /**
     * @brief Gets the underlying SDL2 window width/height.
     * @return The underlying SDL2 window width/height.
     */
    std::pair<u32, u32> GetDimensions();

    /**
     * @brief Creates a font to the internal font list.
     * @param font_name The name to use for the font.
     * @param font The font to add.
     * @note For simple font management, consider using RendererInitOptions.
     */
    bool AddFont(const std::string &font_name, std::shared_ptr<ttf::Font> &font);

    /**
     * @brief Loads a system shared font (pl:) in a font object.
     * @param font The font object to load the shared font in.
     * @param type The shared font type to add.
     * @note For simple font management, consider using RendererInitOptions.
     * @note The pl: service must have been initialized for this function to work, either from RendererInitOptions or manually.
     */
    bool LoadSingleSharedFontInFont(std::shared_ptr<ttf::Font> &font, const PlSharedFontType type);

    /**
     * @brief Loads all system shared fonts (pl:) in a font object.
     * @param font The font object to load the shared fonts in.
     * @note For simple font management, consider using RendererInitOptions.
     * @note The pl: service must have been initialized for this function to work, either from RendererInitOptions or manually.
     */
    bool LoadAllSharedFontsInFont(std::shared_ptr<ttf::Font> &font);

    /**
     * @brief Adds a font object as a default font to the internal font list.
     * @param font The font object to add.
     */
    inline void AddDefaultFont(std::shared_ptr<ttf::Font> &font) {
        AddFont(MakeDefaultFontName(font->GetFontSize()), font);
    }

    /**
     * @brief Gets the resulting text size for rendering a text with the specified font.
     * @param font_name The name of the font to use.
     * @param text The text to render.
     * @param out_width The resulting width of the text.
     * @param out_height The resulting height of the text.
     * @return Whether the specified font is available (was added) or not, and the text size was calculated.
     */
    bool GetTextDimensions(const std::string &font_name, const std::string &text, s32 &out_width, s32 &out_height);

    /**
     * @brief Gets the resulting text width for rendering a text with the specified font.
     * @param font_name The name of the font to use.
     * @param text The text to render.
     * @return The resulting width of the text. If the font is not available, 0 will be returned.
     */
    s32 GetTextWidth(const std::string &font_name, const std::string &text);

    /**
     * @brief Gets the resulting text height for rendering a text with the specified font.
     * @param font_name The name of the font to use.
     * @param text The text to render.
     * @return The resulting height of the text. If the font is not available, 0 will be returned.
     */
    s32 GetTextHeight(const std::string &font_name, const std::string &text);

    /**
     * @brief Renders a text to a texture.
     * @param font_name The name of the font to use.
     * @param text The text to render.
     * @param clr The color to use for the text.
     * @param max_width The maximum width of the text.
     * @param max_height The maximum height of the text.
     * @note If max_width or max_height are 0, they will be ignored. If the text exceeds the dimensions, it will be clamped and ended by appending "...".
     * @return The rendered text texture. If the font is not available, nullptr will be returned.
     */
    sdl2::Texture RenderText(const std::string &font_name, const std::string &text, const Color clr, const u32 max_width = 0, const u32 max_height = 0);

}
