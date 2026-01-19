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

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


    // game loop
    while (!window.closed())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.update();
    }

    return 0;
}
