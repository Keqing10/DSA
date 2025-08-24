/*********************************************************************
 * \file   list.hpp
 * \brief  链表实现：单链表，双链表
 *		   反转链表算法
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/

#include <iostream>

namespace ms {
    /**
     * @brief 单链表结点类
     */
    template <typename T>
    class LNode {
    public:
        T val;
        LNode* next;

        LNode() : val(T()), next(nullptr) {}
        LNode(T t) : val(t), next(nullptr) {}
        LNode(T t, LNode* p) : val(t), next(p) {}
        ~LNode() {}
    };

    /**
     * @brief 双链表结点类
     */
    template <typename T>
    class DLNode {
    public:
        T val;
        DLNode* prev, * next;

        DLNode() : val(T()), prev(nullptr), next(nullptr) {}
        DLNode(T t) : val(t), prev(nullptr), next(nullptr) {}
        DLNode(T t, DLNode* p) : val(t), prev(nullptr), next(p) {}
        DLNode(T t, DLNode* p1, DLNode* p2) : val(t), prev(p1), next(p2) {}
        ~DLNode() {}
    };

    /**
     * @brief 翻转链表，不带单独头结点
     * @param head 链表的第一个元素结点
     * @return LNode<T>* 翻转后的链表的第一个元素结点
     */
    template <typename T>
    LNode<T>* reverse(LNode<T>* head) {
        LNode<T> nh, * p = head, * q;
        while (p) {
            q = p->next;
            p->next = nh.next;
            nh.next = p;
            p = q;
        }
        return nh.next;
    }


    /**
     * @brief 翻转链表，不带单独头结点
     * @param head 链表的第一个元素结点
     * @return DLNode<T>* 翻转后的链表的第一个元素结点
     */
    template <typename T>
    DLNode<T>* reverse(DLNode<T>* head) {
        DLNode<T> nh, * p = head, * q;
        while (p) {
            q = p->next;
            p->next = nh.next;
            if (nh.next) nh.next->prev = p;
            nh.next = p;
            p->prev = nullptr;
            p = q;
        }
        return nh.next;
    }
}
