cmake_minimum_required(VERSION 3.5.0)
project(opengl_grid_game_setup VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

add_executable(opengl_grid_game_setup
    src/main.cpp 
    src/glad.c
)

target_link_libraries(opengl_grid_game_setup
    glfw
)