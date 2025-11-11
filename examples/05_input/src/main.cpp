#include <print>
#include "glw/glw.hpp"

int main() {
    if (glw::Initialize("Hello triangle!", 800, 600, true) == false) {
        std::println("Could not initialize glw");
        return 1;
    }

    while (!glw::ShouldQuit()) {
        glw::PollEvents();

        if (glw::KeyDown(glw::KEY_SPACE)) {
            std::println("SPACE is pressed!");
        }

        glw::vec2 mouse_delta = glw::GetMouseDelta();
        if (glm::abs(mouse_delta.x) > 0.0001f && glm::abs(mouse_delta.y) > 0.0001f) {
            std::println("Mouse delta: x = {}, y = {}", mouse_delta.x, mouse_delta.y);
        }

        glw::Clear();
        glw::SwapBuffers();
    }
}

