#include "Test.h"

#include <cstdio>
#include <functional>
#include <iostream>
#include <string>

#include "bitree.hpp"
#include "bstree.hpp"
#include "list.hpp"
#include "queue.hpp"
#include "sort.hpp"
#include "stack.hpp"
#include "string.hpp"
#include "utils.h"
#include "vector.hpp"

void ms::run_test() {
    test_vector();
    test_list();
    test_stack();
    test_queue();
    test_string();
    test_bitree();
    test_bstree();
    test_sort();
}

void ms::test_vector() {
    TestPrint(">> vector");
    TestPrint("constructor");

    ms::vector<int> v0;
    std::cout << "v0: size = " << v0.size() << ", maxSize = " << v0.maxSize() << std::endl;
    ms::vector<int> v1(10, 2);
    ms::vector<int> v2(v1);
    std::cout << "v2: size = " << v2.size() << ", maxSize = " << v2.maxSize() << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "v2[" << i << "] = " << v2[i] << std::endl;
    }
    ms::vector<Stu> v3(5, Stu(0, true, "test"));
    std::cout << "v3:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "v3[" << i << "] : ";
        v3[i].print();
    }

    TestPrint("assign()");
    v2.assign(100, 3);
    std::cout << "v2: size = " << v2.size() << ", maxSize = " << v2.maxSize() << std::endl;
    for (int i = 0; i < 100; ++i) {
        if (v2[i] != 3)
            std::cout << "There is an elem != 3 after assign()!\n";
    }

    TestPrint("operator=");
    ms::vector<Stu> v4 = v3;
    std::cout << "v4:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "v4[" << i << "] : ";
        v4[i].print();
    }

    TestPrint("push_back(), pop_back(), insert(), erase()");
    v4.clear();
    v4.push_back(Stu(1, true, "alpha"));
    v4.push_back(Stu(3, false, "gamma"));
    v4.insert(1, Stu(2, true, "beta"));
    v4.push_back(Stu(4, false, "delta"));
    std::cout << "size:" << v4.size() << "\n";
    v4.insert(3, Stu());
    v4.erase(3);
    std::cout << "v4:\n";
    for (int i = 0; i < v4.size(); ++i) {
        std::cout << "v4[" << i << "] : ";
        v4[i].print();
    }

    TestPrint("get_ptr()");
    Stu *p = v4.get_ptr();
    p->print();
}

void ms::test_list() {
    TestPrint(">> forward_list");
    ms::forward_list<int> fl;
    for (int i = 1; i <= 5; ++i) {
        fl.push_front(i);
    }
    ms::LNode<int> *fl_head = fl.get_head();
    while (fl_head) {
        std::cout << fl_head->val << " ";
        fl_head = fl_head->next;
    }
    std::cout << "\n";
    fl.reverse();
    fl_head = fl.get_head();
    while (fl_head) {
        std::cout << fl_head->val << " ";
        fl_head = fl_head->next;
    }
    std::cout << "\n";

    TestPrint(">> list");
    ms::list<int> l;
    for (int i = 1; i <= 5; ++i) {
        l.push_back(i);
    }
    l.push_front(0);
    ms::DLNode<int> *l_head = l.get_head();
    while (l_head) {
        std::cout << l_head->val << " ";
        l_head = l_head->next;
    }
    std::cout << "\n";
    l.pop_back();
    l.pop_front();
    l.reverse();
    l_head = l.get_head();
    while (l_head) {
        std::cout << l_head->val << " ";
        l_head = l_head->next;
    }
    std::cout << "\n";
}

void ms::test_stack() {
    TestPrint(">> stack");
    ms::stack<int> st;
    for (int i = 1; i <= 5; ++i) {
        st.push(i);
    }
    std::cout << "stack pop: ";
    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << "\n";
}

void ms::test_queue() {
    TestPrint(">> deque");
    ms::deque<int> dq;
    dq.push_back(1);
    dq.push_front(2);
    dq.push_back(3); // 2 1 3
    std::cout << "deque pop_front: ";
    while (!dq.empty()) {
        std::cout << dq.pop_front() << " ";
    }
    std::cout << "\n";

    TestPrint(">> queue");
    ms::queue<int> q;
    for (int i = 1; i <= 5; ++i) {
        q.push(i);
    }
    std::cout << "queue pop: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";

    TestPrint(">> priority_queue");
    ms::priority_queue<int> pq;
    pq.push(3);
    pq.push(5);
    pq.push(1);
    pq.push(4);
    pq.push(2);
    std::cout << "priority_queue pop: ";
    while (!pq.empty()) {
        std::cout << pq.pop() << " "; // 默认大根堆，输出应为 5 4 3 2 1
    }
    std::cout << "\n";
}

void ms::test_string() {
    TestPrint(">> string");
    ms::string s1("hello");
    ms::string s2(" world");
    s1.append(s2);
    std::cout << "s1 append s2: " << s1 << "\n";

    s1.insert(5, ",");
    std::cout << "s1 insert ',': " << s1 << "\n";

    s1.erase(5, 1);
    std::cout << "s1 erase ',': " << s1 << "\n";

    int pos = s1.find("world");
    std::cout << "find 'world' at: " << pos << "\n";

    ms::string s3 = std::move(s1);
    std::cout << "s3 move from s1: " << s3 << "\n";
    std::cout << "s1 after move: " << (s1.c_str() ? s1 : ms::string("null")) << "\n";
}

void ms::test_bitree() {
    TestPrint(">> BiTree");
    // Construct a simple binary tree:
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    ms::BiTNode<int> *n4 = new ms::BiTNode<int>(4);
    ms::BiTNode<int> *n5 = new ms::BiTNode<int>(5);
    ms::BiTNode<int> *n6 = new ms::BiTNode<int>(6);
    ms::BiTNode<int> *n2 = new ms::BiTNode<int>(2, n4, n5);
    ms::BiTNode<int> *n3 = new ms::BiTNode<int>(3, nullptr, n6);
    ms::BiTNode<int> *root = new ms::BiTNode<int>(1, n2, n3);

    ms::BiTree<int> tree(root);

    auto print_node = [](ms::BiTNode<int> *node) { std::cout << node->val << " "; };

    std::cout << "preOrderRecursive: ";
    tree.preOrderRecursive(print_node);
    std::cout << "\n";

    std::cout << "preOrderIterative: ";
    tree.preOrderIterative(print_node);
    std::cout << "\n";

    std::cout << "inOrderRecursive: ";
    tree.inOrderRecursive(print_node);
    std::cout << "\n";

    std::cout << "inOrderIterative: ";
    tree.inOrderIterative(print_node);
    std::cout << "\n";

    std::cout << "postOrderRecursive: ";
    tree.postOrderRecursive(print_node);
    std::cout << "\n";

    std::cout << "levelOrder: ";
    tree.levelOrder(print_node);
    std::cout << "\n";

    // Clean up is handled by BiTree destructor
}

void ms::test_bstree() {
    TestPrint(">> BSTree");
    ms::BSTree<int> bst;

    // 插入测试
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    for (int x : arr) {
        bst.insert(x);
    }

    auto print_node = [](ms::BiTNode<int> *node) { std::cout << node->val << " "; };

    std::cout << "inOrder (should be sorted): ";
    bst.inOrderIterative(print_node);
    std::cout << "\n";

    // 最值测试
    std::cout << "Min: " << bst.findMin() << ", Max: " << bst.findMax() << "\n";

    // 查找测试
    std::cout << "Search 4: " << (bst.search(4) ? "Found" : "Not Found") << "\n";
    std::cout << "Search 9: " << (bst.search(9) ? "Found" : "Not Found") << "\n";

    // 删除测试
    std::cout << "Remove 2 (leaf):\n";
    bst.remove(2);
    bst.inOrderIterative(print_node);
    std::cout << "\n";

    std::cout << "Remove 3 (one child):\n";
    bst.remove(3);
    bst.inOrderIterative(print_node);
    std::cout << "\n";

    std::cout << "Remove 5 (two children, root):\n";
    bst.remove(5);
    bst.inOrderIterative(print_node);
    std::cout << "\n";
}

void ms::test_sort() {
    TestPrint(">> sort");
    ms::vector<int> v{5, 2, 9, 1, 5, 6, 8, 3, 7, 4};

    auto test_algorithm = [&v](const char *name, std::function<void(int *, size_t)> sort_func) {
        ms::vector<int> temp{v};
        sort_func(temp.get_ptr(), temp.size());
        std::cout << name << ": ";
        for (size_t i = 0; i < temp.size(); ++i) {
            std::cout << temp[i] << " ";
        }
        std::cout << "\n";
    };

    test_algorithm("bubbleSort", ms::sortBubble<int>);
    test_algorithm("quickSort", ms::sortQuick<int>);
    test_algorithm("insertSort", ms::sortInsert<int>);
    test_algorithm("shellSort", ms::sortShell<int>);
    test_algorithm("checkSort", ms::sortCheck<int>);
    test_algorithm("heapSort", ms::sortHeap<int>);
    test_algorithm("mergeSort", ms::sortMerge<int>);
}
