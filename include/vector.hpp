#pragma once

#include <iostream>

#include "list.hpp"

namespace ms {
	template <typename T>
	class vector {
	private:
		int _maxSize, _size;  // ��󳤶��뵱ǰ����
		T* _ptr;
		// ����
		void _extend() {
			_maxSize *= 2;
			T* np = new T[_maxSize];
			for (int i = 0; i < _size; ++i) np[i] = _ptr[i];
			delete[] _ptr;
			_ptr = np;
		}
	public:
		vector() : _maxSize(100), _size(0) {
			_ptr = new T[_maxSize];
		}
		/**
		 * @brief ���캯��
		 * @param n ��ʼ���ȣ���ʼֵĬ��Ϊ0
		 */
		vector(int n) : _size(n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_ptr = new T[_maxSize];
		}
		/**
		 * @brief ���캯��
		 * @param n ��ʼ����
		 * @param val ��ʼֵ
		 */
		vector(int n, T&& val) : _size(n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_ptr = new T[_maxSize];
			for (int i = 0; i < n; ++i) _ptr[i] = val;
		}
		/**
		 * @brief ���ƹ��캯��
		 */
		vector(vector& vec) : _maxSize(vec.maxSize()), _size(vec.size()) {
			_ptr = new T[_maxSize];
			for (int i = 0; i < _size; ++i) _ptr[i] = vec[i];
		}
		/**
		 * @brief ʹ������p��������
		 * @param p ����ָ��
		 * @param n Ԫ�ظ���
		 */
		vector(T* p, int n) : _size(n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_ptr = new T[_maxSize];
			for (int i = 0; i < n; ++i) _ptr[i] = p[i];
		}
		~vector() { delete[] _ptr; }

		/**
		 * @brief �����������鳤�Ⱥͳ�ʼֵ
		 * @param n ����
		 * @param val ���ǵ�ֵ
		 */
		void assign(int n, T&& val) {
			if (n >= _maxSize) {  // ������
				_maxSize = n * 2;
				T* np = new T[_maxSize];
				delete[] _ptr;
				_ptr = np;
			}
			for (int i = 0; i < n; ++i) _ptr[i] = val;
			_size = n;
		}

		T& operator[](int index) {
			if (index >= _size) {
				std::cerr << "Out of size while reading." << std::endl;
				exit(1);
			}
			return _ptr[index];
		}

		vector& operator=(vector& vec) {
			if (_maxSize < vec.size()) {  // ����
				_maxSize = vec.maxSize();
				delete[] _ptr;
				_ptr = new T[_maxSize];
			}
			_size = vec.size();
			for (int i = 0; i < _size; ++i) _ptr[i] = vec[i];
			return *this;
		}

		/**
		 * @brief ������β���Ԫ��
		 * @param val 
		 */
		void push_back(T val) {
			if (_maxSize == _size) _extend();  // ����ǰ������
			_ptr[_size++] = val;
		}

		/**
		 * @brief ɾ������βԪ�ز�����
		 */
		T pop_back(){
			return _ptr[--_size];
		}

		/**
		 * @brief ���±�index�����Ԫ��val
		 * @param index Ԫ��val�������±�
		 * @param val �������Ԫ��
		 */
		void insert(int index, T&& val) {
			if (index > _size) {
				std::cerr << "Out of size while inserting." << std::endl;
				exit(1);
			}
			if (_maxSize == _size) _extend();
			for (int i = _size; i > index; --i) _ptr[i] = _ptr[i - 1];
			_ptr[index] = val;
		}

		/**
		 * @brief ɾ���±�Ϊindex��Ԫ��
		 */
		void erase(int index) {
			if (index >= _size) {
				std::cerr << "Out of size while erasing." << std::endl;
				exit(1);
			}
			for (int i = index; i < _size - 1; ++i) {
				_ptr[i] = _ptr[i + 1];
			}
			--_size;
		}

		int size() { return _size; }

		int maxSize() { return _maxSize; }

		T* get_ptr() { return _ptr; }
	};
}