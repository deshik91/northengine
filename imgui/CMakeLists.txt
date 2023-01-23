project(imgui)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-missing-field-initializers")
endif ()

#sources
file(GLOB_RECURSE SOURCES
        "imgui/*.cpp"
        "imgui/*.h"
        "imgui/*.hpp"
        "imgui/*.inl"
        "imgui/*.c"
        )


#includes
include_directories(imgui)

# ../northengine_graphics/SDL/SDL2/cmake
set(SDL2_DIR "../northengine/SDL/SDL2/cmake")
find_package(SDL2 REQUIRED)

#target
add_library(imgui STATIC ${SOURCES})

target_link_libraries(imgui SDL2)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
