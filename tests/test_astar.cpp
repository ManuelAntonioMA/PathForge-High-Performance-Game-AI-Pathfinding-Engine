#include <gtest/gtest.h>
#include "AStar.h"
#include "Grid.h"

// Helper function to build a blank grid for testing
Grid createTestGrid(int width, int height) {
    Grid grid;
    grid.width = width;
    grid.height = height;
    grid.data.assign(width * height, 0); 
    return grid;
}

// Helper function to build walls for testing
void setWall(Grid& grid, int x, int y) {
    grid.data[grid.getIndex(x, y)] = 1; 
}

// Scenario 1: A straight/diagonal shot with no obstacles
TEST(AStarTest, FindsClearPath) {
    Grid grid = createTestGrid(5, 5);
    AStar astar(&grid); 
    
    auto path = astar.findPath(0, 0, 4, 4); 
    
    EXPECT_FALSE(path.empty());
    EXPECT_EQ(path.front().first, 0);  
    EXPECT_EQ(path.front().second, 0);
    EXPECT_EQ(path.back().first, 4);
    EXPECT_EQ(path.back().second, 4);
}

// Scenario 2: Forcing the algorithm to path around a wall
TEST(AStarTest, AvoidsObstacles) {
    Grid grid = createTestGrid(5, 5);
    
    setWall(grid, 2, 0);
    setWall(grid, 2, 1);
    setWall(grid, 2, 2);
    setWall(grid, 2, 3);
    
    AStar astar(&grid);
    auto path = astar.findPath(0, 0, 4, 0);
    
    EXPECT_FALSE(path.empty());
    
    // Ensure none of the nodes in the path are on the wall
    for (const auto& node : path) {
        EXPECT_TRUE(grid.isWalkable(node.first, node.second));
    }
}

// Scenario 3: Target is completely walled off
TEST(AStarTest, ReturnsEmptyOnUnreachable) {
    Grid grid = createTestGrid(5, 5);
    
    setWall(grid, 3, 4);
    setWall(grid, 4, 3);
    setWall(grid, 3, 3);
    
    AStar astar(&grid);
    auto path = astar.findPath(0, 0, 4, 4);
    
    // Should return an empty path indicating failure to reach target
    EXPECT_TRUE(path.empty());
}