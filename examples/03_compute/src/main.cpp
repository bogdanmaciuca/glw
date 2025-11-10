#include <print>
#include <vector>
#include "glw/glw.hpp"

int main() {
    glw::Initialize("Compute", 800, 600, true);

    std::vector<glw::Vertex<glw::vec3, glw::vec2>> vertices = {
        glw::MakeVertex(glw::vec3(-0.5f, -0.5f, 0.0f), glw::vec2(0.0f, 0.0f)), // Bottom-left
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec2(1.0f, 0.0f)), // Bottom-right
        glw::MakeVertex(glw::vec3(-0.5f,  0.5f, 0.0f), glw::vec2(0.0f, 1.0f)), // Top-left
        glw::MakeVertex(glw::vec3( 0.5f, -0.5f, 0.0f), glw::vec2(1.0f, 0.0f)), // Bottom-right
        glw::MakeVertex(glw::vec3( 0.5f,  0.5f, 0.0f), glw::vec2(1.0f, 1.0f)), // Top-right
        glw::MakeVertex(glw::vec3(-0.5f,  0.5f, 0.0f), glw::vec2(0.0f, 1.0f))  // Top-left
    };

    auto vao = glw::CreateVAO(vertices).value();

    auto graphics_shader = glw::CreateGraphicsShader(
        "examples/03_compute/shaders/basic.vert",
        "examples/03_compute/shaders/basic.frag"
    ).value();

    auto compute_shader = glw::CreateComputeShader(
        "examples/03_compute/shaders/compute.comp").value();

    // TODO:
    glw::ivec3 max_group_count = glw::ComputeShader::GetMaxWorkGroupCount();
    std::println("Max group count: x = {}, y = {}, z = {}",
        max_group_count.x, max_group_count.y, max_group_count.z);
    std::println("Max invocation count: {}", glw::ComputeShader::GetMaxInvocationCount());

    auto texture = glw::CreateTexture(400, 300).value();
    auto sampler = glw::CreateSampler(glw::TEX_NEAREST, glw::TEX_NEAREST).value();

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

