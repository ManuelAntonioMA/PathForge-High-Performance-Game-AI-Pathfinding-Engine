#include <iostream>
#include <chrono>
#include <vector>
#include "AStar.h"
#include "Grid.h"

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: ./run_bench <map_file> <start_x> <start_y> <goal_x> <goal_y>\n";
        return 1;
    }

    std::string mapFile = argv[1];
    int start_x = std::stoi(argv[2]);
    int start_y = std::stoi(argv[3]);
    int goal_x = std::stoi(argv[4]);
    int goal_y = std::stoi(argv[5]);

    Grid grid;
    if (!grid.loadFromFile(mapFile)) {
        return 1;
    }

    std::cout << "Loaded map: " << mapFile << " (" << grid.width << "x" << grid.height << ")\n";

    AStar astar(&grid);
    
    // Number of iterations for a stable average
    const int iterations = 100;
    std::vector<std::pair<int, int>> path;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        path = astar.findPath(start_x, start_y, goal_x, goal_y);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    
    double avg_ms = (total_duration / 1000.0) / iterations;

    if (path.empty()) {
        std::cout << "Result: No path found.\n";
    } else {
        std::cout << "Result: Path found with length " << path.size() << " steps.\n";
    }
    std::cout << "Average time over " << iterations << " runs: " << avg_ms << " ms\n";

    return 0;
}