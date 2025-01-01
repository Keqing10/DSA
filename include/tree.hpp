#pragma once

#include <iostream>

#include "queue.hpp"
#include "stack.hpp"

namespace ms {
	/**
     * @brief �����������
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
	 * @brief �Զ����������в����ĺ���ָ��
	 * @tparam T 
	 */
	template <typename T>
	using TOP = void (*)(TNode<T>*);

	/**
	 * @brief ����������ݹ���ʽ
	 * @param root ���ĸ����
	 * @param op ���ʽ��ĺ���ָ��
	 */
	template <typename T>
	void dfs11(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		op(root);
		dfs11(root->left, op);
		dfs11(root->right, op);
	}

	/**
	 * @brief ���������������ʽ
	 * @param root ���ĸ����
	 * @param op ���ʽ��ĺ���ָ��
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
	 * @brief ����������ݹ���ʽ
	 * @param root ���ĸ����
	 * @param op ���ʽ��ĺ���ָ��
	 */
	template <typename T>
	void dfs21(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		dfs11(root->left, op);
		op(root);
		dfs11(root->right, op);
	}

	/**
	 * @brief ���������������ʽ
	 * @param root ���ĸ����
	 * @param op ���ʽ��ĺ���ָ��
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
	 * @brief ����������ݹ���ʽ
	 * @param root ���ĸ����
	 * @param op ���ʽ��ĺ���ָ��
	 */
	template <typename T>
	void dfs3(TNode<T>* root, TOP<T> op) {
		if (!root) return;
		dfs11(root->left, op);
		dfs11(root->right, op);
		op(root);
	}
	
	/**
	 * @brief ��α�����������ʽ
	 * @param root ���ĸ���� 
	 * @param op ���ʽ��ĺ���ָ��
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