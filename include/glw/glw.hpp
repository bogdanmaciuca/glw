#ifndef GLW_HPP
#define GLW_HPP

#include <string>

#include "types.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "vao.hpp"
#include "texture.hpp"

namespace glw {
    bool Initialize(const std::string& title, int width, int height, bool debug = false);
    void Terminate();
    bool ShouldQuit();
    void PollEvents();
    void SwapBuffers();

    void Clear();
}

#endif // GLW_HPP

