#ifndef MATH_HPP
#define MATH_HPP

#include "glm/gtc/matrix_transform.hpp"

#include "types.hpp"

namespace glw {
    mat4 LookAt(const vec3& eye, const vec3& point, const vec3& up = vec3(0, 1, 0));
}

#endif // MATH_HPP

