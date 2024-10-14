cmake_minimum_required (VERSION 3.30)
project (JourneyOfDreams)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++20")
file(GLOB_RECURSE sources ../src_client/**.cpp)
add_executable(JourneyOfDreams
    ${sources}
)
target_include_directories(JourneyOfDreams PRIVATE ../src_client)

target_precompile_headers(JourneyOfDreams PRIVATE ../src_client/Precompiled/Precompiled.hpp)
target_link_libraries(JourneyOfDreams SDL2 SDL2_image SDL2_ttf GL GLEW)
