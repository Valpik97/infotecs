# Logger Library & Demo Application

## Overview
A C++17 logger library (static/shared) and a multithreaded demo app. Log messages with levels (Error, Warning, Info) to a file. Thread-safe, clean CMake build.

---

## Requirements
- C++17 compiler
- CMake >= 3.10
- GCC (Linux) or MinGW/MSVC (Windows)

---

## Build Instructions

### Linux (GCC)
1. Install dependencies:
   ```sh
   sudo apt update && sudo apt install build-essential cmake
   ```
2. Clone and enter the repo:
   ```sh
   git clone <your_repo_url>
   cd Bibl
   ```
3. Create build directory and configure:
   - **Shared library:**
     ```sh
     mkdir build && cd build
     cmake -DUSE_SHARED=ON .. -DCMAKE_BUILD_TYPE=Release
     ```
   - **Static library:**
     ```sh
     mkdir build && cd build
     cmake -DUSE_SHARED=OFF .. -DCMAKE_BUILD_TYPE=Release
     ```
4. Build:
   ```sh
   make
   ```

### Windows (MinGW or MSVC)
1. Install CMake and a C++17 compiler (MinGW or MSVC).
2. Clone and enter the repo:
   ```sh
   git clone <your_repo_url>
   cd Bibl
   ```
3. Create build directory and configure:
   - **Shared library:**
     ```sh
     mkdir build
     cd build
     cmake -DUSE_SHARED=ON .. -G "MinGW Makefiles"
     ```
   - **Static library:**
     ```sh
     mkdir build
     cd build
     cmake -DUSE_SHARED=OFF .. -G "MinGW Makefiles"
     ```
4. Build:
   ```sh
   mingw32-make
   ```

---

## How to Use the App
1. **Build** as above.
2. **Run the app:**
   - On Linux:
     ```sh
     ./app/logger_app <logfile> [default_level]
     ```
   - On Windows:
     ```sh
     app\logger_app.exe <logfile> [default_level]
     ```
   - `<logfile>`: Path to log file (e.g., `log.txt`)
   - `[default_level]`: (Optional) `error`, `warning`, or `info` (default: `info`)
3. **Interact:**
   - Enter a message (or `exit` to quit)
   - Enter a level (`error`, `warning`, `info`) or press Enter for default
   - Repeat as needed

---