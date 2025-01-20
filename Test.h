#pragma once

#include "string"

namespace ms {
	class Student {
	public:
		int id;  // 合法id为非负整数，-1表示未有效赋值
		bool male;
		std::string name;
		
		Student() : id(-1), male(false), name() {}
		Student(int _id, bool _male, std::string _name) : id(_id), male(_male), name(_name) {}
		Student(int _id, bool _male, const char* _name) : id(_id), male(_male) { name = std::string(_name); }
		~Student() {}

		void set(int _id, bool _male, std::string _name);  // 重新设置成员变量
		void print();  // 输出成员变量信息

		bool operator<(Student stu);
	};

	class Test {
	public:
		Test() {}
		~Test() {}
		static void run();

		static void test_vector();
		static void test_list();
		static void test_stack();
		static void test_queue();
		static void test_string();
		static void test_tree();
		static void test_sort();
	};
}