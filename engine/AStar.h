#pragma once
#include "Grid.h"
#include <vector>
#include <cstdint>

// Stores path data. We use one massive array of these.
struct PathNode {
    float g = 0.0f;
    float f = 0.0f;
    int parent_index = -1;
    uint32_t generation = 0; // The magic counter to avoid clearing memory
};

class AStar {
private:
    const Grid* grid;
    std::vector<PathNode> nodes;
    uint32_t current_generation;

    // Octile heuristic: Perfect for 8-directional movement
    inline float getOctileDistance(int x1, int y1, int x2, int y2) const;

public:
    AStar(const Grid* grid);
    
    // Returns a list of coordinates forming the path
    std::vector<std::pair<int, int>> findPath(int start_x, int start_y, int goal_x, int goal_y);
};