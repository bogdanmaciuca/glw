#define DEBUG
#include <vector>
#define GLW_IMPLEMENTATION
#include "../glw.hpp"

int main() {
    glw::Context context("GLW Test", 1024, 768);
    std::vector<glm::vec2> vertices = {
        glm::vec2{-0.5f, -0.5f },
        glm::vec2{ 0.5f, -0.5f },
        glm::vec2{ 0.0f,  0.5f }
    };
    glw::VertexBuffer<glm::vec2> vbo(vertices);

    std::vector<glw::u32> indices = { 0, 1, 2 };
    glw::IndexBuffer<glw::u32> ibo(indices);

    glw::VertexArrayObject vao(&vbo, { {GL_FLOAT, 2} }, &ibo);

    const std::string vert_source =
        "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "uniform mat4 uMVP;"
        "void main()\n"
        "{\n"
        "   gl_Position = uMVP * vec4(aPos.xy, 0.0, 1.0);\n"
        "}\0";
    const std::string frag_source =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";

    glw::Shader shader(vert_source, frag_source);
    shader.Bind();

    glw::FPSCamera camera(80.0f, 1024.0f/768.0f);

    bool should_quit = false;
    glClearColor(0.2, 0.4, 0.6, 1.0);
    while (!should_quit) {
        const float delta_time = context.UpdateDeltaTime();

        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;
            }
        }
        const glw::u8* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W])
            camera.Move(glw::CameraForward, delta_time);
        else if (keys[SDL_SCANCODE_S])
            camera.Move(glw::CameraBackward, delta_time);
        if (keys[SDL_SCANCODE_A])
            camera.Move(glw::CameraLeft, delta_time);
        else if (keys[SDL_SCANCODE_D])
            camera.Move(glw::CameraRight, delta_time);

        camera.ProcessMouse();

        shader.SetMat4("uMVP", camera.GetProjectionMatrix() * camera.GetViewMatrix());

        glClear(GL_COLOR_BUFFER_BIT);
        vao.Draw();
        context.Present();
    }
}

