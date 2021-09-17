cmake_minimum_required(VERSION 3.14.5)
project(cppcfw-bench LANGUAGES CXX)

## Enforce out-of-tree build
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

## Force colored output in c compilers
## https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
if(NOT ALREADY_FORCED_COLORED_OUTPUT)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always" CACHE INTERNAL "CMAKE_CXX_FLAGS")
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics" CACHE INTERNAL "CMAKE_CXX_FLAGS")
  endif()
endif()
set(ALREADY_FORCED_COLORED_OUTPUT TRUE CACHE INTERNAL "ALREADY_FORCED_COLORED_OUTPUT")

## Source file
file(GLOB srcs LIST_DIRECTORIES true CONFIGURE_DEPENDS *.cc */*.cc */*.h)
add_executable(bench-program ${srcs})

## Link the original library
add_subdirectory(.. orig)
target_link_libraries(bench-program PRIVATE cppcfwv0)

## Link Celero
include(FetchContent)
option(CELERO_COMPILE_DYNAMIC_LIBRARIES "" OFF)
FetchContent_Declare(Celero GIT_TAG v2.6.0 GIT_REPOSITORY https://github.com/DigitalInBlue/Celero)
FetchContent_MakeAvailable(Celero)
target_link_libraries(bench-program PRIVATE celero)

## Do platform size check
include(CheckTypeSize)
set(CMAKE_EXTRA_INCLUDE_FILES map)
check_type_size("std::map<long, long>" CPPCFW_BENCH___PIMPLS_SIZEOF___MAP LANGUAGE CXX)
set(CMAKE_EXTRA_INCLUDE_FILES)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in include/config.h)
target_include_directories(bench-program PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)

add_custom_target(run COMMAND $<TARGET_FILE:bench-program> DEPENDS bench-program)

