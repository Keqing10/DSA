#include "utils.h"

#include <cstdio>

void TestPrint(const char* p) {
	printf("\n\033[0m\033[1;34m%s\033[0m %s\n", "[TEST]", p);  // blue
}

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
		printf("[Student] id = %d, %s, name = \"%s\".\n", id, male ? "male" : "female", name.c_str());
}

bool ms::Student::operator<(Student stu)
{
	if (id == stu.id && male == stu.male && name == stu.name) return true;
	// 完全相同时返回true，使得升序排序保持稳定性
	return id < stu.id;
}

void ms::Student::operator=(Student stu)
{
	id = stu.id;
	male = stu.male;
	name = stu.name;
}

