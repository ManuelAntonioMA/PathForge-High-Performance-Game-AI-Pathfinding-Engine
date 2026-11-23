#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Grid::Grid() : width(0), height(0) {}

bool Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filename << std::endl;
        return false;
    }

    std::string line, key;
    
    // Parse the Moving AI header
    while (std::getline(file, line)) {
        if (line == "map") break; // Grid data starts after this line
        
        std::istringstream ss(line);
        ss >> key;
        if (key == "height") {
            ss >> height;
        } else if (key == "width") {
            ss >> width;
        }
    }

    // Allocate the exact amount of memory needed in one block
    data.assign(width * height, 0);

    // Read the grid characters
    for (int y = 0; y < height; ++y) {
        std::getline(file, line);
        for (int x = 0; x < width && x < (int)line.length(); ++x) {
            char c = line[x];
            // '.' and 'G' are walkable terrains. Everything else is a wall.
            if (c == '.' || c == 'G') {
                data[getIndex(x, y)] = 0; 
            } else {
                data[getIndex(x, y)] = 1; 
            }
        }
    }

    return true;
}