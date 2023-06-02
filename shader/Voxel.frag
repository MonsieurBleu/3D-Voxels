#version 460

layout (location = 0) uniform ivec2 iResolution;
layout (location = 1) uniform float iTime;

in vec4 vertex_color;

out vec4 frag_color;

void main()
{
    frag_color = vertex_color;
}