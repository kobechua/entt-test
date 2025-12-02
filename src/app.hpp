

//EXTERNAL LIBRARIES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <entt/entt.hpp>

//LOCAL LIBRARIES
#include "gfx/shader.h"
#include "core/window.hpp"

//STANDARD
#include <iostream>
#include <filesystem>

class App
{
    public:
        App();
        ~App();

        int run();
};