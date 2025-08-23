#pragma once 

namespace ms {
	/**
	 * @brief 提供堆相关算法。
	 * 实现：堆排序，优先级队列。
	 * 堆为给定T类型数组，默认为大根堆。建立小根堆可以创建新类，重载“<”实现。
	 * n个元素下标范围为[0, n-1]
	 * i的孩子节点：2*i+1，2*i+2
	 * i的父节点：(i-1)/2.
	 */
	template <typename T>
	class heap {
	private:
		/**
		 * @brief 交换下标为x和y的两个元素，保证：x, y < len
		 */
		void swap(int x, int y) {
			T temp = ptr[x];
			ptr[x] = ptr[y];
			ptr[y] = temp;
		}

		/**
		 * @brief 调整以ptr[n]为根的子树
		 */
		void adjust(int n) {
			if (2 * n + 1 >= len) return;
			if ((ptr[n] < ptr[2 * n + 1]) || (2 * n + 2 < len && ptr[n] < ptr[2 * n + 2])) {
				int t;
				if (2 * n + 2 < len) t = (ptr[2 * n + 1] < ptr[2 * n + 2] ? (2 * n + 2) : (2 * n + 1));
				else t = 2 * n + 1;
				swap(n, t);
				adjust(t);
			}
		}

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
			for (int i = (len - 2) / 2; i > -1; --i) {
				adjust(i);
			}
		}

		/**
		 * @brief 弹出堆顶元素，同时保存到原堆末尾，堆的大小-1.
		 */
		T& pop() {
			swap(0, --len);
			adjust(0);
			return ptr[len];
		}

		/**
		 * @brief 在堆尾插入元素t，再调整堆。堆的容量由被调用者维护，保证能成功插入。
		 * @param len 原来堆的长度，插入后变为len+1
		 * @param t 被插入元素
		 */
		void insert(T& t) {
			ptr[len++] = t;
			for (int i = (len - 2) / 2; i > -1; i = (i - 1) / 2) {
				adjust(i);
			}
		}
	};
}
