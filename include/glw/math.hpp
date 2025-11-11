#ifndef MATH_HPP
#define MATH_HPP

#include "types.hpp"

namespace glw {
    /**
    * @brief Constructs a view matrix
    *
    * @param [in] eye The position of the camera
    * @param [in] point The point at which the camera looks
    * @param [in] up The up vector of the camera
    */
    mat4 LookAt(const vec3& eye, const vec3& point, const vec3& up = vec3(0, 1, 0));

    /**
    * @brief Constructs a projection matrix
    * 
    * @param [in] FOV Field of view in DEGREES
    * @param [in] width The width of the render target
    * @param [in] height The height of the render target
    * @param [in] z_near
    * @param [in] z_far
    */
    mat4 Perspective(
        float FOV, float width, float height,
        float z_near = 0.1f, float z_far = 100.0f
    );
}

#endif // MATH_HPP

