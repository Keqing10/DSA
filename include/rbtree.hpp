/*********************************************************************
 * \file   rbtree.hpp
 * \brief  红黑树的实现
 *
 * 红黑树是一种自平衡二叉搜索树，满足以下性质:
 * 1. 每个节点是红色或黑色
 * 2. 根节点是黑色
 * 3. 所有叶子节点（NIL）是黑色
 * 4. 红色节点的两个子节点都是黑色（不能有连续的红色节点）
 * 5. 从任意节点到其所有叶子节点的路径包含相同数量的黑色节点
 *
 * 实现特点:
 * - 使用哨兵节点(NIL)简化边界条件
 * - 支持插入、删除、搜索、最值查询等操作
 * - 保持O(log n)的时间复杂度
 *
 * \author Mars
 * \date   February 2026
 *********************************************************************/
#pragma once
#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <stdexcept>
#include <utility>

namespace ms {

enum class Color : char { RED, BLACK };

template <typename T> class RBTNode {
  public:
    T val;
    Color color;
    RBTNode *left, *right, *parent;

    RBTNode() : val(T()), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
    RBTNode(const T &v) : val(v), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
    RBTNode(T &&v) : val(std::move(v)), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
    ~RBTNode() {}
};

template <typename T> class RBTree {
  private:
    RBTNode<T> *_root;
    RBTNode<T> *_nil; // 哨兵节点，表示空叶子节点（黑色）

    // 销毁子树
    void destroy(RBTNode<T> *node) {
        if (node == _nil)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    /**
     * @brief 左旋操作
     *
     * 左旋示意图:
     *      x               y
     *     / \             / \
     *    α   y    =>     x   γ
     *       / \         / \
     *      β   γ       α   β
     *
     * 操作步骤:
     * 1. 将y的左子树β变为x的右子树
     * 2. 将x的父节点设置为y的父节点
     * 3. 将x设置为y的左子树
     *
     * @param x 旋转的支点节点
     */
    void leftRotate(RBTNode<T> *x) {
        if (x == _nil || x->right == _nil)
            return;

        RBTNode<T> *y = x->right; // 设置y为x的右孩子
        x->right = y->left;       // 将y的左子树变为x的右子树

        if (y->left != _nil)
            y->left->parent = x;

        y->parent = x->parent; // 将x的父节点赋给y

        if (x->parent == _nil) {
            _root = y; // 如果x是根节点，则y成为新根
        } else if (x == x->parent->left) {
            x->parent->left = y; // 如果x是其父节点的左孩子
        } else {
            x->parent->right = y; // 如果x是其父节点的右孩子
        }

        y->left = x; // 将x放在y的左边
        x->parent = y;
    }

    /**
     * @brief 右旋操作
     *
     * 右旋示意图:
     *        y               x
     *       / \             / \
     *      x   γ    =>     α   y
     *     / \                 / \
     *    α   β               β   γ
     *
     * 操作步骤:
     * 1. 将x的右子树β变为y的左子树
     * 2. 将y的父节点设置为x的父节点
     * 3. 将y设置为x的右子树
     *
     * @param y 旋转的支点节点
     */
    void rightRotate(RBTNode<T> *y) {
        if (y == _nil || y->left == _nil)
            return;

        RBTNode<T> *x = y->left; // 设置x为y的左孩子
        y->left = x->right;      // 将x的右子树变为y的左子树

        if (x->right != _nil)
            x->right->parent = y;

        x->parent = y->parent; // 将y的父节点赋给x

        if (y->parent == _nil) {
            _root = x; // 如果y是根节点，则x成为新根
        } else if (y == y->parent->left) {
            y->parent->left = x; // 如果y是其父节点的左孩子
        } else {
            y->parent->right = x; // 如果y是其父节点的右孩子
        }

        x->right = y; // 将y放在x的右边
        y->parent = x;
    }

    /**
     * @brief 插入后修复红黑性质
     *
     * 红黑树插入后可能违反的性质:
     * 1. 根节点必须是黑色（如果插入的节点成为根，直接染黑）
     * 2. 红色节点的子节点必须是黑色（可能违反）
     *
     * 修复情况（父节点是祖父节点的左孩子）:
     *
     * Case 1: 叔叔节点是红色
     *         G(B)                 G(R)
     *        /   \                /   \
     *      P(R)  U(R)   =>     P(B)  U(B)
     *      /                   /
     *    Z(R)                Z(R)
     * 操作: 父节点和叔叔节点染黑，祖父节点染红，z指向祖父节点继续修复
     *
     * Case 2: 叔叔节点是黑色，z是右孩子
     *         G(B)                 G(B)
     *        /   \                /   \
     *      P(R)  U(B)   =>     Z(R)  U(B)
     *        \                 /
     *        Z(R)            P(R)
     * 操作: z指向父节点，左旋，转换为Case 3
     *
     * Case 3: 叔叔节点是黑色，z是左孩子
     *         G(B)                 P(B)
     *        /   \                /   \
     *      P(R)  U(B)   =>     Z(R)  G(R)
     *      /                           \
     *    Z(R)                          U(B)
     * 操作: 父节点染黑，祖父节点染红，右旋祖父节点
     *
     * 对称情况（父节点是祖父节点的右孩子）类似处理
     *
     * @param z 新插入的节点（红色）
     */
    void insertFixup(RBTNode<T> *z) {
        while (z != _root && isRed(z->parent)) {
            if (z->parent == z->parent->parent->left) {
                RBTNode<T> *y = z->parent->parent->right; // 叔叔节点
                if (isRed(y)) {
                    // Case 1: 叔叔是红色
                    setColor(z->parent, Color::BLACK);
                    setColor(y, Color::BLACK);
                    setColor(z->parent->parent, Color::RED);
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2: 叔叔是黑色，z是右孩子
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: 叔叔是黑色，z是左孩子
                    setColor(z->parent, Color::BLACK);
                    setColor(z->parent->parent, Color::RED);
                    rightRotate(z->parent->parent);
                }
            } else {
                // 对称情况：父节点是右孩子
                RBTNode<T> *y = z->parent->parent->left; // 叔叔节点
                if (isRed(y)) {
                    // Case 1: 叔叔是红色
                    setColor(z->parent, Color::BLACK);
                    setColor(y, Color::BLACK);
                    setColor(z->parent->parent, Color::RED);
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        // Case 2: 叔叔是黑色，z是左孩子
                        z = z->parent;
                        rightRotate(z);
                    }
                    // Case 3: 叔叔是黑色，z是右孩子
                    setColor(z->parent, Color::BLACK);
                    setColor(z->parent->parent, Color::RED);
                    leftRotate(z->parent->parent);
                }
            }
        }
        setColor(_root, Color::BLACK); // 根节点总是黑色
    }

    // 用v子树替换u子树
    void transplant(RBTNode<T> *u, RBTNode<T> *v) {
        if (u->parent == _nil) {
            _root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent; // 哨兵节点的 parent 也必须更新，deleteFixup 依赖此值
    }

    // 查找子树最小节点
    RBTNode<T> *minimum(RBTNode<T> *node) {
        while (node->left != _nil)
            node = node->left;
        return node;
    }

    /**
     * @brief 删除后修复红黑性质
     *
     * 红黑树删除后可能违反的性质:
     * 1. 如果删除的是红色节点，不影响红黑性质
     * 2. 如果删除的是黑色节点，可能导致黑高减少
     *
     * 修复情况（x是父节点的左孩子，w是兄弟节点）:
     *
     * Case 1: 兄弟节点w是红色
     *        P(B)                 W(B)
     *       /   \                /   \
     *     X(B)  W(R)    =>    P(R)  WR(B)
     *          /   \          /   \
     *        WL(B) WR(B)   X(B)  WL(B)
     * 操作: w染黑，p染红，左旋p，重新设置兄弟节点
     *
     * Case 2: 兄弟节点w是黑色，且w的两个孩子都是黑色
     *        P(?)                 P(?)  // ?表示颜色不变
     *       /   \                /   \
     *     X(B)  W(B)    =>    X(B)  W(R)
     *          /   \                /   \
     *        WL(B) WR(B)        WL(B) WR(B)
     * 操作: w染红，x指向p，继续循环
     *
     * Case 3: 兄弟节点w是黑色，w的左孩子红色，右孩子黑色
     *        P(?)                 P(?)
     *       /   \                /   \
     *     X(B)  W(B)    =>    X(B)  WL(B)
     *          /   \                    \
     *        WL(R) WR(B)               W(R)
     *                                    \
     *                                   WR(B)
     * 操作: w的左孩子染黑，w染红，右旋w，重新设置兄弟节点
     *
     * Case 4: 兄弟节点w是黑色，w的右孩子红色
     *        P(?)                 W(?)
     *       /   \                /   \
     *     X(B)  W(B)    =>    P(B)  WR(B)
     *          /   \          /   \
     *        WL(?) WR(R)   X(B)  WL(?)
     * 操作: w的颜色设置为p的颜色，p染黑，w的右孩子染黑，左旋p，设置x为根结束循环
     *
     * 对称情况（x是父节点的右孩子）类似处理
     *
     * @param x 替代被删除节点的节点或其子节点
     */
    void deleteFixup(RBTNode<T> *x) {
        while (x != _root && !isRed(x)) {
            if (x == x->parent->left) {
                RBTNode<T> *w = x->parent->right; // 兄弟节点
                if (isRed(w)) {
                    // Case 1: 兄弟是红色
                    setColor(w, Color::BLACK);
                    setColor(x->parent, Color::RED);
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (!isRed(w->left) && !isRed(w->right)) {
                    // Case 2: 兄弟的两个孩子都是黑色
                    setColor(w, Color::RED);
                    x = x->parent;
                } else {
                    if (!isRed(w->right)) {
                        // Case 3: 兄弟的右孩子是黑色，左孩子是红色
                        setColor(w->left, Color::BLACK);
                        setColor(w, Color::RED);
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // Case 4: 兄弟的右孩子是红色
                    setColor(w, x->parent->color);
                    setColor(x->parent, Color::BLACK);
                    setColor(w->right, Color::BLACK);
                    leftRotate(x->parent);
                    x = _root;
                }
            } else {
                // 对称情况：x是右孩子
                RBTNode<T> *w = x->parent->left; // 兄弟节点
                if (isRed(w)) {
                    // Case 1: 兄弟是红色
                    setColor(w, Color::BLACK);
                    setColor(x->parent, Color::RED);
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (!isRed(w->right) && !isRed(w->left)) {
                    // Case 2: 兄弟的两个孩子都是黑色
                    setColor(w, Color::RED);
                    x = x->parent;
                } else {
                    if (!isRed(w->left)) {
                        // Case 3: 兄弟的左孩子是黑色，右孩子是红色
                        setColor(w->right, Color::BLACK);
                        setColor(w, Color::RED);
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    // Case 4: 兄弟的左孩子是红色
                    setColor(w, x->parent->color);
                    setColor(x->parent, Color::BLACK);
                    setColor(w->left, Color::BLACK);
                    rightRotate(x->parent);
                    x = _root;
                }
            }
        }
        setColor(x, Color::BLACK);
    }

    // 判断节点颜色（处理哨兵节点）
    bool isRed(RBTNode<T> *node) const { return node != _nil && node->color == Color::RED; }

    // 设置节点颜色
    void setColor(RBTNode<T> *node, Color color) {
        if (node != _nil)
            node->color = color;
    }

  public:
    RBTree() {
        _nil = new RBTNode<T>();
        _nil->color = Color::BLACK;
        _nil->left = _nil->right = _nil->parent = _nil;
        _root = _nil;
    }

    /**
     * @brief 使用已分配的根节点构造红黑树
     *
     * 注意：调用者应确保传入的根节点是单个节点或已正确构建的子树。
     * 如果根节点有子节点，需要确保子节点的空指针已正确连接。
     * 建议使用默认构造函数并通过insert()方法插入节点。
     */
    explicit RBTree(RBTNode<T> *root) : _root(root) {
        _nil = new RBTNode<T>();
        _nil->color = Color::BLACK;
        _nil->left = _nil->right = _nil->parent = _nil;

        if (_root == nullptr) {
            _root = _nil;
        } else {
            _root->parent = _nil;
            // 确保根节点的空子节点指向哨兵
            if (_root->left == nullptr)
                _root->left = _nil;
            if (_root->right == nullptr)
                _root->right = _nil;
        }
    }

    ~RBTree() {
        destroy(_root);
        delete _nil;
    }

    RBTNode<T> *getRoot() const { return _root; }
    RBTNode<T> *getNil() const { return _nil; }
    void setRoot(RBTNode<T> *root) { _root = root; }

    RBTNode<T> *search(const T &v) const {
        RBTNode<T> *p = _root;
        while (p != _nil && p->val != v) {
            if (v < p->val)
                p = p->left;
            else
                p = p->right;
        }
        return p == _nil ? nullptr : p;
    }

    const T &findMin() const {
        if (_root == _nil) {
            throw std::out_of_range("findMin() while RBTree is empty.");
        }
        RBTNode<T> *p = _root;
        while (p->left != _nil)
            p = p->left;
        return p->val;
    }

    const T &findMax() const {
        if (_root == _nil) {
            throw std::out_of_range("findMax() while RBTree is empty.");
        }
        RBTNode<T> *p = _root;
        while (p->right != _nil)
            p = p->right;
        return p->val;
    }

    // 插入节点（外部分配节点）
    void insert(RBTNode<T> *node) {
        // 初始化新节点
        node->left = node->right = _nil;
        node->color = Color::RED; // 新插入的节点总是红色

        RBTNode<T> *y = _nil;
        RBTNode<T> *x = _root;

        // 找到插入位置
        while (x != _nil) {
            y = x;
            if (node->val < x->val)
                x = x->left;
            else if (node->val > x->val)
                x = x->right;
            else {
                // 值已存在，删除新节点并返回
                delete node;
                return;
            }
        }

        // 设置父节点
        node->parent = y;
        if (y == _nil) {
            _root = node; // 树为空
        } else if (node->val < y->val) {
            y->left = node;
        } else {
            y->right = node;
        }

        // 红黑树修复
        insertFixup(node);
    }

    // 插入值
    void insert(const T &v) {
        RBTNode<T> *node = new RBTNode<T>(v);
        insert(node);
    }

    // 移动插入
    void insert(T &&v) {
        RBTNode<T> *node = new RBTNode<T>(std::move(v));
        insert(node);
    }

    // 删除节点
    void remove(RBTNode<T> *z) {
        if (z == nullptr)
            return;

        RBTNode<T> *y = z;
        RBTNode<T> *x = _nil;
        Color yOriginalColor = y->color;

        if (z->left == _nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == _nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y; // 即使 x == _nil，也必须更新，deleteFixup 依赖此值
            } else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != _nil)
                    y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left != _nil)
                y->left->parent = y;
            setColor(y, z->color);
        }

        delete z;

        if (yOriginalColor == Color::BLACK) {
            deleteFixup(x);
        }
    }

    // 删除值
    void remove(const T &v) {
        RBTNode<T> *z = search(v);
        if (z != nullptr)
            remove(z);
    }
};

} // namespace ms

#endif // RBTREE_HPP