#pragma once
/**
 * @brief ���������㷨��ʵ��
 * ���룺T������ʼ��ַ�����鳤��
 * ��������T��Ҫ���ء�<�����š���==�����š���>������.
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
	 * @brief ð������
	 */
	template <typename T>
	void bubbleSort(T* p, int len) {
		bool flag = true;  // �Ƿ��Ѿ�����
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
	 * @brief ��������
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
	 * @brief ֱ�Ӳ�������
	 */
	template <typename T>
	void insertSort(T* p, int len) {
		for (int i = 1; i < len; ++i) {
			for (int j = i; j > 0 && p[j] < p[j - 1]; --j)
				swap(p[j - 1], p[j]);
		}
	}

	/**
	 * @brief ϣ������
	 */
	template <typename T>
	void shellSort(T* p, int len) {
		int gap = len / 2;
		while (gap >= 1) {
			for (int i = 0; i < gap; ++i) {  // ��gap�飬i��ÿ���һ��Ԫ�ص�ƫ�ƣ�����Ԫ�ؼ��gap
				for (int j = i + gap; j < len; j += gap) {  // i+gap��ÿ��ڶ���Ԫ�أ��Ӹ�Ԫ�ؿ�ʼ����
					for (int k = j; k > i && p[k] < p[k - gap]; k -= gap) {
						swap(p[k], p[k - gap]);
					}
				}
			}
			if (gap == 1) break;  // gapΪ1ʱ�Ѿ������һ�Σ���ʱ��������˳�
			gap /= 2;
		}
	}

	/**
	 * @brief ��ѡ������
	 */
	template <typename T>
	void checkSort(T* p, int len) {
		for (int i = 0; i < len - 1; ++i) {  // ��ѭ������[i,len-1]�е���Сֵ
			int ind = i;
			for (int j = i + 1; j < len; ++j) {
				if (p[j] < p[ind]) ind = j;
			}
			swap(p[i], p[ind]);
		}
	}

	/**
	 * @brief ������
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
	 * @brief �鲢����
	 */
	template <typename T>
	void mergeSort(T* p, int len) {
		int* pa = new T[len];
		_merge(p, pa, 0, len - 1);
		delete[] pa;
	}
	/**
	 * @brief �鲢����������
	 * @param p ����������
	 * @param pa �����ռ�
	 * @param le ri ����������[le, ri]
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