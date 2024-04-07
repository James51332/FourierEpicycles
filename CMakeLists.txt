cmake_minimum_required(VERSION 3.20)

# Basic Info
project(fft)

# Set the C++ Standard
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Define the executable for the program
add_executable(fft src/art.cpp
                   src/art.h
                   src/main.cpp
                   src/complex.h
                   src/transform.cpp
                   src/transform.h)

target_include_directories(fft PRIVATE "src")

add_subdirectory(vendor/vision)

# Link to the SDL library
target_link_libraries(fft 
                        PUBLIC
                          Vision)