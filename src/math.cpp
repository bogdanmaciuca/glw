#include "glw/math.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace glw {
    mat4 LookAt(const vec3& eye, const vec3& point, const vec3& up) {
        return glm::lookAt(eye, point, up);
    }

    mat4 Perspective(float FOV, float width, float height, float z_near, float z_far) {
        return glm::perspectiveFov(glm::radians(FOV), width, height, z_near, z_far);
    }
}

