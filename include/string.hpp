#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace ms {
	class string {
	private:
		int _size, _capacity;  // ��С����ǰ�ݻ�����֤ _size < _capacity
		char* _ptr;

		void _extend() { _extend(_capacity); }
		void _extend(int len) {
			if (len <= _capacity) return;
			_capacity = len * 2;
			char* np = new char[len];
			memset(np, 0, len);
			for (int i = 0; i < _size; ++i) {
				np[i] = _ptr[i];
			}
			delete[] _ptr;
			_ptr = np;
		}

		bool full() const { return !(_size + 1 < _capacity); }

	public:
		string() : _size(0), _capacity(50) { _ptr = new char[_capacity]; memset(_ptr, 0, _capacity); }
		string(int maxCapacity) : _size(0), _capacity(maxCapacity > 20 ? maxCapacity : 20) { memset(_ptr, 0, _capacity); }
		string(const char* p, unsigned len) : _size(static_cast<int>(len)) {
			_capacity = len > 10 ? len * 2 : 20;
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
			for (int i = 0; i < len; ++i) _ptr[i] = p[i];
		}
		string(const char* p) {
			string(p, strlen(p));
		}
		string(char* p, unsigned len) : _size(static_cast<int>(len)) {
			string(p, len);
		}
		string(string& s) : _size(s.size()), _capacity(s.capacity()) {
			_ptr = new char[_capacity];
			for (int i = 0; i < _size; ++i) _ptr[i] = s[i];
		}

		int size() const { return _size; }
		int length() const { return _size; }
		int capacity() const { return _capacity; }

		char* c_str() { return _ptr; }

		bool empty() const { return _size == 0; }

		char& operator[](int i) {
			if (i < 0 || i >= _size) {
				std::cerr << "Out of size while reading.\n";
				exit(1);
			}
			return _ptr[i];
		}

		char operator[] (int i) const {
			if (i < 0 || i >= _size) {
				std::cerr << "Out of size while reading.\n";
				exit(1);
			}
			return _ptr[i];
		}

		string& operator=(const string& s) {
			_size = s.size();
			_capacity = s.capacity();
			delete[] _ptr;
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
			for (int i = 0; i < _size; ++i) _ptr[i] = s[i];
			return *this;
		}

		string& operator=(const char* p) {
			_size = strlen(p);
			_capacity = _size > 10 ? _size * 2 : 20;
			delete[] _ptr;
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
			for (int i = 0; i < _size; ++i) _ptr[i] = p[i];
			return *this;
		}

		bool operator==(const string& s) {
			if (_size != s.size()) return false;
			for (int i = 0; i < _size; ++i) {
				if (_ptr[i] != s[i]) return false;
			}
			return true;
		}

		bool operator<(const string& s) {
			int len = s.size() < _size ? s.size() : _size;
			for (int i = 0; i < len; ++i) {
				if (_ptr[i] < s[i]) return true;
				else if (_ptr[i] > s[i]) return false;
			}
			if (len == _size && len < s.size()) return true;
			return false;
		}

		string operator+(const string& s) {
			string ans(_capacity + s.capacity());
			ans.append(*this);
			ans.append(s);
			return ans;
		}

		string& operator+=(const string& s) {
			this->append(s);
			return *this;
		}

		char at(int i) {
			if (i < 0 || i >= _size) {
				std::cerr << "Out of size while at().\n";
				exit(1);
			}
			return _ptr[i];
		}

		string& append(const string& s) {
			if (_size + s.size() > _capacity - 3) {  // _size + 1 + s.size() + 1 >= _capacity
				_extend(_size + s.size());
			}
			for (int i = 0; i < s.size(); ++i) {
				_ptr[i + _size] = s[i];
			}
			_size += s.size();
			return *this;
		}

		string& append(char c) {
			if (full()) _extend();
			_ptr[_size++] = c;
			return* this;
		}

		string substr(int pos, int len) {
			if (pos + len + 1 >= _capacity) {
				len = _capacity - pos - 1;
			}
			return string(_ptr + pos, len);
		}

		void insert(int pos, char c) {

		}

		void insert(int pos, const char* p) {

		}

		void erase(int pos, int len) {

		}

		void clear() {

		}

		int compare(string s) {

		}

		int compare(const char* p) {

		}

		int compare(char* p) {


		}

	};
}

/*
find()	�������ַ������ַ����е�λ�á�	std::cout << str.find("sub") << std::endl;
rfind()	���ַ���ĩβ��ʼ�������ַ�����λ�á�	std::cout << str.rfind("sub") << std::endl;
replace()	�滻�ַ����еĲ������ݡ�	str.replace(pos, length, "new_substring");
insert()	��ָ��λ�ò������ݡ�	str.insert(pos, "inserted");
erase()	ɾ��ָ��λ�õ��ַ������ַ�����	str.erase(pos, length);
clear()	����ַ�����	str.clear();
compare()	�Ƚ������ַ�����	int result = str.compare("other");
*/