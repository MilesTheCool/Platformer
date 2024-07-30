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

    void draw(glm::mat4 view) {tile->draw(view);}

    /// @brief Move the player and collide with any hard tiles
    /// @param collidable_surfaces all tiles that can be collided with
    /// @param delta_time dt to normalize movement speed
    void move(std::vector<Tile*> collidable_surfaces, float delta_time = 1.0f);

    /// @brief returns the position of the center of the player
    glm::vec2 pos() const {return tile->center();}

    /// @brief update the player direction to move left or right
    void move_right() {dir.x += 1.0f;}
    void move_left() {dir.x -= 1.0f;}

    /// @brief if possible, have the character jump
    void jump();

    // void set_view(glm::mat4 view) {tile->set_view_matrix(view);}
    

private:
    glm::vec2 dir;
    float size;
    const glm::vec3 color{0.7, 0.4, 1.0};
    const float speed = 2.0f;       // 2 tiles per second
    Tile* tile;

    bool can_jump;
    bool jumped;
    float time_airborn;


};

Player::Player(glm::vec2 pos, glm::mat4 projection) {
    size = 0.5f;
    dir = glm::vec2(0.0f, 0.0f);
    tile = new Tile(pos.x, pos.y, size, size, projection, color);

    can_jump = true;
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

    const float OFFSET = 0.001f;  // small offset so not overlapping

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

    // using formula -32t + 10 (derivative of -16t&2 + 10t + h) to get per frame dy from 'gravity'
    // if jumped, add vertical velocity, otherwise just falling
    float dy = 0.0;
    time_airborn += delta_time;
    if (jumped){
        dy = (-32 * time_airborn) + 14;
    } else {
        dy = (-32 * time_airborn);
    }

    dy *= size * delta_time;

    // move the tile vertically
    tile->set_bottom(tile->bottom() + dy);


    for (Tile*& coll_tile : collidable_surfaces){
        if (colliding(*tile, *coll_tile)){


            if (dy > 0.0f){ // moved up, stuck bottom
                tile->set_top(coll_tile->bottom() - OFFSET);

                // disable jumped, so no more upward velocity, reset time 
                jumped = false;
                time_airborn = 0.0f;
            }


            else if (dy < 0.0f){
                // grounded, allow jumping again
                can_jump = true;
                jumped = false;
                time_airborn = 0.0f;

                tile->set_bottom(coll_tile->top());
            }
        }
    }

    
}

void Player::jump() {
    if (!can_jump){return;}  // early return if no jump
    
    jumped = true;
    //can_jump = false;
    time_airborn = 0.0f;
}

#endif
/* EOF */