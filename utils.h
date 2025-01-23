#pragma once

#include <string>

namespace ms {
	class Student {
	public:
		int id;  // �Ϸ�idΪ�Ǹ�������-1��ʾδ��Ч��ֵ
		bool male;
		std::string name;

		Student() : id(-1), male(false), name() {}
		Student(int _id, bool _male, std::string _name) : id(_id), male(_male), name(_name) {}
		Student(int _id, bool _male, const char* _name) : id(_id), male(_male) { name = std::string(_name); }
		Student(Student& stu) : id(stu.id), male(stu.male), name(stu.name) {}
		~Student() {}

		void set(int _id, bool _male, std::string _name);  // �������ó�Ա����
		void print();  // �����Ա������Ϣ

		bool operator<(Student stu);  // ����id����
		void operator=(Student stu);
	};
}

using stu = ms::Student;

void TestPrint(const char* p);