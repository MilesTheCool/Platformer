
#ifndef TILE_CLASS
#define TILE_CLASS

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"


class Tile {
public:

    Tile(float left = 0.0f, float bottom = 0.0f, float width = 0.0f, float height = 0.0f, 
         glm::mat4 projection = glm::mat4(1.0f), glm::vec3 tile_color = glm::vec3(1.0f));

    ~Tile();

    /// @brief Draw the tile to the screen
    void draw(glm::mat4 view);

    /// @brief Checks if two existing tiles are overlapping, return true if they are
    friend bool colliding(Tile& tile_one, Tile& tile_two);


    /* SET SHADER UNIFORMS */

    /// @brief Calculate and set the transform matrix given the position 
    /// run once on initialization, and when repositioned
    /// for static tiles, this won't ever need to be called again
    void set_transform_matrix();

    /// @brief set the projection matrix being used. 
    /// called once when started, otherwise only run when called
    void set_projection_matrix(glm::mat4 projection) {shader->setMat4("projection", projection);}

    /// @brief set the color uniform for the tile
    /// run once at start, only needs to be run again if color changes
    /// @param color vec3 of the color of the tile
    void set_color(glm::vec3 color) {shader->setVec3("color", color);}

    /// @brief set the view matrix being used for the camera
    void set_view_matrix(glm::mat4 view) {shader->setMat4("view", view);}

    /* SIZE ACCESS */
    /// @brief size in coordinate space of the tile
    glm::vec2 tile_size() const {return size;}
    float width() const {return size.x;}
    float height() const {return size.y;}
    
    /* POSITION ACCESS*/
    // 5 main points
    glm::vec2 bottom_left() const {return pos_bottomleft;}
    glm::vec2 bottom_right() const {return glm::vec2(pos_bottomleft.x + width(), pos_bottomleft.y);}
    glm::vec2 top_left() const {return glm::vec2(pos_bottomleft.x, pos_bottomleft.y + height());}
    glm::vec2 top_right() const {return glm::vec2(pos_bottomleft.x + width(), pos_bottomleft.y + height());}
    glm::vec2 center() const {return glm::vec2(pos_bottomleft.x + (width() / 2.0f), pos_bottomleft.y + (height() / 2.0f));}

    // y - values
    float top() const {return pos_bottomleft.y + height();}
    float mid_y() const {return pos_bottomleft.y + (height() / 2.0f);}
    float bottom() const {return pos_bottomleft.y;}
    
    // x - values
    float left() const {return pos_bottomleft.x;}
    float mid_x() const {return pos_bottomleft.x + (width() / 2.0f);}
    float right() const {return pos_bottomleft.x + width();}

    /* POSITION SETTING */
    // 5 main points
    void set_bottom_left(glm::vec2 pos)  {pos_bottomleft = pos; set_transform_matrix();} 
    void set_bottom_right(glm::vec2 pos) {pos_bottomleft = glm::vec2(pos.x - width(), pos.y); set_transform_matrix();} 
    void set_top_left(glm::vec2 pos) {pos_bottomleft = glm::vec2(pos.x, pos.y - height()); set_transform_matrix();} 
    void set_top_right(glm::vec2 pos) {pos_bottomleft = glm::vec2(pos.x - width(), pos.y - height()); set_transform_matrix();} 
    void set_center(glm::vec2 pos) {pos_bottomleft = glm::vec2(pos.x - (width() / 2.0f), pos.y - (height() / 2.0f)); set_transform_matrix();}

    // y - values
    void set_top(float y) {pos_bottomleft = glm::vec2(left(), y - height()); set_transform_matrix();}
    void set_mid_y(float y) {pos_bottomleft = glm::vec2(left(), y - (height() / 2.0f)); set_transform_matrix();}
    void set_bottom(float y) {pos_bottomleft = glm::vec2(left(), y); set_transform_matrix();}

    // x - values
    void set_right(float x) {pos_bottomleft = glm::vec2(x - width(), bottom()); set_transform_matrix();}
    void set_mid_x(float x) {pos_bottomleft = glm::vec2(x - (width() / 2.0f), bottom()); set_transform_matrix();}
    void set_left(float x) {pos_bottomleft = glm::vec2(x, bottom()); set_transform_matrix();}
    


private:

    
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;

    glm::vec2 size;    // pixel size (width, height) of the tile

    glm::vec2 pos_bottomleft;   // coordinate in pixel where the bottom left of the tile is placed

    Shader* shader;
};

Tile::Tile(float left, float bottom, float width, float height, 
         glm::mat4 projection, glm::vec3 tile_color) {

    // set member variables
    size = glm::vec2(width, height);
    pos_bottomleft = glm::vec2(left, bottom);


    // create Vertex Array
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    unsigned int indeces[] = {
        0, 1, 2,
        2, 3, 1
    };

    // set VAO VBO EBO
    VAO = 0;
    VBO = 0;
    EBO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);
    

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO for now

    
    // Create Shader

    shader = new Shader("/home/miles/dev/platformer/src/tile_vertex.glsl","/home/miles/dev/platformer/src/tile_fragment.glsl");
    shader->use();

    // Set Uniforms
    set_projection_matrix(projection);
    set_color(tile_color);
    set_transform_matrix();
    set_view_matrix(glm::mat4(1.0f));
    glUseProgram(0);
}

Tile::~Tile() {
    // destroy shader
    delete shader;

    // unnallocate opengl stuff
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Tile::draw(glm::mat4 view) {

    glBindVertexArray(VAO);
    shader->use();

    // set the view matrix as the camera moves
    set_view_matrix(view);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Tile::set_transform_matrix() {

    shader->use();

    glm::mat4 transform{1.0f};
    transform = glm::translate(transform, glm::vec3(left(), bottom(), 0.0f));
    transform = glm::scale(transform, glm::vec3(width(), height(), 1.0f));
    shader->setMat4("trans", transform);

    glUseProgram(0);
}

bool colliding(Tile& tile_one, Tile& tile_two) {
    // no collision with a nullptr
    if(&tile_one == nullptr || &tile_two == nullptr) {return false;}
    // if same tile, return false
    if (&tile_one == &tile_two){return false;}

    // check horizontal bounds
    if (tile_one.left() >= tile_two.right() || tile_one.right() <= tile_two.left()) {return false;}  // not overlapping x

    // check vertical bounds
    if (tile_one.top() < tile_two.bottom() || tile_one.bottom() >= tile_two.top()) {return false;} // not overlapping y

    // if not early return, then two separate existing tiles are overlapping x and y
    return true;
}

#endif
/* EOF */