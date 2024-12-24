#include <iostream>

#include "vector.h"

int main() {
	ms::vector v(10, 2);
	for (int i = 0; i < 10; ++i) {
		std::cout << i << " : " << v[i] << std::endl;
	}
}