#pragma once

#include <iostream>

namespace ms {
	template <typename T>
	class vector {
	private:
		int _maxSize, _size;  // ��󳤶��뵱ǰ����
		T* ptr;
		// ����
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
		 * @brief ���캯��
		 * @param n ��ʼ���ȣ���ʼֵĬ��Ϊ0
		 */
		vector(int n) {
			_maxSize = n < 50 ? 100 : n * 2;
			_size = n;
			ptr = new T[_maxSize];
		}
		/**
		 * @brief ���캯��
		 * @param n ��ʼ����
		 * @param val ��ʼֵ
		 */
		vector(int n, T val) {
			_maxSize = n < 50 ? 100 : n * 2;
			_size = n;
			ptr = new T[_maxSize];
			for (int i = 0; i < n; ++i) ptr[i] = val;
		}
		~vector() { delete[] ptr; }

		/**
		 * @brief �����������鳤�Ⱥͳ�ʼֵ
		 * @param n ����
		 * @param val ���ǵ�ֵ
		 */
		void assign(int n, T val) {
			if (n >= _maxSize) {  // ������
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
		 * @brief ������β���Ԫ��
		 * @param val 
		 */
		void push_back(T val) {
			if (_maxSize == _size) _extend();  // ����ǰ������
			ptr[_size++] = val;
		}

		/**
		 * @brief ���±�index�����Ԫ��val
		 * @param index Ԫ��val�������±�
		 * @param val �������Ԫ��
		 */
		void insert(int index, T val) {
			if (_maxSize == _size) _extend();
			for (int i = _size; i > index; --i) ptr[i] = ptr[i - 1];
			ptr[index] = val;
		}

		/**
		 * @brief ɾ���±�Ϊindex��Ԫ��
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