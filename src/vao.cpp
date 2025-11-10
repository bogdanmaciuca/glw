#include "glw/vao.hpp"

#include "glad.h"

namespace glw {
    void VAO::Bind() {
        glBindVertexArray(vao);
    }

    void VAO::Draw() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, draw_count);
    }
}

