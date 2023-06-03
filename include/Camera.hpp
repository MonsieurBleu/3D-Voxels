#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#pragma once 

#define GLM_FORCE_RADIAN 
#include <glm\glm.hpp> 
#include <glm\gtc\matrix_transform.hpp> 

using namespace glm;

class Camera 
{ 
    private: 
    
        float FOV = 1.0f;
        float width = 1920.f;
        float height = 1080.f;
        float nearPlane = 0.1f;
        float farPlane = 100.f;

        float sensitivity = 1.5;

        bool is_following_mouse = true;
        bool force_lookpoint = false;

        mat4 projectionMatrix; 
        mat4 viewMatrix; 
        mat4 ProjectionViewMatrix;
        vec3 position; 
        vec3 lookpoint; 
        vec3 direction;

    public: 
        
        void init(float FOV, float width, float height, float nearplane, float farPlane); 
        
        void setCameraPosition(vec3 _position); 
        void lookAt(vec3 _position);

        const vec3 getPosition() {return position;};
        const vec3 getDirection() {return direction;};
        const vec3 getLookpoint() {return lookpoint;};

        const mat4 getViewMatrix() {return viewMatrix;};
        const mat4 getProjectionMatrix() {return projectionMatrix;};
        const mat4 getProjectionViewMatrix() {return ProjectionViewMatrix;};
        
        void updateViewMatrix();
        void updateProjectionMatrix();
        const mat4 updateProjectionViewMatrix();

        void updateMouseFollow(GLFWwindow *window);

        void toggleMouseFollow(){is_following_mouse = !is_following_mouse;};
        void setMouseFollow(bool enable){is_following_mouse = enable;};

        void toggleForceLookPoint(){force_lookpoint = !force_lookpoint;};
        void setForceLookPoint(bool enable){force_lookpoint = enable;};

        void move(vec3 velocity, double deltatime);
};

#endif