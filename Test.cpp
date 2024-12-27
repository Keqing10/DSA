#include "Test.h"

#include <iostream>

#include "vector.hpp"


void ms::TestVec::run()
{
	ms::vector<int> v(10, 2);
	for (int i = 0; i < 10; ++i) {
		std::cout << i << " : " << v[i] << std::endl;
	}
}
