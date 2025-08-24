/*********************************************************************
 * \file   stack.hpp
 * \brief  栈的实现
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/

#include <iostream>

#include "vector.hpp"

namespace ms {
    template <typename T>
    class stack {
    private:
        vector<T> _vec;

    public:
        stack() : _vec() {}
        /**
         * @param n 初始栈的最大容量。最小为10，n > 10时n有效
         */
        stack(size_t n) : _vec(n > 10 ? n : 10) {}

        inline size_t size() const {
            return _vec.size();
        }

        inline size_t maxSize() const {
            return _vec.maxSize();
        }

        inline bool empty() const {
            return _vec.empty();
        }

        void push(T&& elem) {
            _vec.push_back(elem);
        }

        T pop() {
            if (empty()) {
                std::cerr << "pop() while stack is empty." << std::endl;
                exit(1);
            }
            return _vec.pop_back();
        }

        T& top() {
            if (empty()) {
                std::cerr << "top() while stack is empty." << std::endl;
                exit(1);
            }
            return _vec.back();
        }
    };
}

