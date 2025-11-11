#ifndef GLW_HPP
#define GLW_HPP

#define GLFW_INCLUDE_NONE

#include <string>

#include "types.hpp"
#include "input.hpp"
#include "math.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "texture.hpp"

namespace glw {
    /**
    * @brief Initializes all glw subsystems
    *
    * @param [in] title  The title of the created window
    * @param [in] width  The width of the created window
    * @param [in] height The height of the created window
    * @param [in] debug  Whether to start in debug mode or not.
    * Debug mode prints to the console all errors.
    *
    * @return true on success, false on failure
    */
    bool Initialize(const std::string& title, int width, int height, bool debug = false);

    /**
    * @brief Deinitializes all glw subsystems
    */
    void Terminate();

    /**
    * @brief Gets the state of the window
    * @return true if the window has been closed
    */
    bool ShouldQuit();

    void PollEvents();

    void SwapBuffers();

    /**
    * @brief Clears the render region
    */
    void Clear();
}

#endif // GLW_HPP

