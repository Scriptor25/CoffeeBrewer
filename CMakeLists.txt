cmake_minimum_required(VERSION 3.28)

project(CoffeeBrewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE src src/*.cpp include/*.hpp)

add_executable(CoffeeBrewer ${src})
target_include_directories(CoffeeBrewer PUBLIC include)

install(TARGETS CoffeeBrewer)
