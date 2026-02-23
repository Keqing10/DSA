/*********************************************************************
 * \file   list.hpp
 * \brief  链表实现：单链表，双链表
 *		   反转链表算法
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/
#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

namespace ms {
/**
 * @brief 单链表结点类
 */
template <typename T> class LNode {
  public:
    T val;
    LNode *next;

    LNode() : val(T()), next(nullptr) {}
    LNode(const T &t) : val(t), next(nullptr) {}
    LNode(T &&t) : val(std::move(t)), next(nullptr) {}
    LNode(const T &t, LNode *p) : val(t), next(p) {}
    LNode(T &&t, LNode *p) : val(std::move(t)), next(p) {}
    ~LNode() {}
};

/**
 * @brief 双链表结点类
 */
template <typename T> class DLNode {
  public:
    T val;
    DLNode *prev, *next;

    DLNode() : val(T()), prev(nullptr), next(nullptr) {}
    DLNode(const T &t) : val(t), prev(nullptr), next(nullptr) {}
    DLNode(T &&t) : val(std::move(t)), prev(nullptr), next(nullptr) {}
    DLNode(const T &t, DLNode *p) : val(t), prev(nullptr), next(p) {}
    DLNode(T &&t, DLNode *p) : val(std::move(t)), prev(nullptr), next(p) {}
    DLNode(const T &t, DLNode *p1, DLNode *p2) : val(t), prev(p1), next(p2) {}
    DLNode(T &&t, DLNode *p1, DLNode *p2) : val(std::move(t)), prev(p1), next(p2) {}
    ~DLNode() {}
};

/**
 * @brief 单链表容器类
 */
template <typename T> class forward_list {
  private:
    LNode<T> *_head;
    size_t _size;

  public:
    forward_list() : _head(nullptr), _size(0) {}

    forward_list(const forward_list &other) : _head(nullptr), _size(0) {
        if (!other._head)
            return;
        _head = new LNode<T>(other._head->val);
        LNode<T> *curr = _head;
        LNode<T> *other_curr = other._head->next;
        while (other_curr) {
            curr->next = new LNode<T>(other_curr->val);
            curr = curr->next;
            other_curr = other_curr->next;
        }
        _size = other._size;
    }

    forward_list &operator=(const forward_list &other) {
        if (this == &other)
            return *this;
        clear();
        if (!other._head)
            return *this;
        _head = new LNode<T>(other._head->val);
        LNode<T> *curr = _head;
        LNode<T> *other_curr = other._head->next;
        while (other_curr) {
            curr->next = new LNode<T>(other_curr->val);
            curr = curr->next;
            other_curr = other_curr->next;
        }
        _size = other._size;
        return *this;
    }

    ~forward_list() { clear(); }

    void clear() {
        while (_head) {
            LNode<T> *temp = _head;
            _head = _head->next;
            delete temp;
        }
        _size = 0;
    }

    inline size_t size() const { return _size; }
    inline bool empty() const { return _size == 0; }

    void push_front(const T &val) {
        _head = new LNode<T>(val, _head);
        ++_size;
    }

    void push_front(T &&val) {
        _head = new LNode<T>(std::move(val), _head);
        ++_size;
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front() on empty forward_list");
        }
        LNode<T> *temp = _head;
        _head = _head->next;
        delete temp;
        --_size;
    }

    T &front() {
        if (empty()) {
            throw std::out_of_range("front() on empty forward_list");
        }
        return _head->val;
    }

    const T &front() const {
        if (empty()) {
            throw std::out_of_range("front() on empty forward_list");
        }
        return _head->val;
    }

    void reverse() {
        LNode<T> nh, *p = _head, *q;
        while (p) {
            q = p->next;
            p->next = nh.next;
            nh.next = p;
            p = q;
        }
        _head = nh.next;
    }

    LNode<T> *get_head() const { return _head; }
};

/**
 * @brief 双向链表容器类
 */
template <typename T> class list {
  private:
    DLNode<T> *_head;
    DLNode<T> *_tail;
    size_t _size;

  public:
    list() : _head(nullptr), _tail(nullptr), _size(0) {}

    list(const list &other) : _head(nullptr), _tail(nullptr), _size(0) {
        DLNode<T> *curr = other._head;
        while (curr) {
            push_back(curr->val);
            curr = curr->next;
        }
    }

    list &operator=(const list &other) {
        if (this == &other)
            return *this;
        clear();
        DLNode<T> *curr = other._head;
        while (curr) {
            push_back(curr->val);
            curr = curr->next;
        }
        return *this;
    }

    ~list() { clear(); }

    void clear() {
        while (_head) {
            DLNode<T> *temp = _head;
            _head = _head->next;
            delete temp;
        }
        _tail = nullptr;
        _size = 0;
    }

    inline size_t size() const { return _size; }
    inline bool empty() const { return _size == 0; }

    void push_back(const T &val) {
        DLNode<T> *newNode = new DLNode<T>(val, _tail, nullptr);
        if (_tail) {
            _tail->next = newNode;
        } else {
            _head = newNode;
        }
        _tail = newNode;
        ++_size;
    }

    void push_back(T &&val) {
        DLNode<T> *newNode = new DLNode<T>(std::move(val), _tail, nullptr);
        if (_tail) {
            _tail->next = newNode;
        } else {
            _head = newNode;
        }
        _tail = newNode;
        ++_size;
    }

    void push_front(const T &val) {
        DLNode<T> *newNode = new DLNode<T>(val, nullptr, _head);
        if (_head) {
            _head->prev = newNode;
        } else {
            _tail = newNode;
        }
        _head = newNode;
        ++_size;
    }

    void push_front(T &&val) {
        DLNode<T> *newNode = new DLNode<T>(std::move(val), nullptr, _head);
        if (_head) {
            _head->prev = newNode;
        } else {
            _tail = newNode;
        }
        _head = newNode;
        ++_size;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back() on empty list");
        }
        DLNode<T> *temp = _tail;
        _tail = _tail->prev;
        if (_tail) {
            _tail->next = nullptr;
        } else {
            _head = nullptr;
        }
        delete temp;
        --_size;
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front() on empty list");
        }
        DLNode<T> *temp = _head;
        _head = _head->next;
        if (_head) {
            _head->prev = nullptr;
        } else {
            _tail = nullptr;
        }
        delete temp;
        --_size;
    }

    T &front() {
        if (empty()) {
            throw std::out_of_range("front() on empty list");
        }
        return _head->val;
    }

    const T &front() const {
        if (empty()) {
            throw std::out_of_range("front() on empty list");
        }
        return _head->val;
    }

    T &back() {
        if (empty()) {
            throw std::out_of_range("back() on empty list");
        }
        return _tail->val;
    }

    const T &back() const {
        if (empty()) {
            throw std::out_of_range("back() on empty list");
        }
        return _tail->val;
    }

    void reverse() {
        DLNode<T> nh, *p = _head, *q;
        while (p) {
            q = p->next;
            p->next = nh.next;
            if (nh.next)
                nh.next->prev = p;
            nh.next = p;
            p->prev = nullptr;
            p = q;
        }
        _head = nh.next;
        // 翻转后，原来的头变成了尾，原来的尾变成了头
        _tail = _head;
        while (_tail && _tail->next) {
            _tail = _tail->next;
        }
    }

    DLNode<T> *get_head() const { return _head; }
    DLNode<T> *get_tail() const { return _tail; }
};

} // namespace ms
