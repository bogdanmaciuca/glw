#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texcoord;

out vec2 o_texcoord;

void main() {
    gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
    o_texcoord = a_texcoord;
}
