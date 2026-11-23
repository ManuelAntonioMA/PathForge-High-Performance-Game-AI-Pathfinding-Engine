add_executable(run_bench bench_astar.cpp)

# Include headers and sources from the engine
target_include_directories(run_bench PRIVATE ../engine)
target_sources(run_bench PRIVATE ../engine/AStar.cpp ../engine/Grid.cpp)