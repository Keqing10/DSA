/*********************************************************************
 * \file   tree.hpp
 * \brief  树的实现及其遍历算法
 *
 * \author Mars
 * \date   February 2026
 *********************************************************************/
#pragma once

#ifndef TREE_HPP
#define TREE_HPP

#include "queue.hpp"
#include "tree.hpp"
#include "vector.hpp"

namespace ms {
template <typename T> class TreeNode {
  public:
    T val;
    vector<TreeNode *> children;

    TreeNode() {}
    TreeNode(const T &t) : val(t) {}
    TreeNode(T &&t) : val(std::move(t)) {}
    ~TreeNode() {}
};

template <typename T> using TreeOp = void (*)(TreeNode<T> *);

template <typename T> class Tree {
  private:
    TreeNode<T> *_root;

    void _destroy(TreeNode<T> *node) {
        if (!node)
            return;
        for (TreeNode<T> *child : node->children)
            _destroy(child);
        delete node;
    }

    void _preOrderRecursive(TreeNode<T> *node, TreeOp<T> op) {
        if (!node)
            return;
        op(node);
        for (TreeNode<T> *child : node->children)
            _preOrder(child, op);
    }

    void _postOrderRecursive(TreeNode<T> *node, TreeOp<T> op) {
        if (!node)
            return;
        for (TreeNode<T> *child : node->children)
            _postOrder(child, op);
        op(node);
    }

  public:
    Tree() : _root(nullptr) {}
    explicit Tree(TreeNode<T> *root) : _root(root) {}
    ~Tree() { _destroy(_root); }

    void setRoot(TreeNode<T> *root) { _root = root; }
    TreeNode<T> *getRoot() const { return _root; }

    /**
     * @brief 递归前序遍历
     */
    void preOrder(TreeOp<T> op) { _preOrderRecursive(_root, op); }

    /**
     * @brief 递归后序遍历
     */
    void postOrder(TreeOp<T> op) { _postOrderRecursive(_root, op); }

    /**
     *  @brief 层序遍历
     */
    void levelOrder(TreeOp<T> op) {
        if (!_root)
            return;
        queue<TreeNode<T> *> q;
        q.push(_root);
        while (!q.empty()) {
            TreeNode<T> *node = q.front();
            q.pop();
            op(node);
            for (TreeNode<T> *child : node->children)
                q.push(child);
        }
    }
};

} // namespace ms

#endif // TREE_HPP