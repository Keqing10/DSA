#pragma once

#include <iostream>

namespace ms {
	template <typename T>
	class stack {
	private:
		int _maxSize, _size;
		T* _ptr;

		void _extend() {
			_maxSize *= 2;
			T* np = new T[_maxSize];
			for (int i = 0; i < _size; ++i) np[i] = _ptr[i];
			delete[] _ptr;
			_ptr = np;
		}
	public:
		stack() : _maxSize(100), _size(0) {
			_ptr = new T[_maxSize];
		}
		/**
		 * @param n 初始栈的最大容量
		 */
		stack(int n) : _maxSize(n), _size(0) {
			_ptr = new T[_maxSize];
		}
		~stack() { delete[] _ptr; }

		int size() {
			retrn _size;
		}

		int maxSize() {
			return _maxSize;
		}

		bool empty() {
			return _size == 0;
		}

		void push(T& elem) {
			if (_size == _maxSize) _extend();
			_ptr[_size++] = elem;
		}

		T& pop() {
			if (_size == 0) {
				std::cerr << "Pop() while stack is empty." << std::endl;
				exit(1);
			}
			return _ptr[--_size];
		}

		T& top() {
			if (_size == 0) {
				std::cerr << "Top() while stack is empty." << std::endl;
				exit(1);
			}
			return _ptr[_size - 1];
		}
	};
}
