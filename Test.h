#pragma once

namespace ms {
    class Test {
    public:
        Test() {}
        ~Test() {}
        static void run();

        static void test_vector();
        static void test_list();
        static void test_stack();
        static void test_queue();
        static void test_string();
        static void test_tree();
        static void test_sort();
    };
}

