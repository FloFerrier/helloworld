# README
## Build on Windows
```bash
$ cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -B build
$ cmake --build build
$ cd build
$ ctest -C Debug
```