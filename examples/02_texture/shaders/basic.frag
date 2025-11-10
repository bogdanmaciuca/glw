#version 330 core

in vec2 o_texcoord;

out vec4 FragColor;

uniform sampler2D sampler;

void main() {
    FragColor = texture(sampler, o_texcoord);
}
