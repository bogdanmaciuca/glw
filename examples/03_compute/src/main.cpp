#include <print>
#include <vector>
#include "glw/glw.hpp"

int main() {
    if (glw::Initialize("Compute", 800, 600, true) == false) {
        std::println("Could not initialize glw");
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

    auto graphics_shader_opt = glw::CreateGraphicsShader(
        "examples/03_compute/shaders/basic.vert",
        "examples/03_compute/shaders/basic.frag"
    );
    if (!graphics_shader_opt) {
        std::println("Could not create graphics shader.");
        return 1;
    }
    glw::GraphicsShader graphics_shader = graphics_shader_opt.value();

    auto compute_shader_opt = glw::CreateComputeShader("examples/03_compute/shaders/compute.comp");
    if (!compute_shader_opt) {
        std::println("Could not create compute shader.");
        return 1;
    }
    glw::ComputeShader compute_shader = compute_shader_opt.value();

    // TODO: GetMaxWorkGroupCount() not working right now
    glw::ivec3 max_group_count = glw::ComputeShader::GetMaxWorkGroupCount();
    std::println("Max group count: x = {}, y = {}, z = {}",
        max_group_count.x, max_group_count.y, max_group_count.z);
    std::println("Max invocation count: {}", glw::ComputeShader::GetMaxInvocationCount());

    auto texture_opt = glw::CreateTexture(400, 300);
    if (!texture_opt) {
        std::println("Could not create texture");
        return 1;
    }
    glw::Texture texture = texture_opt.value();

    auto sampler_opt = glw::CreateSampler(glw::TEX_NEAREST, glw::TEX_NEAREST);
    if (!sampler_opt) {
        std::println("Could not create sampler");
        return 1;
    }
    glw::Sampler sampler = sampler_opt.value();

    while (!glw::ShouldQuit()) {
        glw::PollEvents();

        glw::Clear();

        compute_shader.Bind();
        texture.BindAsImage(0, glw::IMG_WRITE);
        compute_shader.Dispatch(400 / 10, 300 / 10, 1);
        compute_shader.MemoryBarrier({ glw::MEM_BARRIER_IMG_ACCESS });

        graphics_shader.Bind();
        graphics_shader.SetInt("sampler", 0);
        sampler.Bind(0);
        texture.Bind(0);
        vao.Draw();

        glw::SwapBuffers();
    }
}

