#include "vector.h"

#include <iostream>

ms::vector::vector()
{
	_maxSize = 100;
	_size = 0;
	ptr = new int[_maxSize];
}

ms::vector::vector(int n)
{
	vector(n, 0);
}

ms::vector::vector(int n, int val)
{
	_maxSize = n < 50 ? 100 : n * 2;
	_size = n;
	ptr = new int[_maxSize];
	for (int i = 0; i < n; ++i) ptr[i] = val;
}

ms::vector::~vector()
{
	delete[] ptr;
}

int& ms::vector::operator[](int i)
{
	if (i < _size) return ptr[i];
	std::cout << "Out of size." << std::endl;
}
