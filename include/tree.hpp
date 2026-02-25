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

#include <queue>
#include <utility>
#include <vector>

namespace ms {
template <typename T> class TreeNode {
  public:
    T val;
    std::vector<TreeNode *> children;

    TreeNode() {}
    TreeNode(const T &t) : val(t) {}
    TreeNode(T &&t) : val(std::move(t)) {}
    TreeNode(const T &t, const std::vector<TreeNode *> &children) : val(t), children(children) {}
    TreeNode(T &&t, std::vector<TreeNode *> &&children) : val(std::move(t)), children(std::move(children)) {}
    ~TreeNode() = default;
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
            _preOrderRecursive(child, op);
    }

    void _postOrderRecursive(TreeNode<T> *node, TreeOp<T> op) {
        if (!node)
            return;
        for (TreeNode<T> *child : node->children)
            _postOrderRecursive(child, op);
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
        std::queue<TreeNode<T> *> q;
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