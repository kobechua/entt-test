#define STB_IMAGE_IMPLEMENTATION

//EXTERNAL LIBRARIES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <entt/entt.hpp>
#include <stb_image.h>


//LOCAL LIBRARIES
#include "gfx/shader.h"
#include "core/window.hpp"

//STANDARD
#include <iostream>
#include <filesystem>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

const char *vertexShaderSource = "../res/shaders/shader.vert";
const char *fragmentShaderSource = "../res/shaders/shader.frag";


int main()
{

    Window window = Window("Kobe", SCR_WIDTH, SCR_HEIGHT);
    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, // right 
        0.0f,  0.5f, 0.0f  // top   
    }; 


    Shader shader = Shader(vertexShaderSource, fragmentShaderSource);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window.getGLFWwindow()))
    {
        window.clear();

        shader.use();
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
