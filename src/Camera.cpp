#include <iostream>
#include <App.hpp>
#include <tgmath.h>

#include <glm/gtx/string_cast.hpp>

#include <Camera.hpp> 
#include <Utils.hpp>

#define PI 3.14159265358979323846

using namespace glm;

void Camera::init(float _FOV, float _width, float _height, float _nearPlane, float _farPlane)
{ 
    FOV = _FOV;
    width = _width;
    height = _height;
    nearPlane = _nearPlane;
    farPlane = _farPlane;

    position = vec3(0.0f, 0.0f, 4.0f); 
 
    lookpoint = vec3(0.0);
} 
 
void Camera::setCameraPosition(vec3 _position)
{ 
   position = _position; 
} 

void Camera::lookAt(vec3 _position)
{
    lookpoint = _position;
}

void Camera::updateViewMatrix()
{
    if(force_lookpoint)
        viewMatrix = glm::lookAt(position, lookpoint, vec3(0,1,0));
    else
        viewMatrix = glm::lookAt(position, position+direction, vec3(0,1,0));
}

void Camera::updateProjectionMatrix()
{
    projectionMatrix = perspective(FOV, width / height, nearPlane, farPlane);
}

const mat4 Camera::updateProjectionViewMatrix()
{
    updateViewMatrix();
    updateProjectionMatrix();
    ProjectionViewMatrix = projectionMatrix*viewMatrix*mat4(1.0);
    return ProjectionViewMatrix;
}

void Camera::updateMouseFollow(GLFWwindow *window)
{
    if(!is_following_mouse) return;

    vec<2, double, glm::packed_highp> Mouse_uv;
    glfwGetCursorPos(window, &Mouse_uv.x, &Mouse_uv.y);

    float th = sensitivity*Mouse_uv.y*PI*(1.0/height); // polar theta of direction
    float ph = sensitivity*Mouse_uv.x*PI*(1.0/width); // polar phi of direction

    direction = normalize(vec3(sin(th)*cos(ph), cos(th), sin(th)*sin(ph)));
}

void Camera::move(vec3 velocity, double deltatime)
{
    velocity *= deltatime;
    position += direction*velocity.x;

    position += cross(vec3(0.f, 1.f, 0.f), direction) * velocity.z;

    position.y += velocity.y;
}