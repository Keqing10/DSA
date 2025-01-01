#pragma once

#include <iostream>

#include "queue.hpp"
#include "stack.hpp"

namespace ms {
	/**
     * @brief 二叉树结点类
     */
	template <typename T>
	class TNode {
	public:
		T val;
		TNode* left, * right;
		
		TNode() : left(nullptr), right(nullptr) {}
		TNode(T&& t) : val(t), left(nullptr), right(nullptr) {}
		TNode(TNode* pl, TNode* pr) : left(pl), right(pr) {}
		TNode(T&& t, TNode* pl, TNode* pr) : val(t), left(pl), right(pr) {}
		~TNode() {}
	};

	/**
	 * @brief 对二叉树结点进行操作的函数指针
	 * @tparam T 
	 */
	template <typename T>
	using TOP = void (*)(TNode<T>*);

	/**
	 * @brief 先序遍历，递归形式
	 * @param root 树的根结点
	 * @param op 访问结点的函数指针
	 */
	template <typename T>
	void dfs11(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		op(root);
		dfs11(root->left, op);
		dfs11(root->right, op);
	}

	/**
	 * @brief 先序遍历，迭代形式
	 * @param root 树的根结点
	 * @param op 访问结点的函数指针
	 */
	template <typename T>
	void dfs12(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		stack<TNode<T>*> stk;
		stk.push(root);
		while (!stk.empty()) {
			TNode<T>* p = stk.pop();
			op(p);
			if (p->right) stk.push(p->right);
			if (p->left) stk.push(p->left);
		}
	}

	/**
	 * @brief 中序遍历，递归形式
	 * @param root 树的根结点
	 * @param op 访问结点的函数指针
	 */
	template <typename T>
	void dfs21(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		dfs11(root->left, op);
		op(root);
		dfs11(root->right, op);
	}

	/**
	 * @brief 中序遍历，迭代形式
	 * @param root 树的根结点
	 * @param op 访问结点的函数指针
	 */
	template <typename T>
	void dfs22(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		stack<TNode<T>*> stk;
		while (!stk.empty() || root) {
			while (root) {
				stk.push(root);
				root = root->left;
			}
			root = stk.pop();
			op(root);
			root = root->right;
		}
	}

	/**
	 * @brief 后序遍历，递归形式
	 * @param root 树的根结点
	 * @param op 访问结点的函数指针
	 */
	template <typename T>
	void dfs3(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		dfs11(root->left, op);
		dfs11(root->right, op);
		op(root);
	}
	
	/**
	 * @brief 层次遍历，迭代形式
	 * @param root 树的根结点 
	 * @param op 访问结点的函数指针
	 */
	template <typename T>
	void bfs(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		queue<TNode<T>*> que;
		que.push(root);
		while (!que.empty()) {
			root = que.pop();
			op(root);
			if (root->left) que.push(root->left);
			if (root->right) que.push(root->right);
		}
	}
}