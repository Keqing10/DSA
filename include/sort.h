#pragma once
/**
 * @brief 各种排序算法的实现
 * 输入：T数组起始地址，数组长度
 * 对于类型T需要重载“<”符号、“==”符号、“>”符号.
 */

#include "heap.hpp"

namespace ms {
	template <typename T>
	void swap(T& a, T& b) {
		T t = a;
		a = b;
		b = t;
	}

	/**
	 * @brief 冒泡排序
	 */
	template <typename T>
	void bubbleSort(T* p, int len) {
		bool flag = true;  // 是否已经有序
		for (int i = len - 1; !flag && i > 0; --i) {
			flag = true;
			for (int j = 0; j < i; ++j) {
				if (p[j] > p[j + 1]) {
					swap(p[j], p[j + 1]);
					flag = false;
				}
			}
		}
	}

	/**
	 * @brief 快速排序
	 */
	template <typename T>
	void quickSort(T* p, int len) {
		if (len <= 1) return;
		int le = 0, ri = len - 1;
		T t = p[0];
		while (le < ri) {
			while (le < ri && t < p[ri]) --ri;
			p[le] = p[ri];  // p[ri] = t
			while (le < ri && p[le] < t) ++le;
			p[ri] = p[le];  // p[le] = t
		}
		p[le] = t;
		quickSort(p, le);
		quickSort(p + le + 1, len - le - 1);
	}

	/**
	 * @brief 直接插入排序
	 */
	template <typename T>
	void insertSort(T* p, int len) {
		for (int i = 1; i < len; ++i) {
			for (int j = i; j > 0 && p[j] < p[j - 1]; --j)
				swap(p[j - 1], p[j]);
		}
	}

	/**
	 * @brief 希尔排序
	 */
	template <typename T>
	void shellSort(T* p, int len) {
		int gap = len / 2;
		while (gap >= 1) {
			for (int i = 0; i < gap; ++i) {  // 有gap组，i是每组第一个元素的偏移，组内元素间隔gap
				for (int j = i + gap; j < len; j += gap) {  // i+gap是每组第二个元素，从该元素开始插入
					for (int k = j; k > i && p[k] < p[k - gap]; k -= gap) {
						swap(p[k], p[k - gap]);
					}
				}
			}
			if (gap == 1) break;  // gap为1时已经排序过一次，此时有序可以退出
			gap /= 2;
		}
	}

	/**
	 * @brief 简单选择排序
	 */
	template <typename T>
	void checkSort(T* p, int len) {
		for (int i = 0; i < len - 1; ++i) {  // 外循环，找[i,len-1]中的最小值
			int ind = i;
			for (int j = i + 1; j < len; ++j) {
				if (p[j] < p[ind]) ind = j;
			}
			swap(p[i], p[ind]);
		}
	}

	/**
	 * @brief 堆排序
	 */
	template <typename T>
	void heapSort(T* p, int len) {
		heap<T> hp(p, len);
		hp.create();
		for (int i = len - 1; i > -1; --i) {
			hp.pop();
		}
	}

	/**
	 * @brief 归并排序
	 */
	template <typename T>
	void mergeSort(T* p, int len) {
		int* pa = new T[len];
		_merge(p, pa, 0, len - 1);
		delete[] pa;
	}
	/**
	 * @brief 归并排序辅助函数
	 * @param p 待排序数组
	 * @param pa 辅助空间
	 * @param le ri 待排序区间[le, ri]
	 */
	template <typename T>
	void _merge(T* p, T* pa, int le, int ri) {
		if (ri - le < 2) {
			if (p[ri] < p[le]) swap(p[le], p[ri]);
			return;
		}
		int mi = (le + ri) / 2;
		_merge(p, pa, le, mi);
		_merge(p, pa, mi + 1, ri);
		for (int i = le; i < mi + 1; ++i) {
			pa[i] = p[i];
		}
		int i = le, j = mi, k = le;
		while (i < mi + 1 && j < ri + 1) {
			if (pa[i] <= p[j]) p[k++] = pa[i++];
			else p[k++] = p[j++];
		}
		while (i < mi + 1) {
			p[k++] = pa[i++];
		}
	}
}