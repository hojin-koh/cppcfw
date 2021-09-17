cmake_minimum_required(VERSION 3.14.5)
project (cppcfwv0 LANGUAGES CXX)

file(GLOB_RECURSE hdrs LIST_DIRECTORIES true CONFIGURE_DEPENDS src/cppcfwv0/*.h)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${hdrs})
target_include_directories(${PROJECT_NAME} INTERFACE src)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

## Do platform size check
include(CheckTypeSize)
set(CMAKE_EXTRA_INCLUDE_FILES deque forward_list string map utility)
check_type_size("std::deque<std::string>::iterator" CPPCFWV0___PIMPLS_SIZEOF___ITERATOR LANGUAGE CXX)
check_type_size("std::forward_list<std::string>" CPPCFWV0___PIMPLS_SIZEOF___LIST_STRING LANGUAGE CXX)
check_type_size("std::map<std::string, std::pair<std::deque<std::string>, std::string>>" CPPCFWV0___PIMPLS_SIZEOF___MAP_PAIR_STRING LANGUAGE CXX)
set(CMAKE_EXTRA_INCLUDE_FILES)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/cppcfwv0/config/config.h.in include/cppcfwv0/config/config.h)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)
