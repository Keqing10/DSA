#include "Test.h"

#include <iostream>

#include "vector.hpp"
#include "list.hpp"

void ms::TestVec::run()
{
	ms::vector<int> v(10, 2);
	ms::vector<int> v2 = v;
	for (int i = 0; i < 10; ++i) {
		std::cout << i << " : " << v2[i] << std::endl;
	}

	ms::LNode<int> a(1), b;
	a.val = 1;
	a.next = &b;
	b.val = 2;
	ms::LNode<int>* p = a.reverse();
	while (p) {
		std::cout << "->" << p->val;
		p = p->next;
	}

	ms::DLNode<int> x, y;
	x.val = 1;
	x.next = &y;
	y.prev = &x;
	y.val = 2;
	ms::DLNode<int>* q = ms::reverse(&x);
	while (q) {
		std::cout << "->" << q->val;
		q = q->next;
	}
}
