#ifndef VAO_HPP
#define VAO_HPP

#include <optional>
#include <vector>
#include <type_traits>

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

    /**
    * @brief Creates a vertex array object which encapsulates a
    * vertex buffer and an index buffer.
    *
    * @param [in] vertices An std::vector of the vertices of the
    * mesh. They can be of any Vertex<...> type.
    * @param [in] indices An std::vector of the indices of the
    * mesh, if it supports them. otherwise an empty vector
    *
    * @return An std::optional object containing the VAO on success
    * or std::nullopt on failure
    *
    * @note The fields of the Vertex<...> type can only be from
    * {f32, f64, i32, u32, vec2, vec3, vec4, ivec2, ivec3, ivec4}
    */
    template<IsVertex V, typename I = u32>
    std::optional<VAO> CreateVAO(
        const std::vector<V> vertices,
        const std::vector<I> indices = {}
    ) {
        if (vertices.empty()) {
            Debug::Print("vertices cannot be empty");
            return std::nullopt;
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
            using FieldType = std::decay_t<decltype(field)>;
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
            glVertexAttribPointer(i, num, type, GL_FALSE, stride, (void*)offset);
        });

        return result;
    }

}

#endif // VAO_HPP

