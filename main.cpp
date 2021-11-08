#include <iostream>
#include "tests.hpp"

using std::cout, std::endl;

int main() {

    test_construct();
    test_push_back();
    test_push_front();
    test_insert();
    test_pop_back();
    test_pop_front();
    test_erase_1();
    test_erase_range();
    test_front();
    test_back();
    test_at();
    test_resize();
    test_rule_of_three();

    demo_integration_testing();
    demo_iterator();
    demo_template();

    cout << "ALL TESTS PASSING" << endl;

    return 0;
} 
