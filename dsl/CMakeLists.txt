project(
    dsl
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "Data-Structure Library"

)

add_library(dsl
    src/object.cpp
)

# lib 접두사 제거
set_target_properties(dsl PROPERTIES PREFIX "")

target_include_directories(dsl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)