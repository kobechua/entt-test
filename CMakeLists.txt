cmake_minimum_required(VERSION 3.28.3)
project(entt-test VERSION 0.1.0)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories( SYSTEM "extern/glad/include")

file(GLOB SOURCES "src/*.cpp")

add_executable(game ${SOURCES} "extern/glad/src/glad.c")

add_subdirectory(extern/glfw)
add_subdirectory(extern/entt)
add_subdirectory(extern/assimp)


target_include_directories(game
   PUBLIC extern/glfw/include
)

target_link_directories(game
   PRIVATE extern/glfw/src
)

target_link_libraries(game
   glfw
   EnTT::EnTT
   glm::glm
   assimp
)

