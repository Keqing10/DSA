#pragma once

namespace ms {
	class Test {
	public:
		Test() {}
		~Test() {}
	};

	class TestVec : Test {
	public:
		TestVec() {}
		void run();
	};
}