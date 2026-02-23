/*********************************************************************
 * \file   vector.hpp
 * \brief  动态数组的实现
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/
#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace ms {
template <typename T> class vector {
  private:
    size_t _maxSize, _size; // 最大长度与当前长度
    T *_ptr;

  public:
    /**
     * @brief 默认构造函数，初始容量默认为100
     */
    vector() : _maxSize(100), _size(0) { _ptr = new T[_maxSize]; }
    /**
     * @brief 构造函数
     * @param n 初始容量，最小为10
     */
    vector(size_t n) : _maxSize(n > 10 ? n : 10), _size(0) { _ptr = new T[_maxSize]; }
    /**
     * @brief 构造函数
     * @param n 初始长度
     * @param val 初始值
     */
    vector(size_t n, const T &val) : _size(n) {
        _maxSize = n < 50 ? 100 : n * 2;
        _ptr = new T[_maxSize];
        for (size_t i = 0; i < n; ++i)
            _ptr[i] = val;
    }
    vector(std::initializer_list<T> il) : _size(il.size()) {
        _maxSize = _size < 50 ? 100 : _size * 2;
        _ptr = new T[_maxSize];
        size_t i = 0;
        for (const T &elem : il)
            _ptr[i++] = elem;
    }
    /**
     * @brief 复制构造函数
     */
    vector(const vector &vec) : _maxSize(vec.maxSize()), _size(vec.size()) {
        _ptr = new T[_maxSize];
        for (size_t i = 0; i < _size; ++i)
            _ptr[i] = vec.get(i);
    }
    /**
     * @brief 移动构造函数
     */
    vector(vector &&vec) noexcept : _maxSize(vec._maxSize), _size(vec._size), _ptr(vec._ptr) {
        vec._ptr = nullptr;
        vec._size = 0;
        vec._maxSize = 0;
    }

    /**
     * @brief 析构函数
     */
    ~vector() { delete[] _ptr; }

    /**
     * @brief 扩容
     */
    void extend() {
        _maxSize *= 2;
        T *np = new T[_maxSize];
        for (size_t i = 0; i < _size; ++i)
            np[i] = std::move(_ptr[i]);
        delete[] _ptr;
        _ptr = np;
    }

    /**
     * @brief 重新声明数组长度和初始值
     * @param n 长度
     * @param val 覆盖的值
     */
    void assign(size_t n, const T &val) {
        if (n >= _maxSize) { // 先扩容
            _maxSize = n * 2;
            T *np = new T[_maxSize];
            delete[] _ptr;
            _ptr = np;
        }
        for (size_t i = 0; i < n; ++i)
            _ptr[i] = val;
        _size = n;
    }

    T &operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Out of size while [] reading.");
        }
        return _ptr[index];
    }

    const T &operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Out of size while [] reading.");
        }
        return _ptr[index];
    }

    const T &get(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Out of size while get() reading.");
        }
        return _ptr[index];
    }

    vector &operator=(const vector &vec) {
        if (this == &vec)
            return *this;            // 防止自赋值
        if (_maxSize < vec.size()) { // 扩容
            _maxSize = vec.maxSize();
            delete[] _ptr;
            _ptr = new T[_maxSize];
        }
        _size = vec.size();
        for (size_t i = 0; i < _size; ++i)
            _ptr[i] = vec[i];
        return *this;
    }

    inline bool empty() const { return _size == 0; }

    inline bool full() const { return _size == _maxSize; }

    /**
     * @brief 在数组尾添加元素
     * @param val
     */
    void push_back(const T &val) {
        if (_maxSize == _size)
            extend(); // 插入前先扩容
        _ptr[_size++] = val;
    }

    void push_back(T &&val) {
        if (_maxSize == _size)
            extend(); // 插入前先扩容
        _ptr[_size++] = std::move(val);
    }

    /**
     * @brief 删除数组尾元素并返回
     */
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back() while vector is empty.");
        }
        return std::move(_ptr[--_size]);
    }

    T &front() {
        if (empty()) {
            throw std::out_of_range("front() while vector is empty.");
        }
        return _ptr[0];
    }

    T &back() {
        if (empty()) {
            throw std::out_of_range("back() while vector is empty.");
        }
        return _ptr[_size - 1];
    }

    /**
     * @brief 在下标index处添加元素val
     * @param index 元素val的最终下标
     * @param val 待插入的元素
     */
    void insert(size_t index, const T &val) {
        if (index > _size) {
            throw std::out_of_range("Out of size while insert().");
        }
        if (_maxSize == _size)
            extend();
        for (size_t i = _size; i > index; --i)
            _ptr[i] = std::move(_ptr[i - 1]);
        _ptr[index] = val;
        ++_size;
    }

    void insert(size_t index, T &&val) {
        if (index > _size) {
            throw std::out_of_range("Out of size while insert().");
        }
        if (_maxSize == _size)
            extend();
        for (size_t i = _size; i > index; --i)
            _ptr[i] = std::move(_ptr[i - 1]);
        _ptr[index] = std::move(val);
        ++_size;
    }

    /**
     * @brief 删除下标为index的元素
     */
    void erase(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Out of size while erasing.");
        }
        for (size_t i = index; i < _size - 1; ++i) {
            _ptr[i] = std::move(_ptr[i + 1]);
        }
        --_size;
    }

    inline size_t size() const { return _size; }

    inline size_t maxSize() const { return _maxSize; }

    T *get_ptr() { return _ptr; }

    void clear() { _size = 0; }
};
} // namespace ms
