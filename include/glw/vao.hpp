#ifndef VAO_HPP
#define VAO_HPP

#include <expected>
#include <vector>

#include "../extern/glad/glad.h"

#include "types.hpp"
#include "vertex.hpp"
#include "debug.hpp"

namespace glw {
    struct VAO {
        u32  vao;
        u32  vbo;
        u32  ibo;
        u32  draw_count       = 0;
        bool has_index_buffer = false;
        void Bind();
        void Draw();
    };
    template<IsVertex V, typename I = u32>
    std::expected<VAO, bool> CreateVAO(std::vector<V> vertices, std::vector<I> indices = {}) {
        if (vertices.empty()) {
            Debug::Print("vertices cannot be empty");
            return std::unexpected(false);
        }

        VAO result;

        // VAO
        glGenVertexArrays(1, &result.vao);
        glBindVertexArray(result.vao);

        // VBO
        glGenBuffers(1, &result.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, result.vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(vertices[0]), vertices.data(),
            GL_STATIC_DRAW
        );
        result.draw_count = vertices.size();

        // IBO
        if (!indices.empty()) {
            glGenBuffers(1, &result.ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.ibo);
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                indices.size() * sizeof(indices[0]), indices.data(),
                GL_STATIC_DRAW
            );
            result.has_index_buffer = true;
            result.draw_count = indices.size();
        }

        // Vertex attributes
        ForEachVertexField(vertices[0], [](int i, auto field, size_t offset) {
            using FieldType = decltype(field);
            const static int stride = sizeof(vertices[0]);

            int num;
            int type;
            if constexpr      (std::is_same_v<FieldType, f32>) { num = 1; type = GL_FLOAT; }
            else if constexpr (std::is_same_v<FieldType, f64>) { num = 1; type = GL_DOUBLE; }
            else if constexpr (std::is_same_v<FieldType, i32>) { num = 1; type = GL_INT; }
            else if constexpr (std::is_same_v<FieldType, u32>) { num = 1; type = GL_UNSIGNED_INT; }

            else if constexpr (std::is_same_v<FieldType, vec2>) { num = 2; type = GL_FLOAT; }
            else if constexpr (std::is_same_v<FieldType, vec3>) { num = 3; type = GL_FLOAT; }
            else if constexpr (std::is_same_v<FieldType, vec4>) { num = 4; type = GL_FLOAT; }

            else if constexpr (std::is_same_v<FieldType, ivec2>) { num = 2; type = GL_INT; }
            else if constexpr (std::is_same_v<FieldType, ivec3>) { num = 3; type = GL_INT; }
            else if constexpr (std::is_same_v<FieldType, ivec4>) { num = 4; type = GL_INT; }

            else {
                static_assert(false, "Invalid field type in Vertex");
            }

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, num, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        });

        return result;
    }

}

#endif // VAO_HPP

