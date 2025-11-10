#include <vector>
#include "glw/glw.hpp"

int main() {
    glw::Initialize("Hello triangle!", 800, 600, true);

    std::vector<glw::Vertex<glw::vec3, glw::vec3>> vertices = {
        glw::MakeVertex(glw::vec3(-0.5f, -0.5f, 0.0f), glw::vec3(1.0f, 0.0f, 0.0f)),
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec3(0.0f, 1.0f, 0.0f)),
        glw::MakeVertex(glw::vec3( 0.0f,  0.5f, 0.0f), glw::vec3(0.0f, 0.0f, 1.0f))
    };
    auto vao = glw::CreateVAO(vertices).value();

    auto shader = glw::LoadGraphicsShader(
        "examples/01_triangle/shaders/basic.vert",
        "examples/01_triangle/shaders/basic.frag"
    ).value();

    while (!glw::ShouldQuit()) {
        glw::PollEvents();

        shader.Bind();
        glw::Clear();
        vao.Draw();
        glw::SwapBuffers();
    }
    
    return 0;
}

