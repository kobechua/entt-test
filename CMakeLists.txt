cmake_minimum_required(VERSION 3.28.3)
project(entt-test VERSION 0.1.0)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game src/main.cpp)

add_subdirectory(extern/glfw)
add_subdirectory(extern/entt)

target_include_directories(game
   PUBLIC extern/glfw/include
)

target_link_directories(game
   PRIVATE extern/glfw/src
)

target_link_libraries(game
   glfw
   GL
   EnTT::EnTT
)

