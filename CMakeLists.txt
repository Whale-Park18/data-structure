# 전역 설정
cmake_minimum_required(VERSION 3.16)

# 프로젝트 설정
project(
    data-structure
    VERSION 1.0.0
    DESCRIPTION "data-structure"
)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Google Test 설정
include(FetchContent) # 외부 라이브러리 관리를 위한 모듈 포함
FetchContent_Declare( # googletest 라이브러리 다운로드 및 설정
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest) # googletest 빌드 실행

# 테스트 활성화(CTest 모듈)
enable_testing()

# 하위 디렉토리 추가
add_subdirectory(dsl)
add_subdirectory(tests)