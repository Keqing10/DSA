/*********************************************************************
 * \file   queue.hpp
 * \brief  队列实现：双向队列，FIFO队列，优先级队列
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/
#pragma once
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>
#include <utility>

#include "heap.hpp"

namespace ms {
template <typename T> class deque {
  private:
    size_t _maxSize, _size, _head, _tail;
    T *_ptr;

    void _extend() {
        T *np = new T[_maxSize * 2];
        for (size_t i = 0; i < _size; ++i)
            np[i] = std::move(_ptr[(_head + i) % _maxSize]);
        delete[] _ptr;
        _ptr = np;
        _head = 0;
        _tail = _size;
        _maxSize *= 2;
    }

  public:
    deque() : _maxSize(100), _size(0), _head(0), _tail(0) { _ptr = new T[100]; }
    deque(size_t maxSize) : _maxSize(maxSize > 10 ? maxSize : 10), _size(0), _head(0), _tail(0) {
        _ptr = new T[_maxSize];
    }
    ~deque() { delete[] _ptr; }

    inline size_t size() const { return _size; }

    inline size_t maxSize() const { return _maxSize; }

    inline bool empty() const { return _size == 0; }

    inline bool full() const { return _size + 1 == _maxSize; }

    /**
     * @brief 在队尾添加元素
     */
    void push_back(const T &elem) {
        if (_size + 1 == _maxSize)
            _extend();
        _ptr[_tail] = elem;
        _tail = (_tail + 1) % _maxSize;
        ++_size;
    }

    void push_back(T &&elem) {
        if (_size + 1 == _maxSize)
            _extend();
        _ptr[_tail] = std::move(elem);
        _tail = (_tail + 1) % _maxSize;
        ++_size;
    }

    /**
     * @brief 在队首添加元素
     */
    void push_front(const T &elem) {
        if (_size + 1 == _maxSize)
            _extend();
        _head = _head == 0 ? _maxSize - 1 : _head - 1;
        _ptr[_head] = elem;
        ++_size;
    }

    void push_front(T &&elem) {
        if (_size + 1 == _maxSize)
            _extend();
        _head = _head == 0 ? _maxSize - 1 : _head - 1;
        _ptr[_head] = std::move(elem);
        ++_size;
    }

    /**
     * @brief 弹出队首元素
     */
    T pop_front() {
        if (_size == 0) {
            throw std::out_of_range("pop_front() while deque is empty.");
        }
        --_size;
        size_t ind = _head;
        _head = (_head + 1) % _maxSize;
        return std::move(_ptr[ind]);
    }

    /**
     * @brief 弹出队尾元素
     * @return
     */
    T pop_back() {
        if (_size == 0) {
            throw std::out_of_range("pop_back() while deque is empty.");
        }
        --_size;
        _tail = (_tail == 0 ? _maxSize - 1 : _tail - 1);
        return std::move(_ptr[_tail]);
    }

    T &front() {
        if (_size == 0) {
            throw std::out_of_range("front() while deque is empty.");
        }
        return _ptr[_head];
    }

    const T &front() const {
        if (_size == 0) {
            throw std::out_of_range("front() while deque is empty.");
        }
        return _ptr[_head];
    }

    T &back() {
        if (_size == 0) {
            throw std::out_of_range("back() while deque is empty.");
        }
        // _tail > 0 => _tail - 1
        // _tail == 0 => _maxSize - 1
        return _ptr[_tail == 0 ? _maxSize - 1 : _tail - 1];
    }

    const T &back() const {
        if (_size == 0) {
            throw std::out_of_range("back() while deque is empty.");
        }
        return _ptr[_tail == 0 ? _maxSize - 1 : _tail - 1];
    }
};

template <typename T> class queue {
  private:
    deque<T> _dq;

  public:
    queue() : _dq() {}
    queue(size_t maxSize) : _dq(maxSize) {}

    inline size_t size() const { return _dq.size(); }

    inline size_t maxSize() const { return _dq.maxSize(); }

    inline bool empty() const { return _dq.empty(); }

    inline bool full() const { return _dq.full(); }

    /**
     * @brief 在队尾添加元素
     */
    void push(const T &elem) { _dq.push_back(elem); }

    void push(T &&elem) { _dq.push_back(std::move(elem)); }

    /**
     * @brief 弹出队首元素
     */
    T pop() {
        if (_dq.empty()) {
            throw std::out_of_range("pop() while queue is empty.");
        }
        return _dq.pop_front();
    }

    T &front() {
        if (_dq.empty()) {
            throw std::out_of_range("front() while queue is empty.");
        }
        return _dq.front();
    }

    const T &front() const {
        if (_dq.empty()) {
            throw std::out_of_range("front() while queue is empty.");
        }
        return _dq.front();
    }

    T &back() {
        if (_dq.empty()) {
            throw std::out_of_range("back() while queue is empty.");
        }
        return _dq.back();
    }

    const T &back() const {
        if (_dq.empty()) {
            throw std::out_of_range("back() while queue is empty.");
        }
        return _dq.back();
    }
};

template <typename T> class priority_queue {
  private:
    size_t _size, _maxSize;
    T *_ptr;
    heap<T> hp;

    void _extend() {
        T *np = new T[_maxSize * 2];
        for (size_t i = 0; i < _size; ++i)
            np[i] = _ptr[i];
        delete[] _ptr;
        _ptr = np;
        _maxSize *= 2;
        hp.set(_ptr, _size);
    }

  public:
    priority_queue() : _size(0), _maxSize(20) {
        _ptr = new T[_maxSize];
        hp.set(_ptr, 0);
    }
    /**
     * @brief 指定初始容量，最小为10
     */
    priority_queue(size_t n) : _size(0), _maxSize(n > 10 ? n : 10) {
        _ptr = new T[_maxSize];
        hp.set(0, _ptr);
    }
    ~priority_queue() { delete[] _ptr; }

    inline size_t size() const { return _size; }

    inline size_t maxSize() const { return _maxSize; }

    inline bool empty() const { return _size == 0; }

    inline bool full() const { return _size == _maxSize; }

    void push(const T &t) {
        if (full())
            _extend();
        hp.insert(t);
        ++_size;
    }

    void push(T &&t) {
        if (full())
            _extend();
        hp.insert(t);
        ++_size;
    }

    T pop() {
        --_size;
        return hp.pop();
    }

    T &front() { return _ptr[0]; }
};
} // namespace ms

#endif // QUEUE_HPP
