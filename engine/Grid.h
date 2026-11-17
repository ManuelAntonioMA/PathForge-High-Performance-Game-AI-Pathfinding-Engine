#pragma once
#include <vector>
#include <string>
#include <cstdint>

class Grid {
public:
    int width;
    int height;
    std::vector<uint8_t> data; // 1D array for cache-friendly memory

    Grid();
    
    // Parses a Moving AI .map file
    bool loadFromFile(const std::string& filename);
    
    // Math to convert 2D coordinates into our 1D array index
    inline int getIndex(int x, int y) const {
        return y * width + x;
    }
    
    // Checks if a coordinate is within bounds and not a wall
    inline bool isWalkable(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) return false;
        return data[getIndex(x, y)] == 0;
    }
};