#version 460

layout (location = 0) uniform ivec2 iResolution;
layout (location = 1) uniform float iTime;
layout (location = 2) uniform mat4 MVP;
layout (location = 3) uniform vec3 CameraPosition;
layout (location = 4) uniform vec3 CameraDirection;


layout (location = 0) in vec3 Vpos;
layout (location = 1) in vec3 offsets;

out vec4 vertex_color;

void main()
{
    // gl_Position = MVP * vec4(Vpos+offsets[gl_InstanceID], 1.0);

    vec3 finalpos = Vpos + offsets;
    // finalpos.x += float(gl_InstanceID)*4.0;

    gl_Position = MVP * vec4(finalpos, 1.0);

    // vertex_color.rgb = Vpos + 0.5;
    vertex_color.rgb = offsets/10.0 + 0.5;
    vertex_color.a = 1.0;
};