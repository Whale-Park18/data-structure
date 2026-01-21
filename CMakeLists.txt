cmake_minimum_required(VERSION 3.16)

project(
    main
    VERSION 1.0.0
    DESCRIPTION "TEST"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)