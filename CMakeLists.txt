cmake_minimum_required(VERSION 3.14.5)
project (cppcfwv0 LANGUAGES CXX)

file(GLOB_RECURSE hdrs LIST_DIRECTORIES true CONFIGURE_DEPENDS src/cppcfwv0/*.h)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${hdrs})
target_include_directories(${PROJECT_NAME} INTERFACE src)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
