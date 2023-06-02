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

void App::mainInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        state = quit;
    
    float camspeed = 15.0;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camspeed *= 10.0;

    // vec3<float> velocity(0.0);

    // if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    // {
    //     velocity.x += camspeed;
    // }
    // if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    // {
    //     velocity.x -= camspeed;
    // }
    // if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    // {
    //     velocity.z -= camspeed;
    // }
    // if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    // {
    //     velocity.z += camspeed;
    // }
    // if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    // {
    //     velocity.y += camspeed;
    // }
    // if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    // {
    //     velocity.y -= camspeed;
    // }

    // camera.move(velocity);

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
    camera.init(radians(50.0f), 1920.f, 1080.f, 0.1f, 100.0f);

    camera.setCameraPosition(vec3(4.f, 3.f, 3.f));
    camera.lookAt(vec3(0.f));




    // // Or, for an ortho camera :
    // //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
    
    // glm::vec3 campos = glm::vec3(4,3,3);

    // // Camera matrix
    // glm::mat4 View = glm::lookAt(
    //     campos, // Camera is at (4,3,3), in World Space
    //     glm::vec3(0,0,0), // and looks at the origin
    //     glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    //     );
    
    // // Model matrix : an identity matrix (model will be at the origin)
    // glm::mat4 Model = glm::mat4(1.0f);
    // // Our ModelViewProjection : multiplication of our 3 matrices
    // glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around









    /// CREATING A SHADER PROGRAM
    // ShaderProgram test("shader/test.frag", "shader/test.vert", "");
    ShaderProgram test("shader/Voxel.frag", "shader/Voxel.vert", "shader/Voxel.geom");

    test.activate();
    int winsizeh[2] = {1920/2, 1080/2};
    glUniform2iv(0, 1, winsizeh);

    glEnable(GL_DEPTH_TEST);


    /// CREATINHG VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    float points[] = {
        0.0f,  0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Spécification de l'agencement des données
    GLint posAttrib = glGetAttribLocation(test.get_program(), "pos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    /// MAIN LOOP
    while(state != quit)
    {
        glfwPollEvents();

        camera.updateMouseFollow(window);

        if(glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
        {
            system("cls");
            glDeleteProgram(test.get_program());
            test.CompileAndLink();
            test.activate();
            int winsize[2] = {1920, 1080};
            glUniform2iv(0, 1, winsize);

        }

        mainInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
        

        glUniform1f(1, (Get_time_ms()-timestart)*1.0/1000.0);
        glUniformMatrix4fv(2, 1, GL_FALSE, &camera.updateProjectionViewMatrix()[0][0]);
        glUniform3fv(3, 1, &camera.getPosition()[0]);

        // glDrawArrays(GL_TRIANGLES, 0, 6);

        glDrawArrays(GL_POINTS, 0, 1);

        glfwSwapBuffers(window);
    }
}