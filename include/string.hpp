#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace ms {
	class string {
	private:
		int _size, _capacity;  // 大小，当前容积，保证 _size < _capacity，末尾有'\0'
		char* _ptr;

		/**
		 * @brief 扩容
		 */
		void _extend() { _extend(_capacity); }
		/**
		 * @brief 扩容
		 * @param len 预计放入字符的数目
		 */
		void _extend(int len) {
			if (len < _capacity) return;
			_capacity = len + 1;
			char* np = new char[_capacity];
			memset(np, 0, _capacity);
			for (int i = 0; i < _size; ++i) {
				np[i] = _ptr[i];
			}
			delete[] _ptr;
			_ptr = np;
		}

		bool full() const { return !(_size + 1 < _capacity); }

	public:
		/**
		 * @brief 默认构造函数，容量为50
		 */
		string() : _size(0), _capacity(50) { _ptr = new char[_capacity]; memset(_ptr, 0, _capacity); }
		/**
		 * @param maxCapacity 提供容量的初始值，最小为20 
		 */
		string(int maxCapacity) : _size(0), _capacity(maxCapacity > 20 ? maxCapacity : 20) { 
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
		}
		/**
		 * @param ps 字符数组首地址
		 * @param len 初始字符串的长度
		 */
		string(const char* ps, int len) : _size(len) {
			_capacity = len > 10 ? len * 2 : 20;
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
			for (int i = 0; i < len; ++i) _ptr[i] = ps[i];
		}
		/**
		 * @param ps 通过常量字符串初始化，末尾有'\0'
		 */
		string(const char* ps) : string(ps, strlen(ps)) {}
		/**
		 * @param ps 字符数组首地址
		 * @param len 初始字符串的长度
		 */
		string(char* ps, int len) : string(static_cast<const char*>(ps), len) {}
		/**
		 * @brief 复制构造函数
		 */
		string(string& s) : _size(s.size()), _capacity(s.capacity()) {
			_ptr = new char[_capacity];
			for (int i = 0; i < _size; ++i) _ptr[i] = s[i];
		}
		/**
		 * @brief 析构函数
		 */
		~string() {
			delete[] _ptr;
		}

		int size() const { return _size; }
		int length() const { return _size; }
		int capacity() const { return _capacity; }  // 实际保存字符容量为_capacity - 1

		char* c_str() { return _ptr; }

		bool empty() const { return _size == 0; }

		/**
		 * @brief 重载[]
		 * @param i 下标
		 * @return 下标i处字符的引用
		 */
		char& operator[](int i) {
			if (i < 0 || i >= _size) {
				std::cerr << "Out of size while reading.\n";
				exit(1);
			}
			return _ptr[i];
		}

		/**
		 * @brief 重载[]，const修饰
		 * @param i 下标
		 * @return 下标i处的字符，非引用
		 */
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

		string& operator=(const char* ps) {
			_size = strlen(ps);
			_capacity = _size > 10 ? _size * 2 : 20;
			delete[] _ptr;
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
			for (int i = 0; i < _size; ++i) _ptr[i] = ps[i];
			return *this;
		}

		/**
		 * @brief 比较两个字符串是否相等，比较size和字符内容，不比较capacity
		 */
		bool operator==(const string& s) const {
			if (_size != s.size()) return false;
			for (int i = 0; i < _size; ++i) {
				if (_ptr[i] != s[i]) return false;
			}
			return true;
		}

		/**
		 * @brief 根据字典序比较两个字符串
		 */
		bool operator<(const string& s) const {
			int len = s.size() < _size ? s.size() : _size;  // 较短字符串的长度
			for (int i = 0; i < len; ++i) {  // _ptr[i] == s[i]时持续循环
				if (_ptr[i] < s[i]) return true;
				else if (_ptr[i] > s[i]) return false;
			}
			if (len == _size && len < s.size()) return true;
			return false;
		}

		bool operator<=(const string& s) const {
			return *this == s || *this < s;
		}

		bool operator>(const string& s) const {
			return !(*this == s || *this < s);
		}

		bool operator>=(const string& s) const {
			return !(*this < s);
		}

		string operator+(const string& s) const {
			string ans(_capacity + s.capacity());  // 根据容量之和构造新的string对象
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

		/**
		 * @brief 在字符串附加字符串。注意有可能调用s.append(s)。
		 */
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

		/**
		 * @brief 在字符串尾附加单个字符
		 */
		string& append(char c) {
			if (full()) _extend();
			_ptr[_size++] = c;
			return* this;
		}

		/**
		 * @brief 返回从pos开始长度为len的子串
		 * @param pos 起始字符的下标
		 * @param len 子串长度
		 */
		string substr(int pos, int len) {
			if (pos + len > _size) {  // len超出边界时截断；式子取等时恰好到string的末尾
				len = _size - pos;
			}
			string ans(_ptr + pos, len);
			return ans;
		}

		/**
		 * @brief 插入单个字符
		 * @param pos 插入字符的位置，插入后是该字符的下标
		 * @param c 被插入的字符
		 */
		string& insert(int pos, char c) {
			if (full()) _extend();
			for (int i = _size; i > pos; --i) _ptr[i] = _ptr[i - 1];
			_ptr[pos] = c;
			return *this;
		}
		/**
		 * @brief 插入字符串
		 * @param pos 被插入的位置，插入后是被插入串首字符的下标
		 * @param ps 被插入的字符串，以'\0'结尾
		 */
		string& insert(int pos, const char* ps) {
			int len = strlen(ps);
			if (_size + len + 1 > _capacity) _extend(_size + len);
			for (int i = _size; i >= pos; --i) _ptr[i + len] = _ptr[i];  // 字符向右移动len
			for (int i = 0; i < len; ++i) _ptr[i + pos] = ps[i];
			return *this;
		}

		/**
		 * @brief 删除子串
		 * @param pos 被删除子串的起始位置
		 * @param len 被删除子串的长度
		 */
		string& erase(int pos, int length) {
			if (pos >= _size) {
				std::cerr << "Out of size while erase().\n";
				exit(1);
			}
			if (pos + length > _size) length = _size - pos;
			for (int i = pos; i < _size - length; ++i) _ptr[i] = _ptr[i + length];
			memset(_ptr + _size - length, 0, length);
			return *this;
		}

		/**
		 * @brief 清空字符串，全赋值0，size归0，capacity不变。
		 */
		void clear() {
			memset(_ptr, 0, _size);
			_size = 0;
		}

		/**
		 * @brief 按照字典序比较两个字符串
		 * @return *this-s的符号，0：相等；1：左＞右；-1：左＜右。
		 */
		int compare(string s) {
			if (*this == s) return 0;
			else if (*this < s) return -1;
			else return 1;
		}

		int compare(const char* ps) {
			int res = strcmp(_ptr, ps);
			if (res == 0) return 0;
			else if (res < 0) return -1;
			else return 1;
		}

		int compare(char* ps) {
			int res = strcmp(_ptr, ps);
			if (res == 0) return 0;
			else if (res < 0) return -1;
			else return 1;
		}

		/**
		 * @brief 查找字符c，返回下标
		 * @return 若查找成功返回下标；查找失败返回-1.
		 */
		int find(char c) {
			for (int i = 0; i < _size; ++i) {
				if (_ptr[i] == c) return i;
			}
			return -1;
		}

		/**
		 * @brief 查找子串ps，返回起始字符下标
		 * @return 若查找成功返回起始字符下标；查找失败返回-1.
		 */
		int find(const char* ps) {
			int len = strlen(ps);
			int i, j;
			for (i = 0, j = 0; j < len &&  i < _size + 1 - len; ++i) {  // i + len <= _size
				// i 为起始字符沿着_ptr移动的循环
				for (j = 0; j < len; ++j) {
					if (_ptr[i + j] != ps[j]) break;
				}
				// 若查找成功，j == len
			}
			if (j == len) return i;
			else return -1;
		}

		/**
		 * @brief 将字符串起始位置pos，长度length的子串替换为ps
		 */
		string& replace(int pos, int length, const char* ps) {
			int lenps = strlen(ps);
			int lenmin = lenps < length ? lenps : length;
			for (int i = 0; i < lenmin; ++i) {
				_ptr[i + pos] = ps[i];
			}
			if (lenmin < length) {  // lenps < length，需要删除中间部分
				erase(pos + lenmin, length - lenmin);
			}
			else if (lenmin < lenps) {  // length < lenps，需要再插入ps剩余部分
				insert(pos + lenmin, ps + lenmin);
			}
			return *this;
		}
	};
}
