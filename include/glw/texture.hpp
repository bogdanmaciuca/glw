#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <expected>
#include <string>

#include "types.hpp"

namespace glw {
    struct Texture {
        u32 texture_id;
        i32 width = 0;
        i32 height = 0;
        void Bind(unsigned int unit);
    };

    std::expected<Texture, bool> CreateTexture(int width = 0, int height = 0);
    bool LoadTextureFromFile(
        Texture* texture, const std::string& path,
        int desired_channel_num = 4, bool generate_mipmap = true
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
    std::expected<Sampler, bool> CreateSampler(
        TextureFilter min_filter,
        TextureFilter mag_filter
    );
}

#endif // TEXTURE_HPP
