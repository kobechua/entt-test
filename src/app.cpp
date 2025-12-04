#include "app.hpp"

// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


App::App()
{}

App::~App()
{}

int App::run()
{

    Window window = Window("Kobe", SCR_WIDTH, SCR_HEIGHT);

    Model  backpack("../res/models/backpack/backpack.obj");
    Shader modelShader("../res/shaders/model.vert",
                   "../res/shaders/model.frag");
    Camera camera = Camera();

    // Once after linking:
    modelShader.use();
    modelShader.setInt("texture_diffuse1",  0);
    modelShader.setInt("texture_diffuse2",  1);
    modelShader.setInt("texture_diffuse3",  2);
    modelShader.setInt("texture_diffuse4",  3);
    modelShader.setInt("texture_specular1", 4);
    modelShader.setInt("texture_specular2", 5);
    modelShader.setInt("texture_specular3", 6);
    modelShader.setInt("texture_specular4", 7);

    // Set light params (example)
    modelShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    modelShader.setVec3("dirLight.ambient",   glm::vec3(0.1f));
    modelShader.setVec3("dirLight.diffuse",   glm::vec3(0.8f));
    modelShader.setVec3("dirLight.specular",  glm::vec3(1.0f));

    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


    // game loop
    while (!glfwWindowShouldClose(window.getGLFWwindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        camera.Update(window);

        glm::mat4 view       = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f,
            100.0f
        );

        modelShader.use();
        modelShader.setVec3("viewPos", camera.Position);

        Renderer::BeginScene(view, projection);

        // example: 100 instances of the same model
        for (int i = 0; i < 100; ++i)
        {
            glm::mat4 modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, glm::vec3(i * 2.0f, 0.0f, 0.0f));
            Renderer::Submit(&backpack, &modelShader, modelMat);
        }

        Renderer::EndScene();

        glfwSwapBuffers(window.getGLFWwindow());
        
    }

    glfwTerminate();

    return 0;
}
