# macOS building
    cmake . -DCMAKE_PREFIX_PATH=/Users/vim/Qt/5.6/clang_64/
    make
# windows building
use cmake/cmake-gui to configure project
for example (building using nmake):
run development console for msvc++
    cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
    nmake
