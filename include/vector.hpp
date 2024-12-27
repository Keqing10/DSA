#pragma once

#include <iostream>

namespace ms {
	template <typename T>
	class vector {
	private:
		int _maxSize, _size;  // 最大长度与当前长度
		T* ptr;
		// 扩容
		void _extend() {
			_maxSize *= 2;
			T* np = new T[_maxSize];
			for (int i = 0; i < _size; ++i) np[i] = ptr[i];
			delete[] ptr;
			ptr = np;
		}
	public:
		vector() {
			_maxSize = 100;
			_size = 0;
			ptr = new T[_maxSize];
		}
		/**
		 * @brief 构造函数
		 * @param n 初始长度，初始值默认为0
		 */
		vector(int n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_size = n;
			ptr = new T[_maxSize];
		}
		/**
		 * @brief 构造函数
		 * @param n 初始长度
		 * @param val 初始值
		 */
		vector(int n, T val) {
			_maxSize = n < 50 ? 100 : n * 2;
			_size = n;
			ptr = new T[_maxSize];
			for (int i = 0; i < n; ++i) ptr[i] = val;
		}
		~vector() { delete[] ptr; }

		/**
		 * @brief 重新声明数组长度和初始值
		 * @param n 长度
		 * @param val 覆盖的值
		 */
		void assign(int n, T val) {
			if (n >= _maxSize) {  // 先扩容
				_maxSize = n * 2;
				T* np = new T[_maxSize];
				delete[] ptr;
				ptr = np;
				for (int i = 0; i < n; ++i) ptr[i] = val;
			}
			for (int i = 0; i < n; ++i) ptr[i] = val;
			_size = n;
		}

		T& operator[](int i) {
			if (i < _size) return ptr[i];
			std::cout << "Out of size while reading." << std::endl;
		}

		/**
		 * @brief 在数组尾添加元素
		 * @param val 
		 */
		void push_back(T val) {
			if (_maxSize == _size) _extend();  // 插入前先扩容
			ptr[_size++] = val;
		}

		/**
		 * @brief 在下标index处添加元素val
		 * @param index 元素val的最终下标
		 * @param val 待插入的元素
		 */
		void insert(int index, T val) {
			if (_maxSize == _size) _extend();
			for (int i = _size; i > index; --i) ptr[i] = ptr[i - 1];
			ptr[index] = val;
		}

		/**
		 * @brief 删除下标为index的元素
		 */
		void erase(int index) {
			if (index < _size) {
				for (int i = index; i < _size - 1; ++i) {
					ptr[i] = ptr[i + 1];
				}
				--_size;
			} else {
				std::cout << "Out of size while erasing." << std::endl;
			}
		}

		int size() { return _size; }
	};
}