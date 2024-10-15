cmake_minimum_required (VERSION 3.30)
project (Darktale)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++20")
file(GLOB_RECURSE sources ../src/**.cpp)
add_executable(Darktale
    ${sources}
)
target_include_directories(Darktale PRIVATE ../src)

target_precompile_headers(Darktale PRIVATE ../src/precompiled/precompiled.hpp)
target_link_libraries(Darktale SDL2 SDL2_image SDL2_ttf GL GLEW assimp)
