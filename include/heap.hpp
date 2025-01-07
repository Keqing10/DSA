#pragma once 

namespace ms {
	/**
	 * @brief 提供堆相关算法。
	 * 实现：堆排序，优先级队列。
	 * 堆为给定T类型数组，默认为大根堆。
	 * n个元素下标范围为[0, n-1]
	 * i的孩子节点：2*i，2*i+1
	 * i的父节点：i/2.
	 */
	template <typename T>
	class heap {
	public:
		T* ptr;
		int len;

		heap() : ptr(nullptr), len(0) {}
		heap(T* p, int n) : ptr(p), len(n) {}
		~heap() {}

		/**
		 * @brief 给定初始数组，建堆
		 * @param p 数组起始地址
		 * @param len 堆的长度，元素范围为[0, len-1]
		 */
		void create() {

		}

		/**
		 * @brief 弹出堆顶元素
		 */
		T& pop() {
			T ans = T[0];


			return ans;
		}

		/**
		 * @brief 在堆尾插入元素t，再调整堆
		 * @param len 原来堆的长度，插入后变为len+1
		 * @param t 被插入元素
		 */
		 void insert(T& t) {

		}
	};
}