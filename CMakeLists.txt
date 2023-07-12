cmake_minimum_required(VERSION 3.5)
project(GameOfLife)

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)

# Packages
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include/)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
