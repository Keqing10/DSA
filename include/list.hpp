#pragma once

#include <iostream>

namespace ms {
	/**
	 * @brief ����������
	 */
	template <typename T>
	class LNode {
	public:
		T val;
		LNode* next;

		LNode() : val(T()), next(nullptr) {}
		LNode(T&& t) : val(t), next(nullptr) {}
		LNode(LNode* p) : val(T()), next(p) {}
		LNode(T&& t, LNode* p) : val(t), next(p) {}
		~LNode() {}

		/**
		 * @brief ��ת������������ͷ���
		 * @param head ����ĵ�һ��Ԫ�ؽ��
		 * @return LNode<T>* ��ת�������ĵ�һ��Ԫ�ؽ��
		 */
		LNode* reverse() {
			LNode nh, *p = this, * q;
			while (p) {
				q = p->next;
				p->next = nh.next;
				nh.next = p;
				p = q;
			}
			return nh.next;
		}
	};

	/**
	 * @brief ˫��������
	 */
	template <typename T>
	class DLNode {
	public:
		T val;
		DLNode* prev, * next;

		DLNode() : prev(nullptr), next(nullptr) {}
		DLNode(T&& t) : val(t), prev(nullptr), next(nullptr) {}
		DLNode(T&& t, DLNode* p) : val(t), prev(nullptr), next(p) {}
		DLNode(DLNode* p1, DLNode* p2) : prev(p1), next(p2) {}
		DLNode(T&& t, DLNode* p1, DLNode* p2) : val(t), prev(p1), next(p2) {}
		~DLNode() {}
	};


	// @todo �Ƿ���Ҫ�޸�ȫ�ֺ���Ϊ��ĳ�Ա����
	/**
	 * @brief ��ת������������ͷ���
	 * @param head ����ĵ�һ��Ԫ�ؽ��
	 * @return DLNode<T>* ��ת�������ĵ�һ��Ԫ�ؽ��
	 */
	template <typename T>
	DLNode<T>* reverse(DLNode<T>* head) {
		DLNode<T> nh, * p = head, * q;
		while (p) {
			q = p->next;
			p->next = nh.next;
			if (nh.next) nh.next->prev = p;
			nh.next = p;
			p->prev = nullptr;
			p = q;
		}
		return nh.next;
	}
}