#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#pragma once 

#define GLM_FORCE_RADIAN 
#include <glm\glm.hpp> 
#include <glm\gtc\matrix_transform.hpp> 
 
class Camera 
{ 
    private: 
    
        float FOV = 50.f;
        float width = 1920.f;
        float height = 1080.f;
        float nearPlane = 0.1f;
        float farPlane = 100.f;

        glm::mat4 projectionMatrix; 
        glm::mat4 viewMatrix; 
        glm::mat4 ProjectionViewMatrix;
        glm::vec3 position; 
        glm::vec3 lookpoint; 

    public: 
        
    void init(float FOV, float width, float height, float nearplane, float farPlane); 
        
    void setCameraPosition(glm::vec3 _position); 
    glm::mat4 getViewMatrix(); 
    glm::mat4 getProjectionMatrix(); 
    
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateProjectionViewMatrix();
};

#endif