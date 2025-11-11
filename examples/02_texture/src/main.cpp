#include <print>
#include <vector>
#include "glw/glw.hpp"

int main() {
    if (glw::Initialize("Hello texture!", 800, 600, true) == false) {
        std::println("Could not initialize glw.");
        return 1;
    }

    std::vector<glw::Vertex<glw::vec3, glw::vec2>> vertices = {
        glw::MakeVertex(glw::vec3(-0.5f, -0.5f, 0.0f), glw::vec2(0.0f, 0.0f)), // Bottom-left
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec2(1.0f, 0.0f)), // Bottom-right
        glw::MakeVertex(glw::vec3(-0.5f,  0.5f, 0.0f), glw::vec2(0.0f, 1.0f)), // Top-left
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec2(1.0f, 0.0f)), // Bottom-right
        glw::MakeVertex(glw::vec3( 0.5f,  0.5f, 0.0f), glw::vec2(1.0f, 1.0f)), // Top-right
        glw::MakeVertex(glw::vec3(-0.5f,  0.5f, 0.0f), glw::vec2(0.0f, 1.0f))  // Top-left
    };

    auto vao_opt = glw::CreateVAO(vertices);
    if (!vao_opt) {
        std::println("Could not create VAO.");
        return 1;
    }
    glw::VAO vao = vao_opt.value();

    auto shader_opt = glw::CreateGraphicsShader(
        "examples/02_texture/shaders/basic.vert",
        "examples/02_texture/shaders/basic.frag"
    );
    if (!shader_opt) {
        std::println("Could not create shader.");
        return 1;
    }
    glw::Shader shader = shader_opt.value();

    auto texture_opt = glw::CreateTexture();
    if (!texture_opt) {
        std::println("Could not create texture.");
        return 1;
    }
    glw::Texture texture = texture_opt.value();

    if (glw::LoadTextureFromFile(&texture, "examples/02_texture/textures/image.png") == false) {
        std::println("Could not load image into texture.");
        return 1;
    }

    auto sampler_opt = glw::CreateSampler(glw::TEX_NEAREST, glw::TEX_NEAREST);
    if (!sampler_opt) {
        std::println("Could not create sampler.");
        return 1;
    }
    glw::Sampler sampler = sampler_opt.value();

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


