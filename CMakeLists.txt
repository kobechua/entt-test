cmake_minimum_required(VERSION 3.28.3)
project(entt-test VERSION 0.1.0)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(extern/glfw)

target_include_directories(${PROJECT_NAME}
   PUBLIC extern/glfw/include
)

target_link_directories(${PROJECT_NAME}
   PRIVATE extern/glfw/src
)

target_link_libraries(${PROJECT_NAME}
   glfw
   GL
)

