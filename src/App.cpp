#include <App.hpp>
#include <Utils.hpp>
// #include <Octree.hpp>
#include <string.h> // for memset

#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>

//https://antongerdelan.net/opengl/hellotriangle.html

App::App(GLFWwindow* window) : window(window)
{
    timestart = Get_time_ms();
}

void App::mainInput(double deltatime)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        state = quit;
    
    float camspeed = 15.0;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camspeed *= 10.0;

    vec3 velocity(0.0);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        velocity.x += camspeed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        velocity.x -= camspeed;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        velocity.z -= camspeed;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        velocity.z += camspeed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        velocity.y += camspeed;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        velocity.y -= camspeed;
    }

    camera.move(velocity, deltatime);

    // if(glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
    // {
    //     camera.add_FOV(-0.1);
    // }

    // if(glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    // {
    //     camera.add_FOV(0.1);
    // }

    // if(glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    // {
    //     // glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data); //to update partially
    // }

    // if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    // {
    //     camera.toggle_mouse_follow();
    // }   
}


void App::mainloop()
{   
    /// CENTER WINDOW
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(window, (mode->width - 1920) / 2, (mode->height - 1080) / 2);

    /// SETTING UP THE CAMERA 
    camera.init(radians(50.0f), 1920.f, 1080.f, 0.1f, 1000.0f);

    camera.setCameraPosition(vec3(4.f, 3.f, 3.f));
    // camera.setForceLookPoint(true);
    // camera.lookAt(vec3(0.0));


    /// CREATING A SHADER PROGRAM
    // ShaderProgram test("shader/test.frag", "shader/test.vert", "");
    // ShaderProgram test("shader/Voxel.frag", "shader/Voxel.vert", "shader/Voxel.geom");
    ShaderProgram shader("shader/Voxel.frag", "shader/InstancedVoxel.vert", "");

    shader.activate();
    int winsizeh[2] = {1920/2, 1080/2};
    glUniform2iv(0, 1, winsizeh);

    glEnable(GL_DEPTH_TEST);


    /// CREATINHG VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    float voxel_size = 0.5;
    float points[] = 
    {
        // X FACES
        -voxel_size, voxel_size, voxel_size,
        -voxel_size, voxel_size, -voxel_size,
        -voxel_size, -voxel_size, voxel_size,
        -voxel_size, -voxel_size, -voxel_size,
        -voxel_size, voxel_size, -voxel_size,
        -voxel_size, -voxel_size, voxel_size,

        voxel_size, voxel_size, voxel_size,
        voxel_size, voxel_size, -voxel_size,
        voxel_size, -voxel_size, voxel_size,
        voxel_size, -voxel_size, -voxel_size,
        voxel_size, voxel_size, -voxel_size,
        voxel_size, -voxel_size, voxel_size,

        // Y FACES
        voxel_size, voxel_size, voxel_size,
        voxel_size, voxel_size, -voxel_size,
        -voxel_size, voxel_size, voxel_size,
        -voxel_size, voxel_size, -voxel_size,
        voxel_size, voxel_size, -voxel_size,
        -voxel_size, voxel_size, voxel_size,

        voxel_size, -voxel_size, voxel_size,
        voxel_size, -voxel_size, -voxel_size,
        -voxel_size, -voxel_size, voxel_size,
        -voxel_size, -voxel_size, -voxel_size,
        voxel_size, -voxel_size, -voxel_size,
        -voxel_size, -voxel_size, voxel_size,
    
        // Z FACES
        voxel_size, voxel_size, voxel_size,
        voxel_size, -voxel_size, voxel_size,
        -voxel_size, voxel_size, voxel_size,
        -voxel_size, -voxel_size, voxel_size,
        voxel_size, -voxel_size, voxel_size,
        -voxel_size, voxel_size, voxel_size,

        voxel_size, voxel_size, -voxel_size,
        voxel_size, -voxel_size, -voxel_size,
        -voxel_size, voxel_size, -voxel_size,
        -voxel_size, -voxel_size, -voxel_size,
        voxel_size, -voxel_size, -voxel_size,
        -voxel_size, voxel_size, -voxel_size,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(points), points, GL_STATIC_DRAW);

    // Création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Spécification de l'agencement des données
    GLint posAttrib = glGetAttribLocation(shader.get_program(), "Vpos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);



    /// CREATING INSTANCED OFFSETS
    GLuint pbo;
    glGenBuffers(1, &pbo);
    glBindBuffer(GL_ARRAY_BUFFER, pbo);

    int voxel_elem_nb = 3;
    uint32 grid_size = 50;
    uint32 instanced_cnt = grid_size*grid_size*grid_size;
    float offsets[instanced_cnt*voxel_elem_nb];
    uint32 index = 0;

    float voxel_spacement = 3.0;

    for(uint32 X = 0; X < grid_size; X++)
    for(uint32 Y = 0; Y < grid_size; Y++)
    for(uint32 Z = 0; Z < grid_size; Z++)
    {
        offsets[index] = X*voxel_spacement;
        offsets[index+1] = Y*voxel_spacement;
        offsets[index+2] = Z*voxel_spacement;

        index += voxel_elem_nb;
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(offsets), offsets, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
    glVertexAttribDivisor(1, 1); // This sets the vertex attribute to instanced attribute.



    /// MAIN LOOP
    while(state != quit)
    {
        double delta_time = Get_delta_time();

        glfwPollEvents();

        camera.updateMouseFollow(window);

        if(glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
        {
            system("cls");
            glDeleteProgram(shader.get_program());
            shader.CompileAndLink();
            shader.activate();
            int winsize[2] = {1920, 1080};
            glUniform2iv(0, 1, winsize);
        }

        mainInput(delta_time);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
        
        shader.activate();

        glBindVertexArray(vao);

        glUniform1f(1, (Get_time_ms()-timestart)*1.0/1000.0);
        glUniformMatrix4fv(2, 1, GL_FALSE, &camera.updateProjectionViewMatrix()[0][0]);
        glUniform3fv(3, 1, &camera.getPosition()[0]);
        glUniform3fv(4, 1, &camera.getDirection()[0]);

        // glDrawArrays(GL_TRIANGLES, 0, 6);

        // glDrawArrays(GL_POINTS, 0, buffer_size);

        glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(points)/3, instanced_cnt);

        glfwSwapBuffers(window);
    }
}