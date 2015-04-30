cmake_minimum_required(VERSION 3.1)
project(SFMLPaddleball)

add_subdirectory(doc)

# Set C++ build options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Enable debug symbols by default
if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set verison information in a config.h.in
set(SFMLPaddleball_VERSION_MAJOR 0)
set(SFMLPaddleball_VERSION_MINOR 1)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

# Configure SFML build
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_ROOT "C:/Program Files/SFML")

# Detect and find SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics window network audio system)


# Set up non-SFML includes
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

# Set up executable.
set(SOURCE_FILES src/main.cpp src/game.cpp src/ball.cpp src/paddle.cpp)
set(EXECUTABLE_NAME "SFMLPaddleball")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Try to include and link SFML libraries
if (SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Copy assets folder to build directory.
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_SOURCE_DIR}/assets
                   ${PROJECT_BINARY_DIR})

install(TARGETS ${EXECUTABLE_NAME}
        DESTINATION bin)
