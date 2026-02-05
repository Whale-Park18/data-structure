#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace dsl
{
    template <typename _T, std::size_t _N>
    class array
    {
    public:
        using value_type = _T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        //**************************************************
        // 생성자/소멸자
        //**************************************************
        
        array() noexcept = default;


        array(const array& other) noexcept
        {
            std::copy(other.data_, other.data_ + _N, data_);
        }

        array(array&& other) noexcept
        {
            std::move(other.data_, other.data_ + _N, data_);
            std::fill(other.data_, other.data_ + _N, value_type{});
        }

        array(std::initializer_list<value_type> init_list) noexcept
        {
            std::copy(init_list.begin(), init_list.end(), data_);
        }

        /// @brief 소멸자
        virtual ~array() = default;

        /// @brief 복사 대입 연산자
        array& operator=(const array& other) noexcept
        {
            std::copy(other.data_, other.data_ + _N, data_);

            return *this;
        }

        /// @brief 이동 대입 연산자
        array& operator=(array&& other) noexcept
        {
            std::move(other.data_, other.data_ + _N, data_);
            std::fill(other.data_, other.data_ + _N, value_type{});

            return *this;
        }

        //**************************************************
        // 요소 접근
        //**************************************************

        reference at(std::size_t index)
        {
            if(_N <= index)
            {
                throw std::out_of_range("Index out of range");
            }
            
            return data_[index];
        }

        const_reference at(std::size_t index) const
        {
            if(_N <= index)
            {
                throw std::out_of_range("Index out of range");
            }

            return data_[index];
        }

        reference operator[](std::size_t index)
        {
            return data_[index];
        }   

        const_reference operator[](std::size_t index) const
        {
            return data_[index];
        }

        reference front()
        {
            return data_[0];
        }

        const_reference front() const
        {
            return data_[0];
        }

        reference back()
        {
            return data_[_N - 1];
        }

        const_reference back() const
        {
            return data_[_N - 1];
        }

        pointer data() noexcept
        {
            return data_;
        }

        const_pointer data() const noexcept
        {
            return data_;
        }

        //**************************************************
        // 크기
        //**************************************************

        bool empty() const
        {
            return size_ == 0;
        }

        std::size_t size() const noexcept
        {
            return _N;
        }

        //**************************************************
        // 기타 연산
        //**************************************************

        void fill(value_type value)
        {
            std::fill(data_, data_ + _N, value);
        }

        void swap(array& other) noexcept
        {
            std::swap(data_, other.data_);
        }

    private:
        value_type data_[_N]{};
        std::size_t size_{ _N };
    };
}