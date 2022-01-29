# Speicfy minimum version

cmake_minimum_required(VERSION 3.16)

# Project name
project(kaipong)

# set cpp standard
set(CMAKE_CXX_STANDARD 17)

# Set output folder
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


# Include directories
include_directories(
   " ${PROJECT_SOURCE_DIR}"
    ${PROJECT_SOURCE_DIR}/src/
    /usr/include/
    /usr/include/SDL2
)



# library path
link_directories(
    /usr/lib/x86_64-linux-gnu/
)


# list of implementation source files
# add each new CPP file here
set( CXX_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/Commons/Commons.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Paddle/Paddle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Ball/Ball.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Collider/Collider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Timer/Timer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/TextField/TextField.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Texture/Texture.cpp


)

# copy asset folder to target
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${EXECUTABLE_OUTPUT_PATH})



# build executable
add_executable(kaipong ${PROJECT_SOURCE_DIR}/src/main.cpp ${CXX_SOURCES})

# link to external libraries (for now we only have main - later we will split into modules)
# TODO: split into modules

target_link_libraries(kaipong 
    libSDL2.so
    libSDL2_image.so
    libSDL2_ttf.so
    libfreetype.so
    libpng.so
)
