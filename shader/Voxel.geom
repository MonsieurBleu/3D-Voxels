#version 460

layout (points) in;
layout (triangle_strip, max_vertices = 128) out;

layout (location = 0) uniform ivec2 iResolution;
layout (location = 1) uniform float iTime;

layout (location = 2) uniform mat4 MVP;

layout (location = 3) uniform vec4 CameraPosition;

in vec3 vp[];

out vec4 vertex_color;

void vertex(vec4 positon)
{
    gl_Position = MVP * positon;
    EmitVertex();
}

void planeZ(vec4 positon, float scale)
{
    vertex(vec4(-scale, -scale, 0.0, 1.0) + positon);

    vertex(vec4(-scale, scale, 0.0, 1.0) + positon);

    vertex(vec4(scale, -scale, 0.0, 1.0) + positon);

    EndPrimitive();



    vertex(vec4(scale, scale, 0.0, 1.0) + positon);

    vertex(vec4(-scale, scale, 0.0, 1.0) + positon);

    vertex(vec4(scale, -scale, 0.0, 1.0) + positon);

    EndPrimitive();
}

void planeX(vec4 positon, float scale)
{
    vertex(vec4(0.0, -scale, -scale, 1.0) + positon);

    vertex(vec4(0.0, -scale, scale, 1.0) + positon);

    vertex(vec4(0.0, scale, -scale, 1.0) + positon);

    EndPrimitive();



    vertex(vec4(0.0, scale, scale, 1.0) + positon);

    vertex(vec4(0.0, -scale, scale, 1.0) + positon);

    vertex(vec4(0.0, scale, -scale, 1.0) + positon);

    EndPrimitive();
}

void planeY(vec4 positon, float scale)
{
    vertex(vec4(-scale, 0.0, -scale, 1.0) + positon);

    vertex(vec4(-scale, 0.0, scale, 1.0) + positon);

    vertex(vec4(scale, 0.0, -scale, 1.0) + positon);

    EndPrimitive();



    vertex(vec4(scale, 0.0, scale, 1.0) + positon);

    vertex(vec4(-scale, 0.0, scale, 1.0) + positon);

    vertex(vec4(scale, 0.0, -scale, 1.0) + positon);

    EndPrimitive();
}


void main()
{
    float voxel_size = 1.0;

    vertex_color = vec4(0.75, 0.5, 0.5, 1.0);

    vec4 Zp = vec4(vp[0], 1.0) + vec4(0.0, 0.0 , voxel_size, 0.0);
    planeZ(Zp, voxel_size);

    vertex_color = vec4(0.75);
    vec4 Xp = vec4(vp[0], 1.0) + vec4(voxel_size, 0.0, 0.0, 0.0);
    planeX(Xp, voxel_size);

    vertex_color = vec4(0.5, 0.25, 0.5, 1.0);
    vec4 Yp = vec4(vp[0], 1.0) + vec4(0.0, voxel_size, 0.0, 0.0);
    planeY(Yp, voxel_size);
}