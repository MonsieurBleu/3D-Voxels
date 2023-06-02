#include <iostream>
#include <App.hpp>
#include <tgmath.h>

#include <Camera.hpp> 

using namespace glm;

void Camera::init(float FOV, float width, float height, float nearplane, float farPlane)
{ 
 
    position = vec3(0.0f, 0.0f, 4.0f); 
 
    lookpoint = vec3(0.0);

    projectionMatrix = perspective(FOV, width / height, nearplane, farPlane); 
} 
 
mat4 Camera::getViewMatrix()
{ 
   return viewMatrix; 
} 
mat4 Camera::getProjectionMatrix()
{ 
   return projectionMatrix; 
} 
 
void Camera::setCameraPosition(vec3 _position)
{ 
   position = _position; 
} 

void Camera::updateViewMatrix()
{
   viewMatrix = lookAt(
        position, // Camera is at (4,3,3), in World Space
        lookpoint, // and looks at the origin
        vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
}

void Camera::updateProjectionMatrix()
{
    projectionMatrix = perspective(FOV, width / height, nearPlane, farPlane); 
}

void Camera::updateProjectionViewMatrix()
{
    ProjectionViewMatrix = projectionMatrix*viewMatrix*mat4(1.0);
}