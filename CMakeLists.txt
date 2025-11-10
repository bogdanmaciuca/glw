cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GLW VERSION 1.0 LANGUAGES CXX C)

file(GLOB SRCS src/*.cpp)
file(GLOB C_SRCS extern/glad/glad.c extern/stb/stb_image.c)

add_library(glw ${SRCS} ${C_SRCS})

target_include_directories(glw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
target_include_directories(glw PUBLIC extern/glad)
target_include_directories(glw PUBLIC extern/stb)

target_link_libraries(glw PUBLIC glfw ${OPENGL_LIBRARIES})

# Examples
option(BUILD_EXAMPLES "Build the project examples" ON)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
