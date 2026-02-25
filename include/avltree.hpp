/*********************************************************************
 * \file   avltree.hpp
 * \brief  平衡二叉搜索树的实现
 *
 * \author Mars
 * \date   February 2026
 *********************************************************************/
#pragma once
#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace ms {

template <typename T> class AVLTNode {
  public:
    T val;
    int height;
    AVLTNode *left, *right;

    AVLTNode() : val(T()), height(1), left(nullptr), right(nullptr) {}
    AVLTNode(const T &v) : val(v), height(1), left(nullptr), right(nullptr) {}
    AVLTNode(T &&v) : val(std::move(v)), height(1), left(nullptr), right(nullptr) {}
    ~AVLTNode() {}
};

template <typename T> class AVLTree {
  private:
    AVLTNode<T> *_root;

    void destroy(AVLTNode<T> *node) {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    int getHeight(AVLTNode<T> *node) const { return node ? node->height : 0; }

    void updateHeight(AVLTNode<T> *node) {
        if (node)
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(AVLTNode<T> *node) const { return node ? getHeight(node->left) - getHeight(node->right) : 0; }

    AVLTNode<T> *rotateRight(AVLTNode<T> *y) {
        if (!y || !y->left)
            return y;

        AVLTNode<T> *x = y->left;
        AVLTNode<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLTNode<T> *rotateLeft(AVLTNode<T> *x) {
        if (!x || !x->right)
            return x;

        AVLTNode<T> *y = x->right;
        AVLTNode<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLTNode<T> *reBalance(AVLTNode<T> *node) {
        if (!node)
            return nullptr;

        updateHeight(node);
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLTNode<T> *_insert(AVLTNode<T> *node, AVLTNode<T> *newNode) {
        if (!node)
            return newNode;

        if (node->val < newNode->val) {
            node->right = _insert(node->right, newNode);
        } else if (node->val > newNode->val) {
            node->left = _insert(node->left, newNode);
        } else {
            delete newNode;
            return node;
        }

        return reBalance(node);
    }

    AVLTNode<T> *_remove(AVLTNode<T> *node, const T &v) {
        if (!node)
            return nullptr;

        if (v < node->val) {
            node->left = _remove(node->left, v);
        } else if (v > node->val) {
            node->right = _remove(node->right, v);
        } else {
            if (!node->left || !node->right) {
                AVLTNode<T> *temp = node->left ? node->left : node->right;
                if (!temp) {
                    delete node;
                    return nullptr;
                }
                delete node;
                node = temp;
            } else {
                AVLTNode<T> *temp = node->right;
                while (temp->left)
                    temp = temp->left;
                node->val = temp->val;
                node->right = _remove(node->right, temp->val);
            }
        }

        return reBalance(node);
    }

  public:
    AVLTree() : _root(nullptr) {}
    explicit AVLTree(AVLTNode<T> *root) : _root(root) {}
    ~AVLTree() { destroy(_root); }

    AVLTNode<T> *getRoot() const { return _root; }
    void setRoot(AVLTNode<T> *root) { _root = root; }

    AVLTNode<T> *search(const T &v) const {
        for (AVLTNode<T> *p = _root; p;) {
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
            throw std::out_of_range("findMax() while AVLTree is empty.");
        }
        AVLTNode<T> *p = _root;
        while (p->right)
            p = p->right;
        return p->val;
    }

    const T &findMin() const {
        if (!_root) {
            throw std::out_of_range("findMin() while AVLTree is empty.");
        }
        AVLTNode<T> *p = _root;
        while (p->left)
            p = p->left;
        return p->val;
    }

    void insert(AVLTNode<T> *node) {
        if (!node)
            return;
        _root = _insert(_root, node);
    }

    void insert(const T &v) { insert(new AVLTNode<T>(v)); }

    void insert(T &&v) { insert(new AVLTNode<T>(std::move(v))); }

    void remove(const T &v) { _root = _remove(_root, v); }
};
} // namespace ms

#endif // AVLTREE_HPP
