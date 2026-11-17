# PathForge 

A C++17 game AI pathfinding engine I built to practice high-performance systems programming and algorithm optimization. My main goal with this project was to route up to 1,000 concurrent agents within a strict 16ms frame budget (the standard for 60 FPS games). 

To make the engine easier to test and visualize, I wrote native Python bindings using **pybind11** and built a **Django** web app so users can upload maps and watch the pathfinding happen in real-time.

##  What I Learned & Key Features

* **C++ Memory & Performance:** Implemented **A*** and **Jump Point Search (JPS)** algorithms. I used flat 1D arrays instead of 2D grids to improve CPU cache hits and keep memory overhead low.
* **Multithreading:** Built a fixed-size C++ thread pool with per-thread scratch buffers so the engine can route hundreds of agents at the same time without thread locking.
* **Cross-Language Bindings:** Connected the C++ core to Python using **pybind11** and NumPy, allowing Python to drop the Global Interpreter Lock (GIL) during heavy pathfinding batches.
* **Full-Stack Tooling:** Created a Django web interface where users can upload real commercial game maps (sourced from the Moving AI Lab), run the C++ engine in the background, and watch the agents move on an HTML5 canvas.
* **CI/CD & Testing:** Set up GitHub Actions to automatically run Google Test (C++) and pytest (Python) on every commit to ensure new code doesn't break the algorithms or slow down the frame times.

##  Tech Stack

* **Core Engine:** C++17, CMake, scikit-build-core
* **Bindings:** pybind11, NumPy
* **Web App:** Python, Django, HTML5 Canvas, Vanilla JS
* **Testing:** Google Test (gtest), pytest, GitHub Actions

##  Repository Structure

* `/engine` - The C++ core (A*, JPS, Grid loading).
* `/bindings` - pybind11 wrappers connecting C++ to Python.
* `/web` - The Django project for map uploads and simulation replays.
* `/bench` - Scripts to track performance and frame-time metrics.

##  Project Benchmarks
* **Target Budget:** < 16ms for 1,000 agents on a 512x512 grid.
* **Baseline Comparison:** ~40x faster than my pure-Python A* implementation.
* **Maps Used:** Uniform-cost grid maps from the Moving AI Lab dataset.
