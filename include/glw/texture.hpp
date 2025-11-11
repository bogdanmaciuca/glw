#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <optional>
#include <string>

#include "types.hpp"

namespace glw {
    enum ImageAccess {
        IMG_READ,
        IMG_WRITE,
        IMG_READWRITE,
    };

    struct Texture {
        u32 texture_id;
        i32 width = 0;
        i32 height = 0;
        void Bind(unsigned int unit);
        void BindAsImage(unsigned int unit, ImageAccess access);
    };

    // TODO: different texture formats
    /**
    * @brief Creates a texture object
    *
    * @param [in] width  Width of the texture (default 0)
    * @param [in] height Height of the texture (default 0)
    * 
    * @return An std::optional object containing the Texture on
    * success or std::nullopt on failure
    *
    * @note No memory space will be allocated for the texture if
    * width or height are 0
    */
    std::optional<Texture> CreateTexture(int width = 0, int height = 0);

    // TODO: allow to change the internal format
    /**
    * @brief Loads a texture from disk into a texture
    *
    * @param [out] texture A pointer to the texture to fill
    * @param [in] path The path to the image on disk
    * @param [in] generate_mipmap Whether or not to generate a
    * mipmap for the texture
    *
    * @return true on success or false on failure
    */
    bool LoadTextureFromFile(
        Texture* texture, const std::string& path,
        bool generate_mipmap = true
    );

    struct Sampler {
        u32 sampler_id;
        void Bind(unsigned int unit);
    };

    // TODO: add options for mipmaps
    enum TextureFilter {
        TEX_NEAREST, TEX_LINEAR
    };
    
    // TODO: add options for wrapping
    /**
    * @brief Creates a sampler
    *
    * @param [in] min_filter How the texture should be
    * sampled when zooming out
    * @param [in] min_filter How the texture should be
    * sampled when zooming in
    * @return An std::optional object containing the Sampler
    * on success or std::nullopt if creation fails.
    */
    std::optional<Sampler> CreateSampler(
        TextureFilter min_filter,
        TextureFilter mag_filter
    );
}

#endif // TEXTURE_HPP
