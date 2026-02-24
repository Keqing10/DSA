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

#include "bitree.hpp"

namespace ms {

template <typename T> class BSTree : public BiTree<T> {
  public:
    BSTree() : BiTree<T>() {}
    BSTree(BiTNode<T> *root) : BiTree<T>(root) {}
    ~BSTree() = default;

    virtual BiTNode<T> *search(const T &v) const {
        if (!this->_root)
            return nullptr;
        for (BiTNode<T> *p = this->_root; p;) {
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

    virtual const T &findMax() const {
        if (!this->_root) {
            throw std::out_of_range("findMax() while BSTree is empty.");
        }
        BiTNode<T> *p = this->_root;
        while (p->right)
            p = p->right;
        return p->val;
    }

    virtual const T &findMin() const {
        if (!this->_root) {
            throw std::out_of_range("findMin() while BSTree is empty.");
        }
        BiTNode<T> *p = this->_root;
        while (p->left)
            p = p->left;
        return p->val;
    }

    virtual void insert(BiTNode<T> *node) {
        if (!this->_root) {
            this->_root = node;
            return;
        }
        for (auto p = this->_root; p;) {
            if (p->val == node->val) {
                delete node; // 避免内存泄漏
                return;      // 不允许存在相同元素
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

    virtual void insert(const T &v) { insert(new BiTNode<T>(v)); }

    virtual void insert(T &&v) { insert(new BiTNode<T>(v)); }

    virtual void remove(const T &v) {
        BiTNode<T> *p = this->_root;
        BiTNode<T> *parent = nullptr;

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
            // 找右子树的最小节点 (minP) 及其父节点 (minParent)
            BiTNode<T> *minParent = p;
            BiTNode<T> *minP = p->right;
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
        BiTNode<T> *child = nullptr;
        if (p->left)
            child = p->left;
        else if (p->right)
            child = p->right;

        // 执行删除并重新连接父节点
        if (!parent) { // 如果 parent 为空，说明要删除的是根节点
            this->_root = child;
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