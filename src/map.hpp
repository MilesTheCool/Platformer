/// @brief a std::vector<std::vector<Tile*>> object wrapped into a class
/// meant to make creating several maps per level for each layer of the map
/// would not work on moving objects
#ifndef MAP_CLASS
#define MAP_CLASS

#include <vector>
#include <string>
#include <fstream>
#include <glm/glm.hpp>   // to use vec3 and mat4 needed to initialize tile 
#include "tile.hpp"

class Map {
public:
    Map(std::string file_path,float tile_size, glm::mat4 perspective);
    ~Map();

    void draw(glm::mat4 view);

    void set_view(glm::mat4 view);

    /// @brief  member variables, data being displayed and if error in reading file
    std::vector<std::vector<Tile*>> data;
    bool is_error;

};

Map::Map(std::string file_path, float tile_size, glm::mat4 perspective) {

    // read the file into a temp int vector
    std::vector<std::vector<int>> int_map;

    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        is_error = true;
    }
    else{
        std::vector<int> row;
        while (!file.eof()) {
            char ch = file.peek();
            switch (ch) {
                case -1:   // ignore EOF character
                case ' ':  // ignore spaces and commas
                case ',':
                    ch = file.get();
                    break;

                case '\n':  // push back the row onto the int map
                    ch = file.get();
                    int_map.push_back(row);
                    row = std::vector<int>{};
                    break;

                
                default:
                    if (isdigit(ch)){
                        int num;
                        file >> num;
                        row.push_back(num);
                    }
                    else {
                        std::cerr << "unexpected char in csv @ " << file_path << ": " << ch << " or " << static_cast<int>(ch) << std::endl;
                        is_error = true;
                        ch = file.get();
                    }
                    break;

            }   
        }
        int_map.push_back(row);
    }

    glm::vec3 color_map[] = {
        glm::vec3(0.7f, 0.0f, 0.0f),    // red
        glm::vec3(0.0f, 0.7f, 0.0f),    // green
        glm::vec3(0.7f, 0.7f, 0.0f),    // yellow
        glm::vec3(0.0f, 0.0f, 0.7f),    // blue
        glm::vec3(0.7f, 0.0f, 0.7f),    // magenta
        glm::vec3(0.0f, 0.7f, 0.7f),    // cyan
    };

    // turn the map into a 2d vector with nullptr for blank tiles, flipping it so 0,0 is bottom left
    for (int y = 0; y < int_map.size(); ++y) {
        std::vector<Tile*> new_vec;
        for (int x = 0; x < int_map.at(0).size(); ++x){
            if (int_map[y][x]) {
                // push new tile to the row vector, invert the y position 
                new_vec.push_back(new Tile(static_cast<float>(x) * tile_size, 
                static_cast<float>(int_map.size() - y - 1) * tile_size, tile_size, tile_size, perspective,color_map[int_map[y][x] - 1]));
            }
            else {
                new_vec.push_back(nullptr);
            }
        }
        data.insert(data.begin(), new_vec);
    }
}

Map::~Map(){
    for (auto& row : data) {
            for (Tile*& tile : row){
                if (tile != nullptr){
                    delete tile;
                    tile = nullptr;
                }
            }
        }
}

void Map::draw(glm::mat4 view) {
    for (auto& row : data) {
            for (auto& tile : row){
                if (tile != nullptr){
                    tile->draw(view);
                }
            }
        }
}

void Map::set_view(glm::mat4 view) {
    for (auto& row : data) {
            for (auto& tile : row){
                if (tile != nullptr){
                    //tile->set_view_matrix(view);
                    continue;
                }
            }
        }
}

#endif 
/* EOF */