#include <glad/glad.h>                      // load in OpenGL functions
#include <GLFW/glfw3.h>                     // OpenGL functions
#include <iostream>                         // push stuff to terminal
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "tile.hpp"
#include <cmath>
#include <vector>
#include <iomanip>
#include "player.hpp"

/// @todo - 
///         images on tiles
///         read in map data from csv file

/// @brief create the window and initialize OpenGL, returning pointer to window
/// @param width The width in pixels of the screen to be made
/// @param height The height in pixels of the screen to be made
/// @param title The title to give the created window
/// @return pointer to the created window
GLFWwindow* setupWindow(unsigned int width, unsigned int height, const char* title);

/// @brief  Function called automatically when dynamically resizing the screen
/// @param window pointer to the window object
/// @param width width in pixels of the new window
/// @param height height in pixels of the new window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/// @brief check inputs and determine what to do as a result
/// @param window The window whose inputs are being checked
/// @param player The player object whose direction in changed by user
/// @param deltaTime used to make player movement speed consistent
void processInput(GLFWwindow *window, Player& player, float deltaTime);



const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 9;

/// @brief Find the 9 tiles around the player for collision detection
/// @param surrounding_tiles a vector to store pointers to nearby tiles
/// @param player_center the rounded position of the center of the player tile
/// @param static_map the tile map containing all static tiles
void determine_surrounding_tiles(std::vector<Tile*>& surrounding_tiles, glm::vec2 player_center, Tile* static_map[MAP_HEIGHT][MAP_WIDTH]);

/// @brief Create the static map
/// @param static_map the array to create containing nullptr or a pointer to a new tile object
/// @param perspective the mat4 the initialize new tiles with
void create_static_map(Tile* static_map[MAP_HEIGHT][MAP_WIDTH], glm::mat4 perspective);

// enforce 16:9 aspect ratio given a screen width

const float TILE_SIZE = 64.0f;
const float SCREEN_W = TILE_SIZE * 16.0f;
const float SCREEN_H = TILE_SIZE * 9.0f;

int main() {
    // setup opengl
    GLFWwindow* window = setupWindow(static_cast<int>(SCREEN_W),static_cast<int>(SCREEN_H),"Grid Setup");

    if (window == nullptr) { 
        std::cout << "ERROR. OPENGL FAILURE" << std::endl;
        return -1;
    }

    // setup orthogonal perspective
    glm::mat4 perspective = glm::ortho(0.0f,SCREEN_W, 0.0f, SCREEN_H);
    
    // create array of tiles
    Tile* static_map[MAP_HEIGHT][MAP_WIDTH] = {{nullptr}};
    create_static_map(static_map, perspective);


    // create Player
    Player* player = new Player(glm::vec2(3.0f * TILE_SIZE, 4.0f * TILE_SIZE), perspective);

    // wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    float timeElapsed = 0.0f;  // time since last print statement
    // render loop
    while (!glfwWindowShouldClose(window))
    {
   
        // update dt
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        timeElapsed += currentFrame;

        if(timeElapsed > 1000.0f) {
            //std::cout << "FPS: " << (1.0f / deltaTime) << std::endl;
            timeElapsed = 0.0f;
        }


        // input
        processInput(window, *player, deltaTime);

        // determine the 9 cells around the player
        std::vector<Tile*> surrounding_tiles;
        determine_surrounding_tiles(surrounding_tiles, player->pos() / TILE_SIZE, static_map);

        // move player and handle collision with static tiles
        player->move(surrounding_tiles, deltaTime);

        // render stuff
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw map
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                if (static_map[y][x] != nullptr){
                    static_map[y][x]->draw();
                }
            }
        }

        // draw player
        player->draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    
    // deallocate map memory
   // draw map
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                if (static_map[y][x] != nullptr){
                    delete static_map[y][x];
                    static_map[y][x] = nullptr;
                }
            }
        }

    // deallocate player
    delete player;
    player = nullptr;

    glfwTerminate();
    return 0;
}

// setup window and startup opengl, return refrence to window object
GLFWwindow* setupWindow(unsigned int width, unsigned int height, const char* title)
{
        // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    window = window;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Player& player, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, true);
    } 

    // jump check
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player.jump();
    }
    
    
    // check horizontal movement
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.move_left();
    } if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.move_right();
    }

}

void create_static_map(Tile* static_map[MAP_HEIGHT][MAP_WIDTH], glm::mat4 perspective){
        // screen holds 16:9 tiles
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 5, 0, 0, 0, 4, 4, 3, 3, 3, 1, 2},
        {2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 3, 4, 0, 0, 0, 4, 4, 4, 3, 3, 3, 1, 2},
        {2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    };

    // flip map  - (0,0) is bottom left of map, so flip y so that's its index too
    int temp;  // Temporary array to hold one row
    // Loop through half of the rows
    for (int i = 0; i < 9 / 2; i++) {
        // Swap the x-values of the rows
        for (int j = 0; j < 16; j++){
            temp = map[i][j];
            map[i][j] = map[8 - i][j];
            map[8 - i][j] = temp;
        }
    }


    glm::vec3 color_map[] = {
        glm::vec3(0.7f, 0.0f, 0.0f),    // red
        glm::vec3(0.0f, 0.7f, 0.0f),    // green
        glm::vec3(0.7f, 0.7f, 0.0f),    // yellow
        glm::vec3(0.0f, 0.0f, 0.7f),    // blue
        glm::vec3(0.7f, 0.0f, 0.7f),    // magenta
        glm::vec3(0.0f, 0.7f, 0.7f),    // cyan
    };

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x){
            if (map[y][x]) {
                static_map[y][x] = new Tile(static_cast<float>(x) * TILE_SIZE, 
                static_cast<float>(y) * TILE_SIZE, TILE_SIZE, TILE_SIZE, perspective,color_map[map[y][x] - 1]);
            }
        }
    }

}

void determine_surrounding_tiles(std::vector<Tile*>& surrounding_tiles, glm::vec2 player_center, Tile* static_map[MAP_HEIGHT][MAP_WIDTH]) {

    // find what tile the center of the player is on before move
    glm::ivec2 center = glm::ivec2(static_cast<int>(player_center.x), static_cast<int>(player_center.y));

    for (int y = -1; y < 2; ++y){
        for (int x = - 1; x < 2; ++x){
            // ensure not out of bounds - avoid invalid array access
            if (center.y + y >= 0 && center.y + y < MAP_HEIGHT && center.x + x >= 0 && center.x + x < MAP_WIDTH){
                surrounding_tiles.push_back(static_map[center.y + y][center.x + x]);
            }
        }
    }

}

/* EOF */