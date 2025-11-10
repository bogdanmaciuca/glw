#include <vector>
#include "glw/glw.hpp"

int main() {
    glw::Initialize("Hello triangle!", 800, 600, true);

    std::vector<glw::Vertex<glw::vec3, glw::vec2>> vertices = {
        glw::MakeVertex(glw::vec3(-0.5f, -0.5f, 0.0f), glw::vec2(0.0f, 0.0f)), // Bottom-left
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec2(1.0f, 0.0f)), // Bottom-right
        glw::MakeVertex(glw::vec3(-0.5f,  0.5f, 0.0f), glw::vec2(0.0f, 1.0f)), // Top-left
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec2(1.0f, 0.0f)), // Bottom-right
        glw::MakeVertex(glw::vec3( 0.5f,  0.5f, 0.0f), glw::vec2(1.0f, 1.0f)), // Top-right
        glw::MakeVertex(glw::vec3(-0.5f,  0.5f, 0.0f), glw::vec2(0.0f, 1.0f))  // Top-left
    };
    auto vao = glw::CreateVAO(vertices).value();


    auto shader = glw::LoadGraphicsShader(
        "examples/02_texture/shaders/basic.vert",
        "examples/02_texture/shaders/basic.frag"
    ).value();

    auto texture = glw::CreateTexture().value();
    glw::LoadTextureFromFile(&texture, "examples/02_texture/textures/image.png");

    Debug::Print("stuff");

    auto sampler = glw::CreateSampler(glw::TEX_NEAREST, glw::TEX_NEAREST).value();

    while (!glw::ShouldQuit()) {
        glw::PollEvents();

        glw::Clear();
        shader.Bind();
        texture.Bind(0);
        sampler.Bind(0);
        vao.Draw();
        glw::SwapBuffers();
    }

    return 0;
}


