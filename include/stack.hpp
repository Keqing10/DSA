/*********************************************************************
 * \file   stack.hpp
 * \brief  栈的实现
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/
#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <stdexcept>
#include <utility>

#include "vector.hpp"

namespace ms {
template <typename T> class stack {
  private:
    vector<T> _vec;

  public:
    stack() : _vec() {}
    /**
     * @param n 初始栈的最大容量。最小为10，n > 10时n有效
     */
    stack(size_t n) : _vec(n > 10 ? n : 10) {}

    inline size_t size() const { return _vec.size(); }

    inline size_t maxSize() const { return _vec.maxSize(); }

    inline bool empty() const { return _vec.empty(); }

    void push(const T &elem) { _vec.push_back(elem); }

    void push(T &&elem) { _vec.push_back(std::move(elem)); }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop() while stack is empty.");
        }
        return _vec.pop_back();
    }

    T &top() {
        if (empty()) {
            throw std::out_of_range("top() while stack is empty.");
        }
        return _vec.back();
    }

    const T &top() const {
        if (empty()) {
            throw std::out_of_range("top() while stack is empty.");
        }
        return _vec.back();
    }
};
} // namespace ms

#endif // STACK_HPP
