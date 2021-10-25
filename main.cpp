#include <iostream>
#include <cassert>
#include "vector.hpp"

using std::cout, std::endl;

void test_construct() {
    {
        vector v;
        assert(v.capacity == 0);
        assert(v.size == 0);
        assert(v.A == nullptr);
    }

    {
        vector v{101, 53, new int[101]{42}};
        assert(v.capacity == 101);
        assert(v.size == 53);
        assert(v.A != nullptr);
        assert(v.A[0] == 42);

        delete[] v.A;
    }
}

void test_push_back() {

    // INSERT INTO NULL ARRAY
    {
        vector v;
        // preconditions
        //   A is null
        //   capacity is 0
        //   size is 0
        assert(v.A == nullptr);
        assert(v.capacity == 0);
        assert(v.size == 0);
        // expect push_back to succeed
        v.push_back(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.A != nullptr);
        assert(v.capacity == 1);
        assert(v.size== 1);
    }

    // INSERT INTO NULL ARRAY (LIE ABOUT CAPACITY)
    {
        vector v{1,0,nullptr};
        // preconditions
        //   A is null
        //   capacity is 1 (lie)
        //   size is 0
        assert(v.A == nullptr);
        assert(v.capacity == 1);
        assert(v.size == 0);
        // expect push_back to succeed
        v.push_back(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.A != nullptr);
        assert(v.capacity == 1);
        assert(v.size == 1);
    }

    // INSERT VALUE INTO ARRAY WITH CAPACITY 0
    {
        vector v{0,0,new int[1]{1}};
        // preconditions
        //   capacity is 0 (lie)
        //   size is 0
        //   A at index 0 is 1
        assert(v.capacity == 0);
        assert(v.size == 0);
        assert(v.A[0] == 1);
        // expect push_back to succeed
        v.push_back(-1);
        // postconditions
        //   capacity is 1
        //   size is 1
        //   A at index 0 is -1
        //   no memory leaks
        assert(v.capacity == 1);
        assert(v.size == 1);
        assert(v.A[0] == -1);

        delete[] v.A;
    }

    // INSERT VALUE INTO EMPTY ARRAY
    {
        vector v{10, 0, new int[10]{2}};
        // preconditions
        //   capacity > 0
        //   size is 0
        //   A at 0 is not 1
        assert(v.capacity > 0);
        assert(v.size == 0);
        assert(v.A[0] != 1);
        // expect push_back to succeed
        size_t old_capacity = v.capacity;
        v.push_back(1);
        // postconditions
        //   capacity did not change
        //   size is 1
        //   A at index 0 is 1
        assert(v.capacity == old_capacity);
        assert(v.size == 1);
        assert(v.A[0] == 1);

        delete[] v.A;
    }

    // FILL UP THE ARRAY
    {
        vector v{10,0,new int[10]{}};
        for (int i = 0; i < 10; i++) {
            // preconditions
            //   size is i
            //   capacity is 10
            //   A at i is 0
            assert(v.size == unsigned(i));
            assert(v.capacity == 10);
            assert(v.A[i] == 0);
            // expect push_back to succeed
            v.push_back(i);
            // postconditions
            //   size is i+1
            //   capacity is 10
            //   A at index i is i
            assert(v.size == unsigned(i+1));
            assert(v.capacity == 10);
            assert(v.A[i] == i);
        }

        for (int i = 0; i < 10; i++) {
            assert(v.A[i] == i);
        }

        delete[] v.A;
    }

    // INSERT INTO A FULL ARRAY
    {
        vector v{2,2,new int[2]{10,11}};
        // preconditions
        //   capacity > 0
        //   size equals capacity
        assert(v.size == v.capacity);
        assert(v.capacity > 0);
        // expect push_back to succeed
        size_t old_capacity = v.capacity;
        v.push_back(1);
        // postconditions
        //   size equals old_capacity + 1 (old_size + 1)
        //   capacity doubles
        assert(v.size == old_capacity + 1);
        assert(v.capacity == 2*old_capacity);

        assert(v.A[0] == 10);
        assert(v.A[1] == 11);
        assert(v.A[2] == 1);

        delete[] v.A;
    }
}

void test_push_front() {

    // INSERT INTO NULL ARRAY
    {
        vector v;
        // preconditions
        //   A is null
        //   capacity is 0
        //   size is 0
        assert(v.A == nullptr);
        assert(v.capacity == 0);
        assert(v.size == 0);
        // expect push_front to succeed
        v.push_front(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.A != nullptr);
        assert(v.capacity == 1);
        assert(v.size== 1);
    }

    // INSERT INTO NULL ARRAY (LIE ABOUT CAPACITY)
    {
        vector v{1,0,nullptr};
        // preconditions
        //   A is null
        //   capacity is 1 (lie)
        //   size is 0
        assert(v.A == nullptr);
        assert(v.capacity == 1);
        assert(v.size == 0);
        // expect push_front to succeed
        v.push_front(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.A != nullptr);
        assert(v.capacity == 1);
        assert(v.size == 1);
    }

    // INSERT VALUE INTO ARRAY WITH CAPACITY 0
    {
        vector v{0,0,new int[1]{1}};
        // preconditions
        //   capacity is 0 (lie)
        //   size is 0
        //   A at index 0 is 1
        assert(v.capacity == 0);
        assert(v.size == 0);
        assert(v.A[0] == 1);
        // expect push_front to succeed
        v.push_front(-1);
        // postconditions
        //   capacity is 1
        //   size is 1
        //   A at index 0 is -1
        //   no memory leaks
        assert(v.capacity == 1);
        assert(v.size == 1);
        assert(v.A[0] == -1);

        delete[] v.A;
    }

    // INSERT VALUE INTO EMPTY ARRAY
    {
        vector v{10, 0, new int[10]{2}};
        // preconditions
        //   capacity > 0
        //   size is 0
        //   A at 0 is not 1
        assert(v.capacity > 0);
        assert(v.size == 0);
        assert(v.A[0] != 1);
        // expect push_front to succeed
        size_t old_capacity = v.capacity;
        v.push_front(1);
        // postconditions
        //   capacity did not change
        //   size is 1
        //   A at index 0 is 1
        assert(v.capacity == old_capacity);
        assert(v.size == 1);
        assert(v.A[0] == 1);

        delete[] v.A;
    }

    // FILL UP THE ARRAY
    {
        vector v{10,0,new int[10]{}};
        for (int i = 0; i < 10; i++) {
            // preconditions
            //   size is i
            //   capacity is 10
            //   A at i is 0
            assert(v.size == unsigned(i));
            assert(v.capacity == 10);
            if (i == 0) {
                assert(v.A[0] == 0);
            } else {
                assert(v.A[0] == i-1);
            }
            // expect push_front to succeed
            v.push_front(i);
            // postconditions
            //   size is i+1
            //   capacity is 10
            //   A at index 0 is i
            assert(v.size == unsigned(i+1));
            assert(v.capacity == 10);
            assert(v.A[0] == i);
        }

        for (int i = 0; i < 10; i++) {
            assert(v.A[i] == 9-i);
        }

        delete[] v.A;
    }

    // INSERT INTO A FULL ARRAY
    {
        vector v{2,2,new int[2]{10,11}};
        // preconditions
        //   capacity > 0
        //   size equals capacity
        assert(v.size == v.capacity);
        assert(v.capacity > 0);
        // expect push_front to succeed
        size_t old_capacity = v.capacity;
        v.push_front(1);
        // postconditions
        //   size equals old_capacity + 1 (old_size + 1)
        //   capacity doubles
        //   A at 0 is 1
        assert(v.size == old_capacity + 1);
        assert(v.capacity == 2*old_capacity);

        assert(v.A[0] == 1);
        assert(v.A[1] == 10);
        assert(v.A[2] == 11);

        delete[] v.A;
    }
}

void test_insert() {
    vector v;

    assert(v.capacity == 0);
    assert(v.size == 0);

    // insert at not 0 into empty (possibly null)
    bool threw_expected_exception = false;
    try {
        v.insert(1, 1);
    } catch(const std::out_of_range& err) {
        threw_expected_exception = true;
    }
    assert(threw_expected_exception);
    assert(v.capacity == 0);
    assert(v.size == 0);

    // insert at 0 into empty
    bool threw_exception = false;
    try {
        v.insert(0, 1);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity == 1);
    assert(v.size == 1);
    assert(v.A[0] == 1);

    // insert at front
    threw_exception = false;
    try {
        v.insert(0, 2);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity == 2);
    assert(v.size == 2);
    assert(v.A[0] == 2);
    assert(v.A[1] == 1);

    // insert at back
    threw_exception = false;
    try {
        v.insert(2, 3);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity == 4);
    assert(v.size == 3);
    assert(v.A[0] == 2);
    assert(v.A[1] == 1);
    assert(v.A[2] == 3);

    // insert at middle
    threw_exception = false;
    try {
        v.insert(1, 4);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity == 4);
    assert(v.size == 4);
    assert(v.A[0] == 2);
    assert(v.A[1] == 4);
    assert(v.A[2] == 1);
    assert(v.A[3] == 3);

    // insert out of bounds in non empty array
    threw_expected_exception = false;
    try {
        v.insert(5, 5);
    } catch(const std::out_of_range& err) {
        threw_expected_exception = true;
    }
    assert(threw_expected_exception);
    assert(v.capacity == 4);
    assert(v.size == 4);
    assert(v.A[0] == 2);
    assert(v.A[1] == 4);
    assert(v.A[2] == 1);
    assert(v.A[3] == 3);

}

void test_pop_back() {
    // REMOVE FROM NULL ARRAY
    {
        vector v{1,1,nullptr};
        // preconditions
        //   A is null
        //   capacity is > 0 (lie)
        //   size is > 0 (lie)
        assert(v.A == nullptr);
        assert(v.capacity > 0);
        assert(v.size > 0);
        size_t old_size = v.size;
        size_t old_capacity = v.capacity;
        // expect pop_back to throw invalid_argument exception
        bool threw_expected_exception = false;
        try {
            v.pop_back();
        } catch (const std::invalid_argument& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"pop_back from null array throws wrong type of exception");
        }
        assert(threw_expected_exception);
        // postconditions
        //   A is null
        //   capacity did not change
        //   size did not change
        assert(v.A == nullptr);
        assert(v.capacity == old_capacity);
        assert(v.size== old_size);
    }

    // REMOVE THE LAST ELEMENT
    {
        vector v{10, 10, new int[10]{1,2,3,4,5,6,7,8,9,10}};
        // preconditions
        //   capacity is > 1
        //   size is <= capacity and > 1
        //   A at 1 before end is 9
        //   A at end is 10
        assert(v.capacity > 1);
        assert(v.size <= v.capacity);
        assert(v.size > 1);
        assert(v.A[v.size-2] == 9);
        assert(v.A[v.size-1] == 10);
        // expect pop_back to return 10
        size_t old_size = v.size;
        size_t old_capacity = v.capacity;
        assert(v.pop_back() == 10);
        // postconditions
        //   capacity did not change
        //   size is 1 less than previous
        //   A at end is 9
        assert(v.capacity == old_capacity);
        assert(v.size == old_size - 1);
        assert(v.A[v.size-1] == 9);

        delete[] v.A;
    }

    // REMOVE ALL ELEMENTS FROM BACK
    {
        vector v{9,9,new int[9]{1,2,3,4,5,6,7,8,9}};
        size_t old_capacity = v.capacity;
        for (int i = 9; i > 0; i--) {
            // preconditions
            //   capacity is > 0
            //   size is i
            //   A at end is i
            assert(v.size == unsigned(i));
            assert(v.A[v.size-1] == i);
            // expect pop_back to return i
            assert(v.pop_back() == i);
            // postconditions
            //   capacity did not change
            //   size is i-1
            //   A at index i-2 (end) is i-1
            assert(v.capacity == old_capacity);
            assert(v.size == unsigned(i-1));
            if (i > 1) {
                assert(v.A[v.size-1] == i-1);
            }
        }

        delete[] v.A;
    }

    // ATTEMPT TO REMOVE FROM NULL
    {
        vector v;
        // preconditions
        //   size is 0
        //   capacity is 0
        //   A is null
        assert(v.size== 0);
        assert(v.capacity == 0);
        assert(v.A == nullptr);
        // expect pop_back to throw invalid_argument exception
        bool threw_expected_exception = false;
        try {
            v.pop_back();
        } catch (const std::invalid_argument& err) {
            threw_expected_exception = true;
        } catch(...) {
            cout << "pop_back threw the wrong type of exception" << endl;
        }
        assert(threw_expected_exception);
        // postconditions
        //   size is 0
        //   capacity is 0
        //   A is null
        assert(v.size== 0);
        assert(v.capacity == 0);
        assert(v.A == nullptr);
    }

    // ATTEMPT TO REMOVE FROM EMPTY
    {
        vector v{5,0,new int[5]{1}};
        // preconditions
        //   size is 0
        //   capacity is > 0
        //   A is not null
        assert(v.size == 0);
        assert(v.capacity > 0);
        assert(v.A != nullptr);
        // expect pop_back to throw invalid_argument exception
        size_t old_capacity = v.capacity;
        int* old_A = v.A;
        bool threw_expected_exception = false;
        try {
            v.pop_back();
        } catch (const std::out_of_range& err) {
            threw_expected_exception = true;
        } catch(...) {
            cout << "pop_back threw the wrong type of exception" << endl;
        }
        assert(threw_expected_exception);
        // postconditions
        //   size is 0
        //   capacity is unchanged
        //   A is unchanged
        assert(v.size== 0);
        assert(v.capacity == old_capacity);
        assert(v.A == old_A);
    }

}

void test_front() {
    // ATTEMPT TO GET FRONT OF NULL ARRAY
    {
        vector v{10, 1, nullptr};
        // pre
        //   A is nullptr
        //   capacity is > 0 (lie)
        //   size is > 0 (lie)
        // expect front of null to throw invalid_argument exception
        assert(v.A == nullptr);
        assert(v.size > 0);
        assert(v.capacity > 0);
        bool throws_expected_exception = false;
        size_t old_size = v.size;
        size_t old_capacity = v.capacity;
        try {
            v.front();
        } catch (const std::invalid_argument& err) {
            throws_expected_exception = true;
        } catch (...) {
            assert(!"front of null array threw wrong kind of exception");
        }
        // post
        //   invalid_argument exception was caught
        //   size does not change
        //   capacity does not change
        //   A is nullptr
        assert(throws_expected_exception);
        assert(v.size == old_size);
        assert(v.capacity == old_capacity);
        assert(v.A == nullptr);
    }

    // ATTEMPT TO GET FRONT OF EMPTY ARRAY
    {
        vector v{10, 0, new int[10]};
        // pre
        //   A is not null
        //   size is 0
        assert(v.A != nullptr);
        assert(v.size == 0);
        // expect front of empty to throw out_of_range exception
        bool throws_expected_exception = false;
        size_t old_capacity = v.capacity;
        int* old_A = v.A; 
        try {
            v.front();
        } catch (const std::out_of_range& err) {
            throws_expected_exception = true;
        } catch (...) {
            assert(!"front of empty array threw wrong kind of exception");
        }
        // post
        //   out_of_range exception was caught
        //   size = 0
        //   capacity is unchanged
        //   A is changed 
        assert(throws_expected_exception);
        assert(v.size == 0);
        assert(v.capacity == old_capacity);
        assert(v.A == old_A);

        delete[] v.A;
    }

    // GET FRONT OF NON-EMPTY ARRAY
    {
        vector v{4, 1, new int[4]{10,11}};
        // pre
        //   A[0] is 10
        //   A[1] is 11
        //   size is 1
        assert(v.A[0] == 10);
        assert(v.A[1] == 11);
        assert(v.size == 1);
        // expect front of {10} to be 10
        assert(v.front() == 10);
        // expect front of {10, 11} to be 10
        v.size = 2;
        assert(v.front() == 10);
        // post
        //   A[0] is 10
        //   A[1] is 11
        //   size is 2
        assert(v.A[0] == 10);
        assert(v.A[1] == 11);
        assert(v.size == 2);

        delete[] v.A;
    }

    // FRONT RETURNS LVALUE REFERENCE
    {
        vector v{3,2,new int[3]{}};
        // pre
        //   A at 0 is not 12
        assert(v.A[0] != 12);
        assert(v.size == 2);
        // expect assignment to return new value
        assert((v.front() = 12) == 12);
        // post
        //   v at 0 is 12, others unchanged
        //   size is unchanged
        assert(v.A[0] == 12);
        assert(v.A[1] == 0);
        assert(v.A[2] == 0);
        assert(v.size == 2);

        delete[] v.A;
    }

    // FRONT OF CONST ARRAY
    {
        const vector constV{3,3,new int[3]{102}};
        assert(constV.front() == 102);

        delete[] constV.A;
    }

    // FRONT OF CONST NULL
    {
        const vector constNull;
        // pre
        //   object is const
        //   A is nullptr
        assert(constNull.A == nullptr);
        bool caught_expected_exception = false;
        try {
            constNull.front();
        } catch (const std::invalid_argument& err) {
            caught_expected_exception = true;
        } catch (...) {}
        // post
        //   caught out_of_range exception
        //   A is nullptr
        assert(caught_expected_exception);
        assert(constNull.A == nullptr);
    }


    // FRONT OF CONST EMPTY
    {
        const vector constEmpty{1,0,new int[1]{}};
        bool caught_expected_exception = false;
        try {
            constEmpty.front();
        } catch (const std::out_of_range& err) {
            caught_expected_exception = true;
        } catch (...) {}
        assert(caught_expected_exception);
        assert(constEmpty.A != nullptr);

        delete[] constEmpty.A;
    }
}

void test_back() {
    // ATTEMPT TO GET BACK OF NULL ARRAY
    {
        vector v{10, 1, nullptr};
        // pre
        //   A is nullptr
        //   capacity is > 0 (lie)
        //   size is > 0 (lie)
        // expect back of null to throw invalid_argument exception
        assert(v.A == nullptr);
        assert(v.size > 0);
        assert(v.capacity > 0);
        bool throws_expected_exception = false;
        size_t old_size = v.size;
        size_t old_capacity = v.capacity;
        try {
            v.back();
        } catch (const std::invalid_argument& err) {
            throws_expected_exception = true;
        } catch (...) {
            assert(!"back of null array threw wrong kind of exception");
        }
        // post
        //   invalid_argument exception was caught
        //   size does not change
        //   capacity does not change
        //   A is nullptr
        assert(throws_expected_exception);
        assert(v.size == old_size);
        assert(v.capacity == old_capacity);
        assert(v.A == nullptr);
    }

    // ATTEMPT TO GET BACK OF EMPTY ARRAY
    {
        vector v{10, 0, new int[10]};
        // pre
        //   A is not null
        //   size is 0
        assert(v.A != nullptr);
        assert(v.size == 0);
        // expect back of empty to throw out_of_range exception
        bool throws_expected_exception = false;
        size_t old_capacity = v.capacity;
        int* old_A = v.A; 
        try {
            v.back();
        } catch (const std::out_of_range& err) {
            throws_expected_exception = true;
        } catch (...) {
            assert(!"back of empty array threw wrong kind of exception");
        }
        // post
        //   out_of_range exception was caught
        //   size = 0
        //   capacity is unchanged
        //   A is changed 
        assert(throws_expected_exception);
        assert(v.size == 0);
        assert(v.capacity == old_capacity);
        assert(v.A == old_A);

        delete[] v.A;
    }

    // GET BACK OF NON-EMPTY ARRAY
    {
        vector v{4, 1, new int[4]{10,11}};
        // pre
        //   A[0] is 10
        //   A[1] is 11
        //   size is 1
        assert(v.A[0] == 10);
        assert(v.A[1] == 11);
        assert(v.size == 1);
        // expect back of {10} to be 10
        assert(v.front() == 10);
        // expect back of {10, 11} to be 10
        v.size = 2;
        assert(v.back() == 11);
        // post
        //   A[0] is 10
        //   A[1] is 11
        //   size is 2
        assert(v.A[0] == 10);
        assert(v.A[1] == 11);
        assert(v.size == 2);

        delete[] v.A;
    }

    // BACK RETURNS LVALUE REFERENCE
    {
        vector v{3,2,new int[3]{}};
        // pre
        //   A at 1 is not 12
        assert(v.A[1] != 12);
        assert(v.size == 2);
        // expect assignment to return new value
        assert((v.back() = 12) == 12);
        // post
        //   A at 1 is 12, others unchanged
        //   size is unchanged
        assert(v.A[0] == 0);
        assert(v.A[1] == 12);
        assert(v.A[2] == 0);
        assert(v.size == 2);

        delete[] v.A;
    }

    // BACK OF CONST ARRAY
    {
        const vector constV{3,3,new int[3]{0,0,221}};
        assert(constV.back() == 221);

        delete[] constV.A;
    }

    // BACK OF CONST NULL
    {
        const vector constNull;
        // pre
        //   object is const
        //   A is nullptr
        assert(constNull.A == nullptr);
        bool caught_expected_exception = false;
        try {
            constNull.back();
        } catch (const std::invalid_argument& err) {
            caught_expected_exception = true;
        } catch (...) {}
        // post
        //   caught out_of_range exception
        //   A is nullptr
        assert(caught_expected_exception);
        assert(constNull.A == nullptr);
    }


    // BACK OF CONST EMPTY
    {
        const vector constEmpty{1,0,new int[1]{}};
        bool caught_expected_exception = false;
        try {
            constEmpty.back();
        } catch (const std::out_of_range& err) {
            caught_expected_exception = true;
        } catch (...) {}
        assert(caught_expected_exception);
        assert(constEmpty.A != nullptr);

        delete[] constEmpty.A;
    }
}

void test_at() {
    // ATTEMPT TO ACCESS NULL ARRAY
    {
        vector v{1, 1, nullptr};
        // pre
        //   A is nullptr
        //   size is > 0 (lie)
        //   capacity is > 0 (lie)
        assert(v.A == nullptr);
        assert(v.size > 0);
        assert(v.capacity > 0);
        // expect at of null to throw invalid_argument exception
        bool threw_expected_exception = false;
        try {
            v.at(0);
        } catch (const std::invalid_argument& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"at of null array threw wrong kind of exception");
        }
        // post
        //   invalid_argument exception was caught
        //   size = 1 (lie)
        assert(threw_expected_exception);
        assert(v.size == 1);
    }

    // ATTEMPT TO ACCESS EMPTY ARRAY
    {
        vector v{5,0,new int[5]};
        // pre
        //   A is not null
        //   size = 0
        assert(v.A != nullptr);
        assert(v.size == 0);
        // expect at of empty to throw out_of_range exception
        bool threw_expected_exception = false;
        try {
            v.at(0);
        } catch (const std::out_of_range& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"at of empty array threw wrong kind of exception");
        }
        // post
        //   out_of_range exception was caught
        //   size = 0
        assert(threw_expected_exception);
        assert(v.size== 0);

        delete[] v.A;
    }

    // ACCESS MIDDLE OF ARRAY
    {
        vector v{10, 10, new int[10]{9,-1,-2,0,-4,3,7,5,6,8}};
        // pre
        //   A[8] is 6
        //   A[7] is 5
        //   A[3] is 0
        //   size is 10
        assert(v.A[8] == 6);
        assert(v.A[7] == 5);
        assert(v.A[3] == 0);
        assert(v.size == 10);
        // expect A at {8,7,3} to be {6,5,0}
        assert(v.at(8) == 6);
        assert(v.at(7) == 5);
        assert(v.at(3) == 0);
        // post
        //   A[8] is 6
        //   A[7] is 5
        //   A[3] is 0
        //   size is 10
        assert(v.A[8] == 6);
        assert(v.A[7] == 5);
        assert(v.A[3] == 0);
        assert(v.size == 10);
        
        delete[] v.A;
    }

    // ATTEMPT TO ACCESS ARRAY OUT OF BOUNDS
    {
        vector v{10, 5, new int[10]{1,2,3,4,5}};
        // pre
        //   size is 5
        assert(v.size == 5);
        // expect A at 5 to throw out_of_range exception
        bool threw_expected_exception = false;
        try {
            v.at(5);
        } catch (const std::out_of_range& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"at threw the wrong type of exception");
        }
        assert(threw_expected_exception);

        threw_expected_exception = false;
        try {
            v.at(5) = 0;
        } catch (const std::out_of_range& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"at threw the wrong type of exception");
        }
        assert(threw_expected_exception);

        delete[] v.A;
    }

    // ATTEMPT TO ACCESS CONST ARRAY OUT OF BOUNDS
    {
        const vector v{10, 5, new int[10]{1,2,3,4,5}};
        // pre
        //   size is 5
        assert(v.size == 5);
        // expect A at 5 to throw out_of_range exception
        bool threw_expected_exception = false;
        try {
            v.at(5);
        } catch (const std::out_of_range& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"at threw the wrong type of exception");
        }
        assert(threw_expected_exception);

        delete[] v.A;
    }

    // AT RETURNS LVALUE REFERENCE
    {
        vector v{10, 5, new int[10]{}};
        // pre
        //   size > 3
        //   A at 2 is not 7
        assert(v.size > 3);
        assert(v.A[2] != 7);
        size_t old_size = v.size;
        // expect at(A,size,2) = 7 to set A at 2 to 7
        v.at(2) = 7;
        // post
        //   size did not change
        //   A at 2 is 7
        assert(v.size == old_size);
        assert(v.A[2] == 7);

        delete[] v.A;
    }

    // ACCESS CONST ARRAY
    {
        const vector constV{3, 2, new int[3]{0,121}};
        assert(constV.at(1) == 121);

        delete[] constV.A;
    }

    // ATTEMPT TO ACCESS CONST NULL ARRAY
    {
        const vector constV;
        bool threw_expected_exception = false;
        try {
            constV.at(0);
        } catch (const std::invalid_argument& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"at of null const array threw wrong kind of exception");
        }
        assert(threw_expected_exception);
    }
}

void test_resize() {
    vector v{10, 5, new int[10]{12,13,17,15,16}};
    // pre
    //   A is [12, 13, 17, 15, 16]
    //   size is 5
    //   capacity is 10
    assert(v.A[0] == 12);
    assert(v.A[1] == 13);
    assert(v.A[2] == 17);
    assert(v.A[3] == 15);
    assert(v.A[4] == 16);
    assert(v.size == 5);
    assert(v.capacity == 10);
    // expect resize to double the capacity
    v.resize();
    // post
    //   A is [12, 13, 17, 15, 16]
    //   size is 5
    //   capacity is 20
    assert(v.A[0] == 12);
    assert(v.A[1] == 13);
    assert(v.A[2] == 17);
    assert(v.A[3] == 15);
    assert(v.A[4] == 16);
    // zeros in new part of array
    assert(v.A[10] == 0);
    assert(v.A[19] == 0);
    assert(v.size == 5);
    assert(v.capacity == 20);

    // no easy way to tell if the allocation was _actually_ correct

    delete[] v.A;
}


int main() {

    test_construct();
    test_push_back();
    test_push_front();
    test_insert();
    test_pop_back();
    test_front();
    test_back();
    test_at();
    test_resize();

    cout << "ALL TESTS PASSING" << endl;

    return 0;
} 