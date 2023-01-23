cmake_minimum_required(VERSION 3.23)

project(NORTH_ENGINE_LANG)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(BIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH})

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# find_package(LLVM REQUIRED CONFIG)
#
# message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
# message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
#
# include_directories(${LLVM_INCLUDE_DIRS})
# add_definitions(${LLVM_DEFINITIONS})
#
# llvm_map_components_to_libnames(llvm_libs support core irreader)

# add all files in SOURCE_PATH and INCLUDE_PATH
file(GLOB_RECURSE SOURCES "${SOURCE_PATH}/*.c" "${INCLUDE_PATH}/*.h")

# remove main.c from SOURCES
list(REMOVE_ITEM SOURCES "${SOURCE_PATH}/main.c")

add_library(north_engine_lang SHARED ${SOURCES})

add_executable(NEC "${SOURCE_PATH}/main.c")

target_link_libraries(NEC north_engine_lang)

target_include_directories(north_engine_lang PUBLIC ${INCLUDE_PATH})

