/**
 * Plutonium library
 * @file render_SDL2.hpp
 * @brief Contains useful wrappers for rendering with SDL2
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/sdl2/sdl2_Types.hpp>

namespace pu::ui::render {

    /**
     * @brief Converts a Surface to a Texture.
     * @param surface The Surface to convert.
     * @note The Surface will be freed after conversion.
     * @return The converted Texture.
     */
    sdl2::Texture ConvertToTexture(sdl2::Surface surface);

    /**
     * @brief Loads an image from the specified path.
     * @param path The path to the image.
     * @return The loaded image as a Texture, or nullptr if the image could not be loaded.
     */
    sdl2::Texture LoadImageFromFile(const std::string &path);

    /**
     * @brief Loads an image from the specified data buffer.
     * @param img_data The data buffer containing the image in the some supported image format (PNG, JPEG, etc).
     * @param img_size The size of the data buffer.
     * @return The loaded image as a Texture, or nullptr if the image could not be loaded.
     * @note If the data buffer is nullptr or the size is 0, this function will do nothing and return nullptr.
     * @note No write or free is done on the data buffer (it is only read), so it is up to the user to manage it.
     */
    sdl2::Texture LoadImageFromBuffer(const void *img_data, const size_t img_size);

    /**
     * @brief Gets the width of a Texture.
     * @param texture The Texture to get the width from.
     * @return The width of the Texture.
     */
    s32 GetTextureWidth(sdl2::Texture texture);

    /**
     * @brief Gets the height of a Texture.
     * @param texture The Texture to get the height from.
     * @return The height of the Texture.
     */
    s32 GetTextureHeight(sdl2::Texture texture);

    /**
     * @brief Sets the alpha value (for blending) of a Texture.
     * @param texture The Texture to set the alpha value to.
     * @param alpha The alpha value to set.
     */
    void SetAlphaValue(sdl2::Texture texture, const u8 alpha);

    /**
     * @brief Frees a Texture from memory, and sets nullptr to the reference.
     * @param texture The Texture to free.
     * @note If the Texture is nullptr, this function will do nothing.
     */
    void DeleteTexture(sdl2::Texture &texture);

}
