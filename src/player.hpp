#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include "tile.hpp"
#include <vector>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Player {
public:
    Player(glm::vec2 pos, glm::mat4 pojection);
    ~Player();

    void draw() {tile->draw();}

    /// @brief Move the player and collide with any hard tiles
    /// @param collidable_surfaces all tiles that can be collided with
    /// @param delta_time dt to normalize movement speed
    void move(std::vector<Tile*> collidable_surfaces, float delta_time = 1.0f);

    /// @brief returns the position of the center of the player
    glm::vec2 pos() const {return tile->center();}

    /// @brief update the player direction to move left or right
    void move_right() {dir.x += 1.0f;}
    void move_left() {dir.x -= 1.0f;}

    // if possible, have the charact jump
    void jump();
    

private:
    glm::vec2 dir;
    float size;
    const glm::vec3 color{0.7, 0.4, 1.0};
    const float speed = 2.0f * 60.0f;       // 2 tiles per second (in terms of pixels)
    Tile* tile;

    bool airborn;
    bool can_jump;
    bool jumped;
    double time_airborn;


};

Player::Player(glm::vec2 pos, glm::mat4 projection) {
    size = 32.0f;
    dir = glm::vec2(0.0f, 0.0f);
    tile = new Tile(pos.x, pos.y, size, size, projection, color);

    can_jump = true;
    airborn = false;
    jumped = false;
    time_airborn = 0.0;
}

Player::~Player(){
    delete tile;
    tile = nullptr;
}

void Player::move(std::vector<Tile*> collidable_surfaces, float delta_time) {

    // find how far to move x and y
    float dx = dir.x * speed * delta_time;

    const float OFFSET = 1.0f;  // 1 pixel offset

    // Horizontal collisions
    tile->set_left(tile->left() + dx);
    // loop through COLLidable TILEs
    for (Tile*& coll_tile : collidable_surfaces){
        if (colliding(*tile, *coll_tile)){
            if (dir.x > 0.0f){ // moved right, stuck left
                tile->set_right(coll_tile->left() - OFFSET);
            } else if (dir.x < 0.0f){
                tile->set_left(coll_tile->right() + OFFSET);
                
            }
        }
    }

    // reset dir for next move frame
    dir.x = 0.0f;

    // if jumped, use formula -32t + 10 from jump (derivative of -16t^2 + 10t + h)
    // if fell, use similar formula -32t for fall (derivative of  -16t^2 + h)
    double dy = 0.0;
    double t = glfwGetTime() - time_airborn;
    if (jumped){
        dy = (-32 * t) + 14;
    } else {
        dy = (-32 * t);
        std::cout << dy << std::endl;
    }

    dy *= size * delta_time;

    // move the tile vertically
    tile->set_bottom(tile->bottom() + dy);

    bool floor = false;  // check if floor hit, if yes reset fall timer

    for (Tile*& coll_tile : collidable_surfaces){
        if (colliding(*tile, *coll_tile)){


            if (dy > 0.0f){ // moved up, stuck bottom
                tile->set_top(coll_tile->bottom() - OFFSET);

                // disable jumped, so no more upward velocity, reset time 
                jumped = false;
                time_airborn = glfwGetTime();
            }


            else if (dy < 0.0f){
                // grounded, allow jumping again
                can_jump = true;
                jumped = false;

                floor = true;
                time_airborn = glfwGetTime();

                tile->set_bottom(coll_tile->top());
            }
        }
    }

    if (!floor){
        can_jump = false;
    }
    
}

void Player::jump() {
    if (!can_jump){return;}  // early return if no jump
    
    jumped = true;
    can_jump = false;
    airborn = true;
    time_airborn = glfwGetTime();
}

#endif
/* EOF */