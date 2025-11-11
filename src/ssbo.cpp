#include "glw/ssbo.hpp"

#include "glad.h"

namespace glw {
    void SSBO::Bind(int unit) {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, unit, ssbo_id);
    }

    void SSBO::Source(void* data, size_t size_bytes) {
        glNamedBufferData(ssbo_id, size_bytes, data, GL_STATIC_DRAW);
    }

    // TODO: error handling
    std::expected<SSBO, bool> CreateSSBO(size_t size_bytes) {
        SSBO result;
        glCreateBuffers(1, &result.ssbo_id);

        if (size_bytes != 0) {
            glNamedBufferData(result.ssbo_id, size_bytes, nullptr, GL_STATIC_DRAW);
        }
        
        return result;
    }
}

