#include <print>
#include <vector>
#include "glw/glw.hpp"

int main() {
    if (glw::Initialize("Hello triangle!", 800, 600, true) == false) {
        std::println("Could not initialize glw");
        return 1;
    }

    std::vector<glw::Vertex<glw::vec3, glw::vec3>> vertices = {
        glw::MakeVertex(glw::vec3(-0.5f, -0.5f, 0.0f), glw::vec3(1.0f, 0.0f, 0.0f)),
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec3(0.0f, 1.0f, 0.0f)),
        glw::MakeVertex(glw::vec3( 0.0f,  0.5f, 0.0f), glw::vec3(0.0f, 0.0f, 1.0f))
    };

    auto vao_opt = glw::CreateVAO(vertices);
    if (!vao_opt) {
        std::println("Could not create VAO");
        return 1;
    }
    glw::VAO vao = vao_opt.value();

    auto shader_opt = glw::CreateGraphicsShader(
        "examples/01_triangle/shaders/basic.vert",
        "examples/01_triangle/shaders/basic.frag"
    );
    if (!shader_opt) {
        std::println("Could not create shader");
        return 1;
    }
    glw::Shader shader = shader_opt.value();

    while (!glw::ShouldQuit()) {
        glw::PollEvents();

        shader.Bind();
        glw::Clear();
        vao.Draw();
        glw::SwapBuffers();
    }
    
    return 0;
}

