#version 460

layout (location = 0) uniform ivec2 iResolution;
layout (location = 1) uniform float iTime;

in vec3 Voxel_Position;

out vec3 vp;

void main()
{
    vp = Voxel_Position;

    // gl_Position = vec4(vp, 1.0);

    // vp = vec3(0.0);

    // vp.z = cos(iTime)*5.0;
    // vp.y = sin(iTime)*5.0;
};