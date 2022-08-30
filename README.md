# Thumbnailviewer

[![thumbnailviewer](https://github.com/ivorob/thumbnailviewer/actions/workflows/cmake.yml/badge.svg)](https://github.com/ivorob/thumbnailviewer/actions/workflows/cmake.yml)

## macOS building

```
mkdir build
cd build
cmake -G "Unix Makefiles" .. -DCMAKE_PREFIX_PATH=/path/Qt/5.6/clang_64/
cmake --build .
```

## Windows building

use cmake/cmake-gui to configure project
for example (building using nmake):

- run development console for msvc++
- execute the following commands:
```
mkdir build
cd build
cmake -G "NMake Makefiles" .. -DCMAKE_BUILD_TYPE=Release
nmake
```

## Executables

You can download executables from Github Actions for current repository.
