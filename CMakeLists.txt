cmake_minimum_required(VERSION 3.10)

project(GbEmulatorCpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(GbEmulatorCpp ${SOURCES})
target_link_libraries(GbEmulatorCpp ${SDL2_LIBRARIES})
target_link_libraries(GbEmulatorCpp ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(GbEmulatorCpp ${SDL2_TTF_LIBRARIES})
