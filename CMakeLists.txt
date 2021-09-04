cmake_minimum_required(VERSION 3.14)

project(ptgn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
set(SUPPORT_OGG ON)

FetchContent_Declare(sdl2
				GIT_REPOSITORY https://github.com/martinstarkov/SDL.git
                GIT_TAG main)
FetchContent_MakeAvailable(sdl2)

FetchContent_Declare(sdl2_image
				GIT_REPOSITORY https://github.com/martinstarkov/SDL_image.git
                GIT_TAG main)
FetchContent_MakeAvailable(sdl2_image)

FetchContent_Declare(sdl2_mixer
				GIT_REPOSITORY https://github.com/martinstarkov/SDL_mixer.git
                GIT_TAG master)
FetchContent_MakeAvailable(sdl2_mixer)

FetchContent_Declare(sdl2_ttf
				GIT_REPOSITORY https://github.com/martinstarkov/SDL_ttf.git
                GIT_TAG main)
FetchContent_MakeAvailable(sdl2_ttf)

set(PTGN_DIR     "${CMAKE_CURRENT_SOURCE_DIR}")
set(PTGN_SRC_DIR "${PTGN_DIR}/src")

file(GLOB_RECURSE PTGN_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false 
     "${PTGN_SRC_DIR}/*.h"
	 "${PTGN_SRC_DIR}/*.cpp")

include_directories(${PTGN_SRC_DIR})

add_library(${PROJECT_NAME} STATIC ${PTGN_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static ${ZLIB_LIBRARY} ${PNG_LIBRARY} SDL2_image SDL2_mixer SDL2_ttf)

target_include_directories(${PROJECT_NAME} INTERFACE ${PTGN_SRC_DIR})

function(add_ptgn_to TARGET)
    target_link_libraries(${TARGET} PRIVATE ptgn)
    set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 17)
endfunction()

option(PTGN_TEST_APP "PTGN_TEST_APP" ON)

if(PTGN_TEST_APP)
    add_subdirectory(test_app)
endif()