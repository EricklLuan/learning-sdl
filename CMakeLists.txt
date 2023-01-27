cmake_minimum_required(VERSION 3.0.0)
project(learning_sdl VERSION 0.1.0)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB SOURCES "src/*.cpp")

include_directories("include")
add_executable(learning_sdl ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(learning_sdl PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(learning_sdl PRIVATE SDL2_image::SDL2_image)
target_link_libraries(learning_sdl PRIVATE SDL2_ttf::SDL2_ttf) 
