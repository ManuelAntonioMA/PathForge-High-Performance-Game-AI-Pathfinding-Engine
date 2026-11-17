#include "AStar.h"
#include <queue>
#include <cmath>
#include <algorithm>

// Used in the priority queue (Min-Heap)
struct OpenNode {
    int index;
    float f;
    bool operator>(const OpenNode& other) const {
        return f > other.f; 
    }
};

AStar::AStar(const Grid* g) : grid(g), current_generation(0) {
    // Pre-allocate memory once for the entire grid
    nodes.resize(grid->width * grid->height);
}

inline float AStar::getOctileDistance(int x1, int y1, int x2, int y2) const {
    int dx = std::abs(x1 - x2);
    int dy = std::abs(y1 - y2);
    // 0.41421356f is roughly (sqrt(2) - 1)
    return std::max(dx, dy) + 0.41421356f * std::min(dx, dy);
}

std::vector<std::pair<int, int>> AStar::findPath(int start_x, int start_y, int goal_x, int goal_y) {
    std::vector<std::pair<int, int>> path;
    
    if (!grid->isWalkable(start_x, start_y) || !grid->isWalkable(goal_x, goal_y)) {
        return path; 
    }

    current_generation++; // O(1) grid reset!
    
    // Min-heap for the open list
    std::priority_queue<OpenNode, std::vector<OpenNode>, std::greater<OpenNode>> openList;
    
    int startIndex = grid->getIndex(start_x, start_y);
    int goalIndex = grid->getIndex(goal_x, goal_y);
    
    nodes[startIndex].g = 0;
    nodes[startIndex].f = getOctileDistance(start_x, start_y, goal_x, goal_y);
    nodes[startIndex].parent_index = -1;
    nodes[startIndex].generation = current_generation;
    
    openList.push({startIndex, nodes[startIndex].f});
    
    const float SQRT2 = 1.41421356f;
    struct Dir { int dx, dy; float cost; };
    Dir dirs[8] = {
        {0, -1, 1.0f}, {1, 0, 1.0f}, {0, 1, 1.0f}, {-1, 0, 1.0f}, // Cardinal
        {1, -1, SQRT2}, {1, 1, SQRT2}, {-1, 1, SQRT2}, {-1, -1, SQRT2} // Diagonal
    };

    while (!openList.empty()) {
        OpenNode current = openList.top();
        openList.pop();
        
        // Skip stale nodes in the priority queue
        if (current.f > nodes[current.index].f) continue;
        
        if (current.index == goalIndex) {
            // Goal found! Reconstruct path by walking backwards
            int curr = goalIndex;
            while (curr != -1) {
                int cx = curr % grid->width;
                int cy = curr / grid->width;
                path.push_back({cx, cy});
                curr = nodes[curr].parent_index;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        int cx = current.index % grid->width;
        int cy = current.index / grid->width;
        
        for (const auto& dir : dirs) {
            int nx = cx + dir.dx;
            int ny = cy + dir.dy;
            
            if (!grid->isWalkable(nx, ny)) continue;
            
            // Prevent corner cutting
            if (dir.dx != 0 && dir.dy != 0) {
                if (!grid->isWalkable(cx + dir.dx, cy) || !grid->isWalkable(cx, cy + dir.dy)) {
                    continue;
                }
            }
            
            int nIndex = grid->getIndex(nx, ny);
            float new_g = nodes[current.index].g + dir.cost;
            
            // If node is unvisited THIS generation, or we found a faster path to it
            if (nodes[nIndex].generation != current_generation || new_g < nodes[nIndex].g) {
                nodes[nIndex].g = new_g;
                nodes[nIndex].f = new_g + getOctileDistance(nx, ny, goal_x, goal_y);
                nodes[nIndex].parent_index = current.index;
                nodes[nIndex].generation = current_generation;
                
                openList.push({nIndex, nodes[nIndex].f});
            }
        }
    }
    
    return path; // Return empty if no path exists
}