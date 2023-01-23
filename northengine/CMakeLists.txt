cmake_minimum_required(VERSION 3.23)

project(NORTH_ENGINE_LANG)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# if compiler is clang or gcc
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -mwindows -Os")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
#    remove -Wlanguage-extension-token
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
endif ()

# static stdlib

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(BIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH})

#add_definitions(-DSDL_MAIN_HANDLED)

# SDL2
set(SDL2_DIR SDL/SDL2/cmake/)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# SDL_image
set(SDL2_image_DIR SDL/SDL_image/cmake/)
find_package(SDL2_image REQUIRED)

if (WIN32)
    set(SDL2_IMAGE_INCLUDE_DIRS SDL/SDL_image/x86_64-w64-mingw32/include)
else ()
    set(SDL2_IMAGE_INCLUDE_DIRS SDL/SDL_image/i686-w64-mingw32/include)
endif ()
include_directories(SDL2_IMAGE_INCLUDE_DIRS)

# SDL_ttf
set(SDL2_ttf_DIR SDL/SDL_ttf/cmake/)
find_package(SDL2_ttf REQUIRED)

if (WIN32)
    set(SDL2_TTF_INCLUDE_DIRS SDL/SDL_ttf/x86_64-w64-mingw32/include)
else ()
    set(SDL2_TTF_INCLUDE_DIRS SDL/SDL_ttf/i686-w64-mingw32/include)
endif ()
include_directories(SDL2_TTF_INCLUDE_DIRS)


# add all files in SOURCE_PATH and INCLUDE_PATH
file(GLOB_RECURSE SOURCES "${SOURCE_PATH}/*.cpp" "${SOURCE_PATH}/*.c" "${INCLUDE_PATH}/*.h")

# remove main.c from SOURCES
list(REMOVE_ITEM SOURCES "${SOURCE_PATH}/main.cpp")

add_library(ne_graphics SHARED ${SOURCES})

add_subdirectory(glad_3.3)

add_subdirectory(glm)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set_target_properties(glm PROPERTIES COMPILE_FLAGS "-Wno-error=deprecated -Wno-deprecated")
endif ()

add_subdirectory(F:/northengine/imgui ${CMAKE_BINARY_DIR}/imgui EXCLUDE_FROM_ALL)

target_include_directories(ne_graphics PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(ne_graphics PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(ne_graphics PUBLIC ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(ne_graphics SDL2::SDL2 SDL2_image::SDL2_image-static ${SDL2_TTF_LIBRARIES} glad glm imgui)

# remove -Werror=unknown-pragmas
add_executable(northengine "${SOURCE_PATH}/main.cpp")
set_target_properties(northengine PROPERTIES COMPILE_FLAGS "-Wno-error=unknown-pragmas")

target_link_libraries(northengine ne_graphics)

target_include_directories(ne_graphics PUBLIC ${INCLUDE_PATH})

