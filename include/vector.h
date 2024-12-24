#pragma once

namespace ms {
	class vector {
	private:
		int _maxSize, _size;
		int* ptr;
	public:
		vector();
		vector(int n);
		vector(int n, int val);
		~vector();

		int& operator[](int i);

	};
}