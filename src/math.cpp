#include "glw/math.hpp"

namespace glw {
    mat4 LookAt(const vec3& eye, const vec3& point, const vec3& up) {
        return glm::lookAt(eye, point, up);
    }
}

