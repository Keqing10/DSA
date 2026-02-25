/*********************************************************************
 * \file   bitree.hpp
 * \brief  二叉树的实现及其遍历算法
 *
 * \author Mars
 * \date   August 2025
 *********************************************************************/
#pragma once
#ifndef BITREE_HPP
#define BITREE_HPP

#include <queue>
#include <stack>
#include <utility>

namespace ms {
/**
 * @brief 二叉树结点类
 */
template <typename T> class BiTNode {
  public:
    T val;
    BiTNode *left, *right;

    BiTNode() : left(nullptr), right(nullptr) {}
    BiTNode(const T &t) : val(t), left(nullptr), right(nullptr) {}
    BiTNode(T &&t) : val(std::move(t)), left(nullptr), right(nullptr) {}
    BiTNode(BiTNode *pl, BiTNode *pr) : left(pl), right(pr) {}
    BiTNode(const T &t, BiTNode *pl, BiTNode *pr) : val(t), left(pl), right(pr) {}
    BiTNode(T &&t, BiTNode *pl, BiTNode *pr) : val(std::move(t)), left(pl), right(pr) {}
    ~BiTNode() {}
};

/**
 * @brief 对二叉树结点进行操作的函数指针
 * @tparam T
 */
template <typename T> using BiTOp = void (*)(BiTNode<T> *);

/**
 * @brief 二叉树类
 */
template <typename T> class BiTree {
  private:
    BiTNode<T> *_root;

    void _destroy(BiTNode<T> *node) {
        if (!node)
            return;
        _destroy(node->left);
        _destroy(node->right);
        delete node;
    }

    void _preOrderRecursive(BiTNode<T> *node, BiTOp<T> op) {
        if (!node)
            return;
        op(node);
        _preOrderRecursive(node->left, op);
        _preOrderRecursive(node->right, op);
    }

    void _inOrderRecursive(BiTNode<T> *node, BiTOp<T> op) {
        if (!node)
            return;
        _inOrderRecursive(node->left, op);
        op(node);
        _inOrderRecursive(node->right, op);
    }

    void _postOrderRecursive(BiTNode<T> *node, BiTOp<T> op) {
        if (!node)
            return;
        _postOrderRecursive(node->left, op);
        _postOrderRecursive(node->right, op);
        op(node);
    }

  public:
    BiTree() : _root(nullptr) {}
    BiTree(BiTNode<T> *root) : _root(root) {}
    virtual ~BiTree() { _destroy(_root); }

    BiTNode<T> *getRoot() const { return _root; }
    void setRoot(BiTNode<T> *root) { _root = root; }

    /**
     * @brief 先序遍历，递归形式
     */
    void preOrderRecursive(BiTOp<T> op) { _preOrderRecursive(_root, op); }

    /**
     * @brief 先序遍历，迭代形式
     */
    void preOrderIterative(BiTOp<T> op) {
        if (!_root)
            return;
        std::stack<BiTNode<T> *> stk;
        stk.push(_root);
        while (!stk.empty()) {
            BiTNode<T> *p = stk.top();
            stk.pop();
            op(p);
            if (p->right)
                stk.push(p->right);
            if (p->left)
                stk.push(p->left);
        }
    }

    /**
     * @brief 中序遍历，递归形式
     */
    void inOrderRecursive(BiTOp<T> op) { _inOrderRecursive(_root, op); }

    /**
     * @brief 中序遍历，迭代形式
     */
    void inOrderIterative(BiTOp<T> op) {
        if (!_root)
            return;
        std::stack<BiTNode<T> *> stk;
        BiTNode<T> *curr = _root;
        while (!stk.empty() || curr) {
            while (curr) {
                stk.push(curr);
                curr = curr->left;
            }
            curr = stk.top();
            stk.pop();
            op(curr);
            curr = curr->right;
        }
    }

    /**
     * @brief 后序遍历，递归形式
     */
    void postOrderRecursive(BiTOp<T> op) { _postOrderRecursive(_root, op); }

    /**
     * @brief 层次遍历，迭代形式
     */
    void levelOrder(BiTOp<T> op) {
        if (!_root)
            return;
        std::queue<BiTNode<T> *> que;
        que.push(_root);
        while (!que.empty()) {
            BiTNode<T> *curr = que.front();
            que.pop();
            op(curr);
            if (curr->left)
                que.push(curr->left);
            if (curr->right)
                que.push(curr->right);
        }
    }
};
} // namespace ms

#endif // BITREE_HPP
