#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace ms {
	class string {
	private:
		int _size, _capacity;  // ��С����ǰ�ݻ�����֤ _size < _capacity��ĩβ��'\0'
		char* _ptr;

		/**
		 * @brief ����
		 */
		void _extend() { _extend(_capacity); }
		/**
		 * @brief ����
		 * @param len Ԥ�Ʒ����ַ�����Ŀ
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
		 * @brief Ĭ�Ϲ��캯��������Ϊ50
		 */
		string() : _size(0), _capacity(50) { _ptr = new char[_capacity]; memset(_ptr, 0, _capacity); }
		/**
		 * @param maxCapacity �ṩ�����ĳ�ʼֵ����СΪ20 
		 */
		string(int maxCapacity) : _size(0), _capacity(maxCapacity > 20 ? maxCapacity : 20) { 
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
		}
		/**
		 * @param ps �ַ������׵�ַ
		 * @param len ��ʼ�ַ����ĳ���
		 */
		string(const char* ps, int len) : _size(len) {
			_capacity = len > 10 ? len * 2 : 20;
			_ptr = new char[_capacity];
			memset(_ptr, 0, _capacity);
			for (int i = 0; i < len; ++i) _ptr[i] = ps[i];
		}
		/**
		 * @param ps ͨ�������ַ�����ʼ����ĩβ��'\0'
		 */
		string(const char* ps) {
			string(ps, strlen(ps));
		}
		/**
		 * @param ps �ַ������׵�ַ
		 * @param len ��ʼ�ַ����ĳ���
		 */
		string(char* ps, int len) : _size(len) {
			string(ps, len);
		}
		/**
		 * @brief ���ƹ��캯��
		 */
		string(string& s) : _size(s.size()), _capacity(s.capacity()) {
			_ptr = new char[_capacity];
			for (int i = 0; i < _size; ++i) _ptr[i] = s[i];
		}
		/**
		 * @brief ��������
		 */
		~string() {
			delete[] _ptr;
		}

		int size() const { return _size; }
		int length() const { return _size; }
		int capacity() const { return _capacity; }

		char* c_str() { return _ptr; }

		bool empty() const { return _size == 0; }

		/**
		 * @brief ����[]
		 * @param i �±�
		 * @return �±�i���ַ�������
		 */
		char& operator[](int i) {
			if (i < 0 || i >= _size) {
				std::cerr << "Out of size while reading.\n";
				exit(1);
			}
			return _ptr[i];
		}

		/**
		 * @brief ����[]��const����
		 * @param i �±�
		 * @return �±�i�����ַ���������
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
		 * @brief �Ƚ������ַ����Ƿ���ȣ��Ƚ�size���ַ����ݣ����Ƚ�capacity
		 */
		bool operator==(const string& s) {
			if (_size != s.size()) return false;
			for (int i = 0; i < _size; ++i) {
				if (_ptr[i] != s[i]) return false;
			}
			return true;
		}

		/**
		 * @brief �����ֵ���Ƚ������ַ���
		 */
		bool operator<(const string& s) {
			int len = s.size() < _size ? s.size() : _size;  // �϶��ַ����ĳ���
			for (int i = 0; i < len; ++i) {  // _ptr[i] == s[i]ʱ����ѭ��
				if (_ptr[i] < s[i]) return true;
				else if (_ptr[i] > s[i]) return false;
			}
			if (len == _size && len < s.size()) return true;
			return false;
		}

		bool operator<=(const string& s) {
			return *this == s || *this < s;
		}

		string operator+(const string& s) {
			string ans(_capacity + s.capacity());  // ��������֮�͹����µ�string����
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
		 * @brief ���ַ��������ַ�����ע���п��ܵ���s.append(s)��
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
		 * @brief ���ַ���β���ӵ����ַ�
		 */
		string& append(char c) {
			if (full()) _extend();
			_ptr[_size++] = c;
			return* this;
		}

		/**
		 * @brief ���ش�pos��ʼ����Ϊlen���Ӵ�
		 * @param pos ��ʼ�ַ����±�
		 * @param len �Ӵ�����
		 */
		string substr(int pos, int len) {
			if (pos + len > _size) {  // len�����߽�ʱ�ضϣ�ʽ��ȡ��ʱǡ�õ�string��ĩβ
				len = _size - pos;
			}
			return string(_ptr + pos, len);
		}

		/**
		 * @brief ���뵥���ַ�
		 * @param pos �����ַ���λ�ã�������Ǹ��ַ����±�
		 * @param c ��������ַ�
		 */
		string& insert(int pos, char c) {
			if (full()) _extend();
			for (int i = _size; i > pos; --i) _ptr[i] = _ptr[i - 1];
			_ptr[pos] = c;
			return *this;
		}
		/**
		 * @brief �����ַ���
		 * @param pos �������λ�ã�������Ǳ����봮���ַ����±�
		 * @param ps ��������ַ�������'\0'��β
		 */
		string& insert(int pos, const char* ps) {
			int len = strlen(ps);
			if (_size + len + 1 > _capacity) _extend(_size + len);
			for (int i = _size; i >= pos; --i) _ptr[i + len] = _ptr[i];  // �ַ������ƶ�len
			for (int i = 0; i < len; ++i) _ptr[i + pos] = ps[i];
			return *this;
		}

		/**
		 * @brief ɾ���Ӵ�
		 * @param pos ��ɾ���Ӵ�����ʼλ��
		 * @param len ��ɾ���Ӵ��ĳ���
		 */
		string& erase(int pos, int length) {
			if (pos >= _size) return;
			if (pos + length > _size) length = _size - pos;
			for (int i = pos; i < _size - length; ++i) _ptr[i] = _ptr[i + length];
			memset(_ptr + _size - length, 0, length);
			return *this;
		}

		/**
		 * @brief ����ַ�����ȫ��ֵ0��size��0��capacity���䡣
		 */
		void clear() {
			memset(_ptr, 0, _size);
			_size = 0;
		}

		/**
		 * @brief �����ֵ���Ƚ������ַ���
		 * @return *this-s�ķ��ţ�0����ȣ�1�����ң�-1�����ҡ�
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
		 * @brief �����ַ�c�������±�
		 * @return �����ҳɹ������±ꣻ����ʧ�ܷ���-1.
		 */
		int find(char c) {
			for (int i = 0; i < _size; ++i) {
				if (_ptr[i] == c) return i;
			}
			return -1;
		}

		/**
		 * @brief �����Ӵ�ps��������ʼ�ַ��±�
		 * @return �����ҳɹ�������ʼ�ַ��±ꣻ����ʧ�ܷ���-1.
		 */
		int find(const char* ps) {
			int len = strlen(ps);
			int i, j;
			for (i = 0; j < len &&  i < _size + 1 - len; ++i) {  // i + len <= _size
				// i Ϊ��ʼ�ַ�����_ptr�ƶ���ѭ��
				for (j = 0; j < len; ++j) {
					if (_ptr[i + j] != ps[j]) break;
				}
				// �����ҳɹ���j == len
			}
			if (j == len) return i;
			else return -1;
		}

		/**
		 * @brief ���ַ�����ʼλ��pos������length���Ӵ��滻Ϊps
		 */
		string& replace(int pos, int length, const char* ps) {
			int lenps = strlen(ps);
			int lenmin = lenps < length ? lenps : length;
			for (int i = 0; i < lenmin; ++i) {
				_ptr[i + pos] = ps[i];
			}
			if (lenmin < length) {  // lenps < length����Ҫɾ���м䲿��
				erase(pos + lenmin, length - lenmin);
			}
			else if (lenmin < lenps) {  // length < lenps����Ҫ�ٲ���psʣ�ಿ��
				insert(pos + lenmin, ps + lenmin);
			}
			return *this;
		}
	};
}