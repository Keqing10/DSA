#pragma once

#include <iostream>

namespace ms {
	template <typename T>
	class vector {
	private:
		size_t _maxSize, _size;  // 最大长度与当前长度
		T* _ptr;
		// 扩容
		void _extend() {
			_maxSize *= 2;
			T* np = new T[_maxSize];
			for (size_t i = 0; i < _size; ++i) np[i] = _ptr[i];
			delete[] _ptr;
			_ptr = np;
		}
	public:
		/**
		 * @brief 默认构造函数，初始容量默认为100
		 */
		vector() : _maxSize(100), _size(0) {
			_ptr = new T[_maxSize];
		}
		/**
		 * @brief 构造函数
		 * @param n 初始长度，默认为0
		 */
		vector(size_t n) : _size(n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_ptr = new T[_maxSize];
		}
		/**
		 * @brief 构造函数
		 * @param n 初始长度
		 * @param val 初始值
		 */
		vector(size_t n, T&& val) : _size(n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_ptr = new T[_maxSize];
			//if (n == 1) {
			//	_ptr[0] = std::move(val);
			//	return;
			//}
			for (size_t i = 0; i < n; ++i) _ptr[i] = val;
		}
		vector(size_t n, const T& val) : _size(n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_ptr = new T[_maxSize];
			for (size_t i = 0; i < n; ++i) _ptr[i] = val;
		}
		/**
		 * @brief 复制构造函数
		 */
		vector(vector& vec) : _maxSize(vec.maxSize()), _size(vec.size()) {
			_ptr = new T[_maxSize];
			for (size_t i = 0; i < _size; ++i) _ptr[i] = vec[i];
		}
		~vector() { delete[] _ptr; }

		/**
		 * @brief 重新声明数组长度和初始值
		 * @param n 长度
		 * @param val 覆盖的值
		 */
		void assign(size_t n, T&& val) {
			if (n >= _maxSize) {  // 先扩容
				_maxSize = n * 2;
				T* np = new T[_maxSize];
				delete[] _ptr;
				_ptr = np;
			}
			for (size_t i = 0; i < n; ++i) _ptr[i] = val;
			_size = n;
		}

		T& operator[](size_t index) {
			if (index >= _size) {
				std::cerr << "Out of size while reading." << std::endl;
				exit(1);
			}
			return _ptr[index];
		}

		vector& operator=(vector& vec) {
			if (_maxSize < vec.size()) {  // 扩容
				_maxSize = vec.maxSize();
				delete[] _ptr;
				_ptr = new T[_maxSize];
			}
			_size = vec.size();
			for (size_t i = 0; i < _size; ++i) _ptr[i] = vec[i];
			return *this;
		}

		/**
		 * @brief 在数组尾添加元素
		 * @param val 
		 */
		void push_back(T&& val) {
			if (_maxSize == _size) _extend();  // 插入前先扩容
			_ptr[_size++] = val;
		}

		/**
		 * @brief 删除数组尾元素并返回
		 */
		T pop_back(){
			return _ptr[--_size];
		}

		/**
		 * @brief 在下标index处添加元素val
		 * @param index 元素val的最终下标
		 * @param val 待插入的元素
		 */
		void insert(size_t index, T&& val) {
			if (index > _size) {
				std::cerr << "Out of size while inserting." << std::endl;
				exit(1);
			}
			if (_maxSize == _size) _extend();
			for (size_t i = _size; i > index; --i) _ptr[i] = _ptr[i - 1];
			_ptr[index] = val;
			++_size;
		}

		/**
		 * @brief 删除下标为index的元素
		 */
		void erase(size_t index) {
			if (index >= _size) {
				std::cerr << "Out of size while erasing." << std::endl;
				exit(1);
			}
			for (size_t i = index; i < _size - 1; ++i) {
				_ptr[i] = _ptr[i + 1];
			}
			--_size;
		}

		size_t size() { return _size; }

		size_t maxSize() { return _maxSize; }

		T* get_ptr() { return _ptr; }

		void clear() { _size = 0; }
	};
}
