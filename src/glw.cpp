#include "glw/glw.hpp"

#include <string>

#include "GLFW/glfw3.h"

#include "glw/debug.hpp"

namespace glw {
    static GLFWwindow* s_window;

    bool Initialize(const std::string& title, int width, int height, bool debug) {
        Debug::Set(debug);

        if (glfwInit() == false) {
            const char *error;
            glfwGetError(&error);
            Debug::Print("Could not initialize GLFW: {}", error);
            free((void*)error);
            return false;
        }

        s_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (s_window == nullptr) {
            const char *error;
            glfwGetError(&error);
            Debug::Print("Could not create window: {}", error);
            free((void*)error);
            return false;
        }

        glfwMakeContextCurrent(s_window);

        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
            Debug::Print("Could not initialize GLAD");
            return false;
        }

        return true;
    }

    void Terminate() {
        glfwDestroyWindow(s_window);
        glfwTerminate();
    }

    bool ShouldQuit() {
        return glfwWindowShouldClose(s_window);
    }

    void PollEvents() {
        glfwPollEvents();
    }

    void SwapBuffers() {
        glfwSwapBuffers(s_window);
    }

    void Clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

