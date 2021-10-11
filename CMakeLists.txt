cmake_minimum_required(VERSION 3.14)

project(library_name)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
set(SUPPORT_OGG ON)

FetchContent_Declare(sdl2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git GIT_TAG main)
FetchContent_MakeAvailable(sdl2)

FetchContent_Declare(sdl2_image GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git GIT_TAG main)
FetchContent_MakeAvailable(sdl2_image)

FetchContent_Declare(sdl2_mixer GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git GIT_TAG master)
FetchContent_MakeAvailable(sdl2_mixer)

FetchContent_Declare(sdl2_ttf GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git GIT_TAG main)
FetchContent_MakeAvailable(sdl2_ttf)

set(LIBRARY_NAME_DIR     "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIBRARY_NAME_SRC_DIR "${LIBRARY_NAME_DIR}/src")

file(GLOB_RECURSE LIBRARY_NAME_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false 
     "${LIBRARY_NAME_SRC_DIR}/*.h"
     "${LIBRARY_NAME_SRC_DIR}/*.cpp")

include_directories(${LIBRARY_NAME_SRC_DIR})

add_library(${PROJECT_NAME} STATIC ${LIBRARY_NAME_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static ${ZLIB_LIBRARY} ${PNG_LIBRARY} SDL2_image SDL2_mixer SDL2_ttf)

target_include_directories(${PROJECT_NAME} INTERFACE ${LIBRARY_NAME_SRC_DIR})

function(add_library_name_to TARGET)
    target_link_libraries(${TARGET} PRIVATE library_name)
    set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 17)
endfunction()

option(LIBRARY_TEST_APP "LIBRARY_TEST_APP" ON)

if(LIBRARY_TEST_APP)
    add_subdirectory(test_app)
endif()
