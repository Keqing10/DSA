#include "Test.h"

#include <cstdio>
#include <iostream>

#include "list.hpp"
#include "queue.hpp"
#include "sort.h"
#include "stack.hpp"
#include "string.hpp"
#include "tree.hpp"
#include "vector.hpp"

void ms::Student::set(int _id, bool _male, std::string _name)
{
	id = _id;
	male = _male;
	name = _name;
}

void ms::Student::print()
{
	if (id == -1)
		printf("[Student] NULL.\n");
	else
		printf("[Student] id = %d, %s, name = %s.\n", id, male ? "male" : "female", name.c_str());
}

bool ms::Student::operator<(Student stu)
{
	//if (id == stu.id) return name < stu.name;  // 应不允许出现相同id
	return id < stu.id;
}

void ms::Test::run()
{
	test_vector();
	//test_list();
	//test_stack();
	//test_queue();
	//test_string();
	//test_tree();
	//test_sort();
}

void ms::Test::test_vector()
{
	ms::vector<int> v(10, 2);
	ms::vector<int> v2 = v;
	for (int i = 0; i < 10; ++i) {
		std::cout << i << " : " << v2[i] << std::endl;
	}

}

void ms::Test::test_list()
{
	//ms::LNode<int> a(1), b;
	//a.val = 1;
	//a.next = &b;
	//b.val = 2;
	//ms::LNode<int>* p = a.reverse();
	//while (p) {
	//	std::cout << "->" << p->val;
	//	p = p->next;
	//}

	//ms::DLNode<int> x, y;
	//x.val = 1;
	//x.next = &y;
	//y.prev = &x;
	//y.val = 2;
	//ms::DLNode<int>* q = ms::reverse(&x);
	//while (q) {
	//	std::cout << "->" << q->val;
	//	q = q->next;
	//}

}

void ms::Test::test_stack()
{
}

void ms::Test::test_queue()
{
}

void ms::Test::test_string()
{
}

void ms::Test::test_tree()
{
}

void ms::Test::test_sort()
{
}
