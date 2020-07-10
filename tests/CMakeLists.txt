cmake_minimum_required(VERSION 3.14.5)
project(cppcfw-test LANGUAGES CXX)

## Enforce out-of-tree build
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

## Enforce c++17 usage when building catch2
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "CMAKE_CXX_STANDARD")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "CMAKE_CXX_STANDARD_REQUIRED") # c++17 is required
set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "CMAKE_CXX_EXTENSIONS") # use -std=c++* instead of -std=gnu++*

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
add_executable(test-program ${srcs})

## Link the original library
add_subdirectory(.. orig)
target_link_libraries(test-program PRIVATE cppcfw)

## Link the necessary catch2
include(FetchContent)
FetchContent_Declare(Catch2 GIT_TAG v3.0.0-preview3 GIT_REPOSITORY https://github.com/catchorg/Catch2.git)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(test-program PRIVATE Catch2::Catch2WithMain)

add_custom_target(run COMMAND $<TARGET_FILE:test-program> --use-colour yes DEPENDS test-program)

