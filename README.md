# Jetpack Joyride using OpenGL

 Game made using OpenGL 3.3 library

## Build & Run
* `cd build`
* `cmake ..`
* `make all`
* `./jetpack-joyride`

## Controls
* W/Space bar: Jump
* A/Left Arrow key: Left
* D/ Right Arrow key: Right
* S: Shoot water balloons

## Objects implemented
* Player
* Firelines
* Firebeams
* Semi-circular ring
* Coins
* Special power-ups
* Water balloons
* Boomerang
* Seven segment display

## Directory Structure
```
.
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.5.1
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeSystem.cmake
│   │   │   ├── CompilerIdC
│   │   │   │   ├── a.out
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   └── CompilerIdCXX
│   │   │       ├── a.out
│   │   │       └── CMakeCXXCompilerId.cpp
│   │   ├── cmake.check_cache
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── CMakeOutput.log
│   │   ├── CMakeTmp
│   │   ├── feature_tests.bin
│   │   ├── feature_tests.c
│   │   ├── feature_tests.cxx
│   │   ├── graphics_asgn1.dir
│   │   │   ├── build.make
│   │   │   ├── cmake_clean.cmake
│   │   │   ├── CXX.includecache
│   │   │   ├── DependInfo.cmake
│   │   │   ├── depend.internal
│   │   │   ├── depend.make
│   │   │   ├── flags.make
│   │   │   ├── link.txt
│   │   │   ├── progress.make
│   │   │   └── src
│   │   ├── Makefile2
│   │   ├── Makefile.cmake
│   │   ├── progress.marks
│   │   └── TargetDirectories.txt
│   ├── cmake_install.cmake
│   ├── Makefile
│   ├── Sample_GL.frag
│   └── Sample_GL.vert
├── CMakeLists.txt
├── LICENSE
├── README.md
└── src
    ├── ball.cpp
    ├── ball.h
    ├── boomerang.cpp
    ├── boomerang.h
    ├── coin.cpp
    ├── coin.h
    ├── color.cpp
    ├── display.cpp
    ├── display.h
    ├── firebeam.cpp
    ├── firebeam.h
    ├── fireline.cpp
    ├── fireline.h
    ├── floor.cpp
    ├── floor.h
    ├── input.cpp
    ├── magnet.cpp
    ├── magnet.h
    ├── main.cpp
    ├── main.h
    ├── nonedit.cpp
    ├── objects.cpp
    ├── objects.h
    ├── other_handlers.cpp
    ├── ring.cpp
    ├── ring.h
    ├── Sample_GL.frag
    ├── Sample_GL.vert
    ├── timer.cpp
    ├── timer.h
    ├── wballoon.cpp
    └── wballoon.h
```

## Notes

* src directory contains the .cpp files for the game
* run the executable is named 'jetpack-joyride' to play the game
* Do a `make clean` once done playing the game to remove all the compiled object files.

## License
The MIT License https://rohanc.mit-license.org/  
Copyright &copy; 2019 Rohan Chacko <rohanchacko007@gmail.com>
