/*********************************************************************
 * \file   avltree.hpp
 * \brief  平衡二叉搜索树的实现
 *
 * \author Mars
 * \date   February 2026
 *********************************************************************/
#pragma once

#include "bitree.hpp"
#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <stdexcept>

#include "bstree.hpp"

namespace ms {

template <typename T> class AVLTNode : public BiTNode<T> {
  public:
    int height; // 以该节点为根的子树的高度

    AVLTNode(const T &v) : BiTNode<T>(v), height(1) {}
    AVLTNode(T &&v) : BiTNode<T>(v), height(1) {}
};

template <typename T> class AVLTree : public BSTree<T> {
  private:
    // 封装static_cast
    AVLTNode<T> *AVL(BiTNode<T> *node) const { return static_cast<AVLTNode<T> *>(node); }

    int getHeight(BiTNode<T> *node) const { return node ? AVL(node)->height : 0; }

    void updateHeight(BiTNode<T> *node) {
        if (node)
            AVL(node)->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(BiTNode<T> *node) const { return node ? getHeight(node->left) - getHeight(node->right) : 0; }

    /**
     * @brief 插入节点并返回新的子树根节点
     * @param node 当前子树的根节点
     * @param newNode 要插入的新节点
     */
    BiTNode<T> *_insert(BiTNode<T> *node, BiTNode<T> *newNode) {
        if (!node)
            return newNode;
        if (node->val < newNode->val) {
            node->right = _insert(node->right, newNode);
        } else if (node->val > newNode->val) {
            node->left = _insert(node->left, newNode);
        } else {
            return node; // 不允许重复
        }
        return reBalance(node);
    }

    /**
     * @brief 递归删除节点
     * @param node 当前子树根节点
     * @param v 要删除的值
     */
    BiTNode<T> *_remove(BiTNode<T> *node, const T &v) {
        if (!node)
            return nullptr;

        if (v < node->val) {
            node->left = _remove(node->left, v);
        } else if (v > node->val) {
            node->right = _remove(node->right, v);
        } else {
            // 找到节点
            if (!node->left || !node->right) {
                BiTNode<T> *temp = node->left ? node->left : node->right;
                if (!temp) { // 无子节点
                    delete node;
                    return nullptr;
                } else { // 一个子节点
                    delete node;
                    node = temp;
                }
            } else {
                // 两个子节点：找右子树最小节点
                BiTNode<T> *temp = node->right;
                while (temp->left)
                    temp = temp->left;
                node->val = temp->val;
                node->right = _remove(node->right, temp->val);
            }
        }

        return reBalance(node);
    }

  protected:
    /**
     * @brief 旋转操作
     *     y                               x
     *    / \     Right Rotation          /  \
     *   x   T3   - - - - - - - >        T1   y
     *  / \       < - - - - - - -            / \
     * T1  T2     Left Rotation             T2  T3
     *
     */
    AVLTNode<T> *rotateRight(BiTNode<T> *y) {
        if (!y || !y->left)
            return AVL(y);

        AVLTNode<T> *x = AVL(y->left);
        BiTNode<T> *T2 = x->right;

        // 旋转
        x->right = y;
        y->left = T2;

        // 更新高度
        updateHeight(y);
        updateHeight(x);

        return x; // 新的根节点
    }

    AVLTNode<T> *rotateLeft(BiTNode<T> *x) {
        if (!x || !x->right)
            return AVL(x);

        AVLTNode<T> *y = AVL(x->right);
        BiTNode<T> *T2 = y->left;

        // 旋转
        y->left = x;
        x->right = T2;

        // 更新高度
        updateHeight(x);
        updateHeight(y);

        return y; // 新的根节点
    }

    AVLTNode<T> *reBalance(BiTNode<T> *node) {
        if (!node)
            return nullptr;

        updateHeight(node);
        int balance = getBalanceFactor(node);

        // LL
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);

        // LR
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RR
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);

        // RL
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return AVL(node);
    }

  public:
    AVLTree() : BSTree<T>() {}
    explicit AVLTree(AVLTNode<T> *root) : BSTree<T>(root) {}
    ~AVLTree() = default;

    virtual void insert(AVLTNode<T> *node) {
        if (this->_root == nullptr) {
            this->_root = node;
            return;
        }
        if (this->_root == nullptr) {
            this->_root = node;
            return;
        }
        if (!node)
            return;
        this->_root = _insert(this->_root, node);
    }

    virtual void insert(BiTNode<T> *node) override { insert(AVL(node)); }

    virtual void insert(const T &v) override { insert(new AVLTNode<T>(v)); }

    virtual void insert(T &&v) override { insert(new AVLTNode<T>(v)); }

    virtual void remove(const T &v) { this->_root = _remove(this->_root, v); }
};
} // namespace ms

#endif // AVLTREE_HPP