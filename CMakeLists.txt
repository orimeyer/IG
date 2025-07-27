cmake_minimum_required(VERSION 3.0.0)
project(IG VERSION 0.1.0 LANGUAGES C CXX)

# flags for C++
set(MTM_FLAGS_DEBUG "-Wall -pedantic")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_CXX_FLAGS ${MTM_FLAGS_DEBUG})

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build executable
add_executable(my_executable 
    image_loader.cpp 
    grayscale_utils.cpp 
    model.cpp 
    ig.cpp 
    pgm_writer.cpp 
    main.cpp
)
