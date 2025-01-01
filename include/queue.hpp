#pragma once

#include <iostream>

namespace ms {
	template <typename T>
	class queue {
	private:
		int _maxSize, _size, _head, _tail;  // 最大长度，当前长度，头元素下标，尾元素下标+1
		T* _ptr;

		void _extend() {
			T* np = new T[_maxSize * 2];
			for (int i = 0; i < _size; ++i) np[i] = _ptr[(_head + i) % _maxSize];
			delete[] _ptr;
			_ptr = np;
			_head = 0;
			_tail = _size;
			_maxSize *= 2;
		}

	public:
		queue() : _maxSize(100), _size(0), _head(0), _tail(0) {
			_ptr = new T[100];
		}
		queue(int maxSize) : _size(0), _head(0), _tail(0) {
			_maxSize = maxSize > 10 ? maxSize : 10;
			_ptr = new T[_maxSize];
		}
		~queue() { delete[] _ptr; }

		int size() { return _size; }

		int maxSize() { return _maxSize; }

		bool empty() { return _size == 0; }

		bool full() { return _size + 1 == _maxSize; }

		/**
		 * @brief 在队尾添加元素
		 */
		void push(T&& elem) {
			if (_size + 1 == _maxSize) _extend();
			_ptr[_tail] = elem;
			_tail = (_tail + 1) % _maxSize;
			++_size;
		}

		/**
		 * @brief 弹出队首元素
		 */
		T& pop() {
			if (_size == 0) {
				std::cerr << "pop() while queue is empty." << std::endl;
				exit(1);
			}
			--_size;
			int ind = _head;
			_head = (_head + 1) % _maxSize;
			return _ptr[ind];
		}

		T& front() {
			if (_size == 0) {
				std::cerr << "front() while queue is empty." << std::endl;
				exit(1);
			}
			return _ptr[_head];
		}

		T& back() {
			if (_size == 0) {
				std::cerr << "back() while queue is empty." << std::endl;
				exit(1);
			}
			// _tail > 0 => _tail - 1
			// _tail == 0 => _maxSize - 1
			return T[_tail == 0 ? _maxSize - 1 : tail - 1];
		}
	};

	template <typename T>
	class deque {
	private:
		int _maxSize, _size, _head, _tail;
		T* _ptr;

		void _extend() {
			T* np = new T[_maxSize * 2];
			for (int i = 0; i < _size; ++i) np[i] = _ptr[(_head + i) % _maxSize];
			delete[] _ptr;
			_ptr = np;
			_head = 0;
			_tail = _size;
			_maxSize *= 2;
		}

	public:
		deque() : _maxSize(100), _size(0), _head(0), _tail(0) {
			_ptr = new T[100];
		}
		deque(int maxSize) : _size(0), _head(0), _tail(0) {
			_maxSize = maxSize > 10 ? maxSize : 10;
			_ptr = new T[_maxSize];
		}
		~deque() { delete[] _ptr; }

		int size() { return _size; }

		int maxSize() { return _maxSize; }

		bool empty() { return _size == 0; }

		bool full() { return _size + 1 == _maxSize; }

		/**
		 * @brief 在队尾添加元素
		 */
		void push_back(T&& elem) {
			if (_size + 1 == _maxSize) _extend();
			_ptr[_tail] = elem;
			_tail = (_tail + 1) % _maxSize;
			++_size;
		}

		/**
		 * @brief 在队首添加元素
		 */
		void push_front(T&& elem) {
			if (_size + 1 == _maxSize) _extend();
			_head = _head == 0 ? _maxSize - 1 : _head - 1;
			_ptr[_head] = elem;
			++_size;
		}

		/**
		 * @brief 弹出队首元素
		 */
		T& pop_front() {
			if (_size == 0) {
				std::cerr << "pop_front() while queue is empty." << std::endl;
				exit(1);
			}
			--_size;
			int ind = _head;
			_head = (_head + 1) % _maxSize;
			return _ptr[ind];
		}

		/**
		 * @brief 弹出队尾元素
		 * @return 
		 */
		T& pop_back() {
			if (_size == 0) {
				std::cerr << "pop_back() while queue is empty." << std::endl;
				exit(1);
			}
			--_size;
			_tail = _tail == 0 ? _maxSize - 1 : _tail - 1;
			return _ptr[_tail];
		}

		T& front() {
			if (_size == 0) {
				std::cerr << "front() while queue is empty." << std::endl;
				exit(1);
			}
			return _ptr[_head];
		}

		T& back() {
			if (_size == 0) {
				std::cerr << "back() while queue is empty." << std::endl;
				exit(1);
			}
			// _tail > 0 => _tail - 1
			// _tail == 0 => _maxSize - 1
			return T[_tail == 0 ? _maxSize - 1 : tail - 1];
		}
	};
}