#include "glw/input.hpp"

#include "GLFW/glfw3.h"

#include "glw/types.hpp"

namespace glw {
    extern GLFWwindow* g_window;

    bool KeyDown(Key key) {
        return glfwGetKey(g_window, key);
    }

    vec2 GetMouseDelta() {
        static vec2 last_mouse_pos = GetMousePos();
        vec2 mouse_pos = GetMousePos();
        vec2 result = mouse_pos - last_mouse_pos;
        last_mouse_pos = mouse_pos;
        return result;
    }

    vec2 GetMousePos() {
        double x, y;
        glfwGetCursorPos(g_window, &x, &y);
        return vec2(x, y);
    }
}

