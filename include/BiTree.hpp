#pragma once

#include <iostream>

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
		TNode(T& t) : val(t), left(nullptr), right(nullptr) {}
		TNode(TNode* pl, TNode* pr) : left(pl), right(pr) {}
		TNode(T& t, TNode* pl, TNode* pr) : val(t), left(pl), right(pr) {}
		~TNode() {}
	};


}