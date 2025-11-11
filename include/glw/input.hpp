#ifndef INPUT_HPP
#define INPUT_HPP

#include "types.hpp"
#include "keys.hpp"

namespace glw {
    /**
    * @brief Checks whether a key is pressed or not
    */
    bool KeyDown(Key key);

    /**
    * @brief Gets the difference between the current mouse
    * position and the mouse position at the time of the last call
    */
    vec2 GetMouseDelta();

    /**
    * @brief Gets the mouse position
    */
    vec2 GetMousePos();
}

#endif // INPUT_HPP

