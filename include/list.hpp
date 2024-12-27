#pragma once

#include <iostream>

namespace ms {
	/**
	 * @brief Ω·µ„¿‡
	 */
	template <typename T>
	class LNode {
	public:
		T val;
		LNode* prev, * next;

		LNode() : prev(nullptr), next(nullptr) {}
		LNode(T t) : val(t), prev(nullptr), next(nullptr) {}
		LNode(T t, LNode* p) : val(t), prev(nullptr), next(p) {}
		LNode(T t, LNode* p1, LNode* p2) : val(t), prev(p1), next(p2) {}
		~LNode() {}

	};
}