#pragma once 

namespace ms {
	/**
	 * @brief �ṩ������㷨��
	 * ʵ�֣����������ȼ����С�
	 * ��Ϊ����T�������飬Ĭ��Ϊ����ѡ�
	 * n��Ԫ���±귶ΧΪ[0, n-1]
	 * i�ĺ��ӽڵ㣺2*i��2*i+1
	 * i�ĸ��ڵ㣺i/2.
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
		 * @brief ������ʼ���飬����
		 * @param p ������ʼ��ַ
		 * @param len �ѵĳ��ȣ�Ԫ�ط�ΧΪ[0, len-1]
		 */
		void create() {

		}

		/**
		 * @brief �����Ѷ�Ԫ��
		 */
		T& pop() {
			T ans = T[0];


			return ans;
		}

		/**
		 * @brief �ڶ�β����Ԫ��t���ٵ�����
		 * @param len ԭ���ѵĳ��ȣ�������Ϊlen+1
		 * @param t ������Ԫ��
		 */
		 void insert(T& t) {

		}
	};
}