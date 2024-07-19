cmake_minimum_required(VERSION 3.20)
project(DrawingExamples)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Find the required packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    #${CMAKE_SOURCE_DIR}/src/Components/DDA
)

# Source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/Components/DDA/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Components/Circle/*.cpp"
#    "${CMAKE_SOURCE_DIR}/src/Components/Bresenham/*.cpp"
#    "${CMAKE_SOURCE_DIR}/src/Components/House/*.cpp"
#    "${CMAKE_SOURCE_DIR}/src/Components/Car/*.cpp"
)

# Header files
file(GLOB_RECURSE HEADERS
    "${CMAKE_SOURCE_DIR}/src/Components/DDA/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/Components/Circle/*.hpp"
#    "${CMAKE_SOURCE_DIR}/src/Components/Bresenham/*.hpp"
#    "${CMAKE_SOURCE_DIR}/src/Components/House/*.hpp"
#    "${CMAKE_SOURCE_DIR}/src/Components/Car/*.hpp"
)

add_executable(Drawing 
    ${SOURCES}
    ${HEADERS}
)

# Link the libraries
target_link_libraries(Drawing PRIVATE
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw
)
