#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <glm/glm.hpp>

namespace glw {
    using u8    = uint8_t;
    using u16   = uint16_t;
    using u32   = uint32_t;
    using u64   = uint64_t;
    using i8    = int8_t;
    using i16   = int16_t;
    using i32   = int32_t;
    using i64   = int64_t;
    using f32   = float;
    using f64   = double;
    using usize = std::size_t;

    using vec2  = glm::vec2;
    using vec3  = glm::vec3;
    using vec4  = glm::vec4;
    using ivec2 = glm::ivec2;
    using ivec3 = glm::ivec3;
    using ivec4 = glm::ivec4;
    using mat3  = glm::mat3;
    using mat4  = glm::mat4;
}

#endif // TYPES_HPP

