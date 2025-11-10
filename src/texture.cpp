// TODO:
// - decouple sampler from texture

#include "glw/texture.hpp"

#include <expected>
#include <string>

#include "glad.h"
#include "stb_image.h"

#include "glw/types.hpp"
#include "glw/debug.hpp"

namespace glw {
    unsigned int GetInternalFormatFromChannelNum(int channel_num);
    unsigned int GetFilter(TextureFilter glw_filter);

    void Texture::Bind(unsigned int unit) {
        glBindTextureUnit(unit, texture_id);
    }

    void Texture::BindAsImage(unsigned int unit, ImageAccess access) {
        GLenum gl_access;
        switch (access) {
            case IMG_READ:      gl_access = GL_READ_ONLY;  break;
            case IMG_WRITE:     gl_access = GL_WRITE_ONLY; break;
            case IMG_READWRITE: gl_access = GL_READ_WRITE; break;
            default:
                Debug::Print("Invalid ImageAccess value: {}", (int)access);
                break;
        }
        glBindImageTexture(unit, texture_id, 0, false, 0, gl_access, GL_RGBA8);
    }

    std::expected<Texture, bool> CreateTexture(int width, int height) {
        Texture result;
        glCreateTextures(GL_TEXTURE_2D, 1, &result.texture_id);

        // If width and height are not 0, allocate memory for
        // the texture and set its width and height
        if (width != 0 && height != 0) {
            glTextureStorage2D(result.texture_id, 1, GL_RGBA8, width, height);
            result.width = width;
            result.height = height;
        }

        return result;
    }

    bool LoadTextureFromFile(
        Texture* texture, const std::string& path,
        int desired_channel_num, bool generate_mipmap
    ) {
        // Remember these so that we can check if
        // memory was allocated for the texture or not
        i32 original_width = texture->width;
        i32 original_height = texture->height;

        // Load image from file
        int channel_num;
        u8* pixels = stbi_load(
            path.c_str(), &texture->width, &texture->height, &channel_num, desired_channel_num);
        if (pixels == nullptr) {
            Debug::Print("Could not load texture from file: {}", path);
            return false;
        }

        // If memory was not allocated, allocate now
        if (original_width == 0 && original_height == 0) {
            glTextureStorage2D(texture->texture_id, 1, GL_RGBA8, texture->width, texture->height);
        }

        // Fill the allocated memory
        glTextureSubImage2D(
            texture->texture_id, 0, 0, 0, texture->width, texture->height,
            GetInternalFormatFromChannelNum(desired_channel_num), GL_UNSIGNED_BYTE, pixels
        );

        if (generate_mipmap) {
            glGenerateTextureMipmap(texture->texture_id);
        }
        
        return true;
    }

    void Sampler::Bind(unsigned int unit) {
        glBindSampler(unit, sampler_id);
    }

    std::expected<Sampler, bool> CreateSampler(
        TextureFilter min_filter,
        TextureFilter mag_filter
    ) {
        Sampler result;
        glCreateSamplers(1, &result.sampler_id);

        glSamplerParameteri(result.sampler_id, GL_TEXTURE_MIN_FILTER, GetFilter(min_filter));
        glSamplerParameteri(result.sampler_id, GL_TEXTURE_MAG_FILTER, GetFilter(mag_filter));
        glSamplerParameteri(result.sampler_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(result.sampler_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        return result;
    }

    unsigned int GetInternalFormatFromChannelNum(int channel_num) {
        switch (channel_num) {
            case 1: return GL_RED;
            case 2: return GL_RG;
            case 3: return GL_RGB;
            case 4: return GL_RGBA;
            default:
                Debug::Print(
                    "Invalid internal format (wrong number of channels): {}", channel_num);
                return 0;
        }
    }
    
    unsigned int GetFilter(TextureFilter glw_filter) {
        switch (glw_filter) {
            case TEX_NEAREST: return GL_NEAREST;
            case TEX_LINEAR:  return GL_LINEAR;
            default:
                Debug::Print("Invalid sampler filter");
                return 0;
        }
    }
}
