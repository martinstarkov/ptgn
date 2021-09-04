cmake_minimum_required(VERSION 3.14)

project(test_app)

file(GLOB_RECURSE FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${FILES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources/" DESTINATION "${PROJECT_BINARY_DIR}/resources")

add_ptgn_to(${PROJECT_NAME})