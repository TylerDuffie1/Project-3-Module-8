Corner Grocer - Item Tracking (C++)

Files:
- src/ItemTracker.cpp, include/ItemTracker.h: class that loads items from input, counts them with std::map,
  writes frequency.dat, prints reports and histogram.
- src/main.cpp: menu-driven UI (options 1-4).
- data/CS210_Project_Three_Input_File.txt: sample input list (one item per line is fine).

Build (Codio or any g++):
  g++ -std=c++17 -Isrc -Iinclude src/*.cpp -o CornerGrocer
  ./CornerGrocer

Visual Studio (Windows):
  1) Create a new "Console App" (C++). Name it CornerGrocer.
  2) In Solution Explorer, add existing items: src\ItemTracker.cpp and src\main.cpp.
  3) Add a Header File include\ItemTracker.h to the project (or Add Existing).
  4) Right-click the project > Properties > C/C++ > General > Additional Include Directories: add 'include'.
  5) Create a folder 'data' next to the .exe (Project > Properties > General > Output Directory), then copy
     data\CS210_Project_Three_Input_File.txt there. At runtime the program expects 'data/CS210_Project_Three_Input_File.txt'.
  6) Build and Run (Ctrl+F5). frequency.dat will be created in the working directory.

Export ZIP from Visual Studio:
  File > Export Template or follow your course "CS Visual Studio Export Tutorial" to zip the entire solution folder.

Notes:
- Input normalization: case-insensitive; leading/trailing punctuation is stripped.
- frequency.dat is overwritten each run.
- Menu input is validated; only 1-4 accepted.
