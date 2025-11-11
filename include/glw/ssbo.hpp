#ifndef SSBO_HPP
#define SSBO_HPP

#include <cstddef>
#include <expected>

namespace glw {
    struct SSBO {
        unsigned int ssbo_id;
        size_t       size = 0; // In bytes
        void Bind(int unit);
        void Source(void* data, size_t byte_size);
        // TODO: SourceRange()
    };
    std::expected<SSBO, bool> CreateSSBO(size_t size_bytes = 0);
}

#endif // SSBO_HPP

