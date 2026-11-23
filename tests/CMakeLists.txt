# Include the FetchContent module to download GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# This setting is required on Windows to prevent C++ runtime library conflicts
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_astar_tests test_astar.cpp)

# Include the headers from your engine directory
target_include_directories(run_astar_tests PRIVATE ../engine)

# Link your core engine files
target_sources(run_astar_tests PRIVATE ../engine/Astar.cpp ../engine/Grid.cpp)

# Link Google Test (using the fetched target name)
target_link_libraries(run_astar_tests gtest_main)

# Register the test with CTest
add_test(NAME AstarTests COMMAND run_astar_tests)