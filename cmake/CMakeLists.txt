cmake_minimum_required (VERSION 2.6) 
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Release)
option(USE_CLANG "use clang" ON) # OFF is the default

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

if(USE_CLANG)
 set(CMAKE_C_COMPILER /usr/bin/clang-3.8)
 set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.8")
 set(CMAKE_CXX_FLAGS_RELEASE "-g -O2 -fno-omit-frame-pointer -march=opteron -fsanitize=address -std=c++14")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
 set(CMAKE_CXX_LINK_FLAGS "-g -fsanitize=address")
else()
 set(CMAKE_CXX_COMPILER "g++")
 set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ggdb -std=c++14")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()


project(ALLCPP)

message(STATUS ${CMAKE_CURRENT_BINARY_DIR})

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR}/../)
include_directories(${PROJECT_ROOT_DIR})

set(CMAKE_EXE_LINKER_FLAGS "-lpthread -llzo2 -lssl -lsnappy")
link_directories(${PROJECT_ROOT_DIR}/lib/)

add_subdirectory(../tests tests)
 