set(CMAKE_CXX_STANDARD 17)

add_executable(tests dummy_test.cpp)

# Google Test 라이브러리 링크
target_link_libraries(
    tests
    PRIVATE
        gtest_main # google test의 메인 함수 자동 추가
        gtest      # google test 라이브러리 링크
        dsl        # dsl 라이브러리 링크
)

target_include_directories(dsl
    PUBLIC
        ${CMAKE_SOURCEDIR}/dsl/include
)

add_test(NAME tests COMMAND tests)