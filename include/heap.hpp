#pragma once 

namespace ms {
	/**
	 * @brief �ṩ������㷨��
	 * ʵ�֣����������ȼ����С�
	 * ��Ϊ����T�������飬Ĭ��Ϊ����ѡ�����С���ѿ��Դ������࣬���ء�<��ʵ�֡�
	 * n��Ԫ���±귶ΧΪ[0, n-1]
	 * i�ĺ��ӽڵ㣺2*i��2*i+1
	 * i�ĸ��ڵ㣺i/2.
	 */
	template <typename T>
	class heap {
	private:
		/**
		 * @brief �����±�Ϊx��y������Ԫ�أ���֤��x, y < len
		 */
		void swap(int x, int y) {
			T temp = ptr[x];
			ptr[x] = ptr[y];
			ptr[y] = temp;
		}

		/**
		 * @brief ������ptr[n]Ϊ��������
		 */
		void adjust(int n) {
			if (2 * n >= len) return;
			if ((ptr[n] < ptr[2 * n]) || (2 * n + 1 < len && ptr[n] < ptr[2 * n + 1])) {
				int t;
				if (2 * n + 1 < len) t = (ptr[2 * n] < ptr[2 * n + 1] ? (2 * n + 1) : (2 * n));
				else t = 2 * n;
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
		 * @brief ������ʼ���飬����
		 * @param p ������ʼ��ַ
		 * @param len �ѵĳ��ȣ�Ԫ�ط�ΧΪ[0, len-1]
		 */
		void create() {
			for (int i = (len - 1) / 2; i > -1; --i) {
				adjust(i);
			}
		}

		/**
		 * @brief �����Ѷ�Ԫ�أ�ͬʱ���浽ԭ��ĩβ���ѵĴ�С-1.
		 */
		T& pop() {
			swap(0, --len);
			adjust(0);
			return ptr[len];
		}

		/**
		 * @brief �ڶ�β����Ԫ��t���ٵ����ѡ��ѵ������ɱ�������ά������֤�ܳɹ����롣
		 * @param len ԭ���ѵĳ��ȣ�������Ϊlen+1
		 * @param t ������Ԫ��
		 */
		void insert(T& t) {
			ptr[len++] = t;
			adjust(0);
		}
	};
}