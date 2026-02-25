/*********************************************************************
 * \file   bstree.hpp
 * \brief  二叉搜索树的实现
 *
 * \author Mars
 * \date   February 2026
 *********************************************************************/
#pragma once
#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <stdexcept>
#include <utility>

namespace ms {

template <typename T> class BSTNode {
  public:
    T val;
    BSTNode *left, *right;

    BSTNode() : left(nullptr), right(nullptr) {}
    BSTNode(const T &t) : val(t), left(nullptr), right(nullptr) {}
    BSTNode(T &&t) : val(std::move(t)), left(nullptr), right(nullptr) {}
    BSTNode(BSTNode *pl, BSTNode *pr) : left(pl), right(pr) {}
    BSTNode(const T &t, BSTNode *pl, BSTNode *pr) : val(t), left(pl), right(pr) {}
    BSTNode(T &&t, BSTNode *pl, BSTNode *pr) : val(std::move(t)), left(pl), right(pr) {}
    ~BSTNode() {}
};

template <typename T> class BSTree {
  private:
    BSTNode<T> *_root;

    void destroy(BSTNode<T> *node) {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

  public:
    BSTree() : _root(nullptr) {}
    explicit BSTree(BSTNode<T> *root) : _root(root) {}
    ~BSTree() { destroy(_root); }

    BSTNode<T> *getRoot() const { return _root; }
    void setRoot(BSTNode<T> *root) { _root = root; }

    BSTNode<T> *search(const T &v) const {
        for (BSTNode<T> *p = _root; p;) {
            if (p->val == v) {
                return p;
            } else if (p->val < v) {
                p = p->right;
            } else {
                p = p->left;
            }
        }
        return nullptr;
    }

    const T &findMax() const {
        if (!_root) {
            throw std::out_of_range("findMax() while BSTree is empty.");
        }
        BSTNode<T> *p = _root;
        while (p->right)
            p = p->right;
        return p->val;
    }

    const T &findMin() const {
        if (!_root) {
            throw std::out_of_range("findMin() while BSTree is empty.");
        }
        BSTNode<T> *p = _root;
        while (p->left)
            p = p->left;
        return p->val;
    }

    void insert(BSTNode<T> *node) {
        if (!node)
            return;
        if (!_root) {
            _root = node;
            return;
        }
        for (BSTNode<T> *p = _root; p;) {
            if (p->val == node->val) {
                delete node;
                return;
            }
            if (p->val < node->val) {
                if (p->right) {
                    p = p->right;
                } else {
                    p->right = node;
                    return;
                }
            } else { // p->val > node->val
                if (p->left) {
                    p = p->left;
                } else {
                    p->left = node;
                    return;
                }
            }
        }
    }

    void insert(const T &v) { insert(new BSTNode<T>(v)); }

    void insert(T &&v) { insert(new BSTNode<T>(std::move(v))); }

    void remove(const T &v) {
        BSTNode<T> *p = _root;
        BSTNode<T> *parent = nullptr;

        while (p && p->val != v) {
            parent = p;
            if (v < p->val)
                p = p->left;
            else
                p = p->right;
        }
        if (!p)
            return;

        if (p->left && p->right) {
            BSTNode<T> *minParent = p;
            BSTNode<T> *minP = p->right;
            while (minP->left) {
                minParent = minP;
                minP = minP->left;
            }
            // 将最小节点的值赋给 p
            p->val = minP->val;
            // 要删除minP，所以把 p 指向 minP，parent 指向 minParent
            p = minP;
            parent = minParent;
        }

        // p 现在最多只有一个子节点
        BSTNode<T> *child = nullptr;
        if (p->left)
            child = p->left;
        else if (p->right)
            child = p->right;

        if (!parent) {
            _root = child;
        } else if (parent->left == p) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete p;
    }
};
} // namespace ms

#endif // BSTREE_HPP