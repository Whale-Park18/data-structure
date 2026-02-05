#include <gtest/gtest.h>

#include <array.hpp>

#include <algorithm>

template<typename _T, std::size_t _N>
static bool is_zero(const dsl::array<_T, _N>& array)
{
    return std::all_of(
        array.data(), array.data() + array.size(),
        [](int val) { return val == 0; }
    );
}

template<typename _T, std::size_t _N>
static bool is_equal(const dsl::array<_T, _N>& a, const dsl::array<_T, _N>& b)
{
    return std::equal(
        a.data(), a.data() + a.size(),
        b.data(), b.data() + b.size()
    );
}

// 기본 생성자
TEST(ArrayTest, DefaultConstructor)
{
    dsl::array<int, 5> array;

    // 1. 원소: 0, 0, 0, 0, 0
    // 2. 크기: 5
    EXPECT_TRUE(is_zero(array));
    EXPECT_EQ(array.size(), 5);
}

// 복사 생성자
TEST(ArrayTest, CopyConstructor)
{
    dsl::array<int, 5> origin{ 1, 2, 3, 4, 5 };
    dsl::array<int, 5> copy = origin;

    // 1. 원소: 1, 2, 3, 4, 5
    // 2. 크기: 5
    EXPECT_TRUE(is_equal(origin, copy));
    EXPECT_EQ(copy.size(), 5);
}

// 이동 생성자
TEST(ArrayTest, MoveConstructor)
{
    dsl::array<int, 5> origin{ 1, 2, 3, 4, 5 };
    dsl::array<int, 5> moved(std::move(origin));

    // 1. 원소: 0, 0, 0, 0, 0
    // 2. 크기: 5
    EXPECT_TRUE(is_zero(origin));
    EXPECT_EQ(origin.size(), 5);

    // 1. 원소: 1, 2, 3, 4, 5
    // 2. 크기: 5
    EXPECT_TRUE(is_equal(moved, dsl::array<int, 5>{ 1, 2, 3, 4, 5 }));
    EXPECT_EQ(moved.size(), 5);
}

// 초기화 리스트 생성자
TEST(ArrayTest, InitializerListConstructor)
{
    dsl::array<int, 5> array{ 5, 4, 3, 2, 1 };

    // 1. 원소: 5, 4, 3, 2, 1
    // 2. 크기: 5
    EXPECT_TRUE(is_equal(array, dsl::array<int, 5>{ 5, 4, 3, 2, 1 }));
    EXPECT_EQ(array.size(), 5);
}

// 복사 배정 연산자
TEST(ArayTest, CopyAssignment)
{
    dsl::array<int, 5> origin{ 1, 2, 3, 4, 5 };
    dsl::array<int, 5> copy;

    copy = origin;

    // 1. 원소: 1, 2, 3, 4, 5
    // 2. 크기: 5
    EXPECT_TRUE(is_equal(origin, copy));
    EXPECT_EQ(copy.size(), 5);
}

// 이동 배정 연산자
TEST(ArrayTest, MoveAssignment)
{
    dsl::array<int, 5> origin{ 1, 2, 3, 4, 5 };
    dsl::array<int, 5> moved;

    moved = std::move(origin);

    // 1. 원소: 0, 0, 0, 0, 0
    // 2. 크기: 5
    EXPECT_TRUE(is_zero(origin));
    EXPECT_EQ(origin.size(), 5);

    // 1. 원소: 1, 2, 3, 4, 5
    // 2. 크기: 5
    EXPECT_TRUE(is_equal(moved, dsl::array<int, 5>{ 1, 2, 3, 4, 5 }));
    EXPECT_EQ(moved.size(), 5);
}

// 요소 접근, at
TEST(ArrayTest, At)
{
    dsl::array<int, 3> array{ 10, 20, 30 };
    
    EXPECT_TRUE(is_equal(array, dsl::array<int, 3>{ 10, 20, 30 }));
    EXPECT_THROW(array.at(3), std::out_of_range);
}

// 요소 접근, operator[]
TEST(ArrayTest, OperatorBracket)
{
    dsl::array<int, 3> array{ 10, 20, 30 };

    EXPECT_TRUE(is_equal(array, dsl::array<int, 3>{ 10, 20, 30 }));
}

// 요소 접근, front
TEST(ArrayTest, Front)
{
    dsl::array<int, 3> array{ 10, 20, 30 };

    EXPECT_EQ(array.front(), 10);
}

// 요소 접근, back
TEST(ArrayTest, Back)
{
    dsl::array<int, 3> array{ 10, 20, 30 };

    EXPECT_EQ(array.back(), 30);
}

// 요소 접근, data
TEST(ArrayTest, Data)
{
    // 이거 어케 테스트 하냐
    EXPECT_TRUE(true);
}

// 크기, empty
TEST(ArrayTest, Empty)
{
    dsl::array<int, 0> zero{};
    dsl::array<int, 1> not_zero{};

    EXPECT_TRUE(zero.empty());
    EXPECT_FALSE(not_zero.empty());
}

// 크기, size
TEST(ArrayTest, Size)
{
    dsl::array<int, 0> zero{};
    dsl::array<int, 3> three{};
    dsl::array<char, 5> five{};

    EXPECT_EQ(zero.size(), 0);
    EXPECT_EQ(three.size(), 3);
    EXPECT_EQ(five.size(), 5);
}

// 기타 연산, fill
TEST(ArrayTest, Fill)
{
    dsl::array<int, 5> array{ 1, 2, 3, 4, 5 };
    array.fill(0);

    EXPECT_TRUE(is_zero(array));
}

// 기타 연산, swap
TEST(ArrayTest, Swap)
{
    dsl::array<int, 5> array1{ 1, 2, 3, 4, 5 };
    dsl::array<int, 5> array2{ 5, 4, 3, 2, 1 };

    array1.swap(array2);
    EXPECT_TRUE(is_equal(array1, dsl::array<int, 5>{ 5, 4, 3, 2, 1 }));
    EXPECT_TRUE(is_equal(array2, dsl::array<int, 5>{ 1, 2, 3, 4, 5 }));
}