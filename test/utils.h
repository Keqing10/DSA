#pragma once

#include <iostream>
#include <string>

void TestPrint(const std::string &);

namespace ms {
/**
 * @brief 中序遍历并输出节点值。
 *
 * 适用于拥有以下成员的二叉树节点类型：
 * - left
 * - right
 * - val
 *
 * 当前项目可直接用于：BiTree 的 BiTNode、BSTree 的 BSTNode、AVLTree 的 AVLTNode。
 */
template <typename Node> void print_inorder(Node *node) {
    if (!node)
        return;
    print_inorder(node->left);
    std::cout << node->val << " ";
    print_inorder(node->right);
}

class Student {
  public:
    int id; // 合法id为非负整数，-1表示未有效赋值
    bool male;
    std::string name;

    Student() : id(-1), male(false), name() {}
    Student(int _id, bool _male, std::string _name) : id(_id), male(_male), name(_name) {}
    Student(int _id, bool _male, const char *_name) : id(_id), male(_male) { name = std::string(_name); }
    Student(Student &stu) : id(stu.id), male(stu.male), name(stu.name) {}
    ~Student() {}

    void set(int _id, bool _male, std::string _name); // 重新设置成员变量
    void print();                                     // 输出成员变量信息

    bool operator<(const Student &stu) const; // 根据id排序
    void operator=(const Student &stu);
    void operator=(Student &&stu);
};
} // namespace ms

using Stu = ms::Student;
