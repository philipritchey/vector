#include <iostream>
#include <cassert>
#include "vector.hpp"

using std::cout, std::endl;

void test_construct() {
    {
        vector v;
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        assert(v.data() == nullptr);
    }

    {
        //vector v{101, 53, new int[101]{42}};
        vector v(101);
        assert(v.capacity() == 101);
        assert(v.size() == 101);
        assert(v.data() != nullptr);
        for (size_t index = 0; index < 101; index++) {
            assert(v.data()[index] == 0); 
        }
    }

    {
        vector v({1,2,3,4,5});
        assert(v.capacity() == 5);
        assert(v.size() == 5);
        assert(v.data() != nullptr);
        for (size_t index = 0; index < 5; index++) {
            assert(v.data()[index] == int(index+1)); 
        }
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
        assert(v.data() == nullptr);
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        // expect push_back to succeed
        v.push_back(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.data() != nullptr);
        assert(v.capacity() == 1);
        assert(v.size()== 1);

        //delete[] v.data();
    }

    /* OBSOLETE
    // INSERT INTO NULL ARRAY (LIE ABOUT CAPACITY)
    {
        vector v{1,0,nullptr};
        // preconditions
        //   A is null
        //   capacity is 1 (lie)
        //   size is 0
        assert(v.data() == nullptr);
        assert(v.capacity() == 1);
        assert(v.size() == 0);
        // expect push_back to succeed
        v.push_back(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.data() != nullptr);
        assert(v.capacity() == 1);
        assert(v.size() == 1);

        //delete[] v.data();
    }

    // INSERT VALUE INTO ARRAY WITH CAPACITY 0
    {
        vector v{0,0,new int[1]{1}};
        // preconditions
        //   capacity is 0 (lie)
        //   size is 0
        //   A at index 0 is 1
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        assert(v.data()[0] == 1);
        // expect push_back to succeed
        v.push_back(-1);
        // postconditions
        //   capacity is 1
        //   size is 1
        //   A at index 0 is -1
        //   no memory leaks
        assert(v.capacity() == 1);
        assert(v.size() == 1);
        assert(v.data()[0] == -1);

        //delete[] v.data();
    }
    */

    // INSERT VALUE INTO EMPTY ARRAY
    {
        //vector v{10, 0, new int[10]{2}};
        vector v;
        v.reserve(10);
        // preconditions
        //   capacity > 0
        //   size is 0
        //   A at 0 is not 1
        assert(v.capacity() > 0);
        assert(v.size() == 0);
        assert(v.data()[0] != 1);
        // expect push_back to succeed
        size_t old_capacity = v.capacity();
        v.push_back(1);
        // postconditions
        //   capacity did not change
        //   size is 1
        //   A at index 0 is 1
        assert(v.capacity() == old_capacity);
        assert(v.size() == 1);
        assert(v.data()[0] == 1);

        //delete[] v.data();
    }

    // FILL UP THE ARRAY
    {
        //vector v{10,0,new int[10]{}};
        vector v;
        v.reserve(10);
        for (int i = 0; i < 10; i++) {
            // preconditions
            //   size is i
            //   capacity is 10
            //   A at i is 0
            assert(v.size() == unsigned(i));
            assert(v.capacity() == 10);
            assert(v.data()[i] == 0);
            // expect push_back to succeed
            v.push_back(i);
            // postconditions
            //   size is i+1
            //   capacity is 10
            //   A at index i is i
            assert(v.size() == unsigned(i+1));
            assert(v.capacity() == 10);
            assert(v.data()[i] == i);
        }

        for (int i = 0; i < 10; i++) {
            assert(v.data()[i] == i);
        }

        //delete[] v.data();
    }

    // INSERT INTO A FULL ARRAY
    {
        //vector v{2,2,new int[2]{10,11}};
        vector v({10,11});
        // preconditions
        //   capacity > 0
        //   size equals capacity
        assert(v.size() == v.capacity());
        assert(v.capacity() > 0);
        // expect push_back to succeed
        size_t old_capacity = v.capacity();
        v.push_back(1);
        // postconditions
        //   size equals old_capacity + 1 (old_size + 1)
        //   capacity doubles
        assert(v.size() == old_capacity + 1);
        assert(v.capacity() == 2*old_capacity);

        assert(v.data()[0] == 10);
        assert(v.data()[1] == 11);
        assert(v.data()[2] == 1);

        //delete[] v.data();
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
        assert(v.data() == nullptr);
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        // expect push_front to succeed
        v.push_front(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.data() != nullptr);
        assert(v.capacity() == 1);
        assert(v.size()== 1);

        //delete[] v.data();
    }

    /* OBSOLETE
    // INSERT INTO NULL ARRAY (LIE ABOUT CAPACITY)
    {
        vector v{1,0,nullptr};
        // preconditions
        //   A is null
        //   capacity is 1 (lie)
        //   size is 0
        assert(v.data() == nullptr);
        assert(v.capacity() == 1);
        assert(v.size() == 0);
        // expect push_front to succeed
        v.push_front(1);
        // postconditions
        //   A is not null
        //   capacity is 1
        //   size is 1
        assert(v.data() != nullptr);
        assert(v.capacity() == 1);
        assert(v.size() == 1);

        //delete[] v.data();
    }

    // INSERT VALUE INTO ARRAY WITH CAPACITY 0
    {
        vector v{0,0,new int[1]{1}};
        // preconditions
        //   capacity is 0 (lie)
        //   size is 0
        //   A at index 0 is 1
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        assert(v.data()[0] == 1);
        // expect push_front to succeed
        v.push_front(-1);
        // postconditions
        //   capacity is 1
        //   size is 1
        //   A at index 0 is -1
        //   no memory leaks
        assert(v.capacity() == 1);
        assert(v.size() == 1);
        assert(v.data()[0] == -1);

        //delete[] v.data();
    }
    */

    // INSERT VALUE INTO EMPTY ARRAY
    {
        //vector v{10, 0, new int[10]{2}};
        vector v;
        v.reserve(10);
        // preconditions
        //   capacity > 0
        //   size is 0
        //   A at 0 is not 1
        assert(v.capacity() > 0);
        assert(v.size() == 0);
        assert(v.data()[0] != 1);
        // expect push_front to succeed
        size_t old_capacity = v.capacity();
        v.push_front(1);
        // postconditions
        //   capacity did not change
        //   size is 1
        //   A at index 0 is 1
        assert(v.capacity() == old_capacity);
        assert(v.size() == 1);
        assert(v.data()[0] == 1);

        //delete[] v.data();
    }

    // FILL UP THE ARRAY
    {
        //vector v{10,0,new int[10]{}};
        vector v;
        v.reserve(10);
        for (int i = 0; i < 10; i++) {
            // preconditions
            //   size is i
            //   capacity is 10
            //   A at i is 0
            assert(v.size() == unsigned(i));
            assert(v.capacity() == 10);
            if (i == 0) {
                assert(v.data()[0] == 0);
            } else {
                assert(v.data()[0] == i-1);
            }
            // expect push_front to succeed
            v.push_front(i);
            // postconditions
            //   size is i+1
            //   capacity is 10
            //   A at index 0 is i
            assert(v.size() == unsigned(i+1));
            assert(v.capacity() == 10);
            assert(v.data()[0] == i);
        }

        for (int i = 0; i < 10; i++) {
            assert(v.data()[i] == 9-i);
        }

        //delete[] v.data();
    }

    // INSERT INTO A FULL ARRAY
    {
        //vector v{2,2,new int[2]{10,11}};
        vector v({10,11});
        // preconditions
        //   capacity > 0
        //   size equals capacity
        assert(v.size() == v.capacity());
        assert(v.capacity() > 0);
        // expect push_front to succeed
        size_t old_capacity = v.capacity();
        v.push_front(1);
        // postconditions
        //   size equals old_capacity + 1 (old_size + 1)
        //   capacity doubles
        //   A at 0 is 1
        assert(v.size() == old_capacity + 1);
        assert(v.capacity() == 2*old_capacity);

        assert(v.data()[0] == 1);
        assert(v.data()[1] == 10);
        assert(v.data()[2] == 11);

        //delete[] v.data();
    }
}

void test_insert() {
    vector v;

    assert(v.capacity() == 0);
    assert(v.size() == 0);

    // insert at not 0 into empty (possibly null)
    bool threw_expected_exception = false;
    try {
        v.insert(1, 1);
    } catch(const std::out_of_range& err) {
        threw_expected_exception = true;
    }
    assert(threw_expected_exception);
    assert(v.capacity() == 0);
    assert(v.size() == 0);

    // insert at 0 into empty
    bool threw_exception = false;
    try {
        v.insert(0, 1);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity() == 1);
    assert(v.size() == 1);
    assert(v.data()[0] == 1);

    // insert at front
    threw_exception = false;
    try {
        v.insert(0, 2);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity() == 2);
    assert(v.size() == 2);
    assert(v.data()[0] == 2);
    assert(v.data()[1] == 1);

    // insert at back
    threw_exception = false;
    try {
        v.insert(2, 3);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity() == 4);
    assert(v.size() == 3);
    assert(v.data()[0] == 2);
    assert(v.data()[1] == 1);
    assert(v.data()[2] == 3);

    // insert at middle
    threw_exception = false;
    try {
        v.insert(1, 4);
    } catch(...) {
        threw_exception = true;
    }
    assert(!threw_exception);
    assert(v.capacity() == 4);
    assert(v.size() == 4);
    assert(v.data()[0] == 2);
    assert(v.data()[1] == 4);
    assert(v.data()[2] == 1);
    assert(v.data()[3] == 3);

    // insert out of bounds in non empty array
    threw_expected_exception = false;
    try {
        v.insert(5, 5);
    } catch(const std::out_of_range& err) {
        threw_expected_exception = true;
    }
    assert(threw_expected_exception);
    assert(v.capacity() == 4);
    assert(v.size() == 4);
    assert(v.data()[0] == 2);
    assert(v.data()[1] == 4);
    assert(v.data()[2] == 1);
    assert(v.data()[3] == 3);

    //delete[] v.data();
}

void test_pop_back() {
    /* OBSOLETE
    // REMOVE FROM NULL ARRAY
    {
        vector v{1,1,nullptr};
        // preconditions
        //   A is null
        //   capacity is > 0 (lie)
        //   size is > 0 (lie)
        assert(v.data() == nullptr);
        assert(v.capacity() > 0);
        assert(v.size() > 0);
        size_t old_size = v.size();
        size_t old_capacity = v.capacity();
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
        assert(v.data() == nullptr);
        assert(v.capacity() == old_capacity);
        assert(v.size()== old_size);
    }
    */

    // REMOVE THE LAST ELEMENT
    {
        //vector v{10, 10, new int[10]{1,2,3,4,5,6,7,8,9,10}};
        vector v({1,2,3,4,5,6,7,8,9,10});
        // preconditions
        //   capacity is > 1
        //   size is <= capacity and > 1
        //   A at 1 before end is 9
        //   A at end is 10
        assert(v.capacity() > 1);
        assert(v.size() <= v.capacity());
        assert(v.size() > 1);
        assert(v.data()[v.size()-2] == 9);
        assert(v.data()[v.size()-1] == 10);
        // expect pop_back to return 10
        size_t old_size = v.size();
        size_t old_capacity = v.capacity();
        assert(v.pop_back() == 10);
        // postconditions
        //   capacity did not change
        //   size is 1 less than previous
        //   A at end is 9
        assert(v.capacity() == old_capacity);
        assert(v.size() == old_size - 1);
        assert(v.data()[v.size()-1] == 9);

        //delete[] v.data();
    }

    // REMOVE ALL ELEMENTS FROM BACK
    {
        //vector v{9,9,new int[9]{1,2,3,4,5,6,7,8,9}};
        vector v({1,2,3,4,5,6,7,8,9});
        size_t old_capacity = v.capacity();
        for (int i = 9; i > 0; i--) {
            // preconditions
            //   capacity is > 0
            //   size is i
            //   A at end is i
            assert(v.size() == unsigned(i));
            assert(v.data()[v.size()-1] == i);
            // expect pop_back to return i
            assert(v.pop_back() == i);
            // postconditions
            //   capacity did not change
            //   size is i-1
            //   A at index i-2 (end) is i-1
            assert(v.capacity() == old_capacity);
            assert(v.size() == unsigned(i-1));
            if (i > 1) {
                assert(v.data()[v.size()-1] == i-1);
            }
        }

        //delete[] v.data();
    }

    // ATTEMPT TO REMOVE FROM NULL
    {
        vector v;
        // preconditions
        //   size is 0
        //   capacity is 0
        //   A is null
        assert(v.size()== 0);
        assert(v.capacity() == 0);
        assert(v.data() == nullptr);
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
        assert(v.size()== 0);
        assert(v.capacity() == 0);
        assert(v.data() == nullptr);
    }

    // ATTEMPT TO REMOVE FROM EMPTY
    {
        //vector v{5,0,new int[5]{1}};
        vector v;
        v.reserve(5);
        // preconditions
        //   size is 0
        //   capacity is > 0
        //   A is not null
        assert(v.size() == 0);
        assert(v.capacity() > 0);
        assert(v.data() != nullptr);
        // expect pop_back to throw invalid_argument exception
        size_t old_capacity = v.capacity();
        const int* old_A = v.data();
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
        assert(v.size()== 0);
        assert(v.capacity() == old_capacity);
        assert(v.data() == old_A);

        //delete[] v.data();
    }

}

void test_front() {
    // ATTEMPT TO GET FRONT OF NULL ARRAY
    {
        vector v;
        // pre
        //   A is nullptr
        // expect front of null to throw invalid_argument exception
        assert(v.data() == nullptr);
        bool throws_expected_exception = false;
        size_t old_size = v.size();
        size_t old_capacity = v.capacity();
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
        assert(v.size() == old_size);
        assert(v.capacity() == old_capacity);
        assert(v.data() == nullptr);
    }

    // ATTEMPT TO GET FRONT OF EMPTY ARRAY
    {
        //vector v{10, 0, new int[10]};
        vector v;
        v.reserve(10);
        // pre
        //   A is not null
        //   size is 0
        assert(v.data() != nullptr);
        assert(v.size() == 0);
        // expect front of empty to throw out_of_range exception
        bool throws_expected_exception = false;
        size_t old_capacity = v.capacity();
        const int* old_A = v.data(); 
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
        assert(v.size() == 0);
        assert(v.capacity() == old_capacity);
        assert(v.data() == old_A);

        //delete[] v.data();
    }

    // GET FRONT OF NON-EMPTY ARRAY
    {
        //vector v{4, 2, new int[4]{10,11}};
        vector v({10,11});
        v.reserve(4);
        // pre
        //   A[0] is 10
        //   A[1] is 11
        //   size is 1
        assert(v.data()[0] == 10);
        assert(v.data()[1] == 11);
        assert(v.size() == 2);
        // expect front of to be 10
        assert(v.front() == 10);
        // post
        //   A[0] is 10
        //   A[1] is 11
        //   size is 2
        assert(v.data()[0] == 10);
        assert(v.data()[1] == 11);
        assert(v.size() == 2);

        //delete[] v.data();
    }

    // FRONT RETURNS LVALUE REFERENCE
    {
        //vector v{3,2,new int[3]{}};
        vector v(3);
        // pre
        //   A at 0 is not 12
        assert(v.data()[0] != 12);
        assert(v.size() == 3);
        // expect assignment to return new value
        assert((v.front() = 12) == 12);
        // post
        //   v at 0 is 12, others unchanged
        //   size is unchanged
        assert(v.data()[0] == 12);
        assert(v.data()[1] == 0);
        assert(v.data()[2] == 0);
        assert(v.size() == 3);

        //delete[] v.data();
    }

    // FRONT OF CONST ARRAY
    {
        //const vector constV{3,3,new int[3]{102}};
        const vector v({102,0,0});
        assert(v.front() == 102);

        //delete[] constv.data();
    }

    // FRONT OF CONST NULL
    {
        const vector constNull;
        // pre
        //   object is const
        //   A is nullptr
        assert(constNull.data() == nullptr);
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
        assert(constNull.data() == nullptr);
    }


    // FRONT OF CONST EMPTY
    {
        //const vector constEmpty{1,0,new int[1]{}};
        const vector v(0);
        bool caught_expected_exception = false;
        try {
            v.front();
        } catch (const std::out_of_range& err) {
            caught_expected_exception = true;
        } catch (...) {}
        assert(caught_expected_exception);
        assert(v.data() != nullptr);

        //delete[] constEmpty.A;
    }
}

void test_back() {
    // ATTEMPT TO GET BACK OF NULL ARRAY
    {
        //vector v{10, 1, nullptr};
        vector v;
        // pre
        //   A is nullptr
        // expect back of null to throw invalid_argument exception
        assert(v.data() == nullptr);
        bool throws_expected_exception = false;
        size_t old_size = v.size();
        size_t old_capacity = v.capacity();
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
        assert(v.size() == old_size);
        assert(v.capacity() == old_capacity);
        assert(v.data() == nullptr);
    }

    // ATTEMPT TO GET BACK OF EMPTY ARRAY
    {
        //vector v{10, 0, new int[10]};
        vector v;
        v.reserve(10);
        // pre
        //   A is not null
        //   size is 0
        assert(v.data() != nullptr);
        assert(v.size() == 0);
        // expect back of empty to throw out_of_range exception
        bool throws_expected_exception = false;
        size_t old_capacity = v.capacity();
        const int* old_A = v.data(); 
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
        assert(v.size() == 0);
        assert(v.capacity() == old_capacity);
        assert(v.data() == old_A);

        //delete[] v.data();
    }

    // GET BACK OF NON-EMPTY ARRAY
    {
        //vector v{4, 2, new int[4]{10,11}};
        vector v({10,11});
        v.reserve(4);
        // pre
        //   A[0] is 10
        //   A[1] is 11
        //   size is 1
        assert(v.data()[0] == 10);
        assert(v.data()[1] == 11);
        // expect back to be 11
        assert(v.back() == 11);
        // post
        //   A[0] is 10
        //   A[1] is 11
        //   size is 2
        assert(v.data()[0] == 10);
        assert(v.data()[1] == 11);
        assert(v.size() == 2);

        //delete[] v.data();
    }

    // BACK RETURNS LVALUE REFERENCE
    {
        //vector v{3,3,new int[3]{}};
        vector v(3);
        // pre
        //   A at 1 is not 12
        assert(v.data()[1] != 12);
        assert(v.size() == 3);
        // expect assignment to return new value
        assert((v.back() = 12) == 12);
        // post
        //   A at 1 is 12, others unchanged
        //   size is unchanged
        assert(v.data()[0] == 0);
        assert(v.data()[1] == 0);
        assert(v.data()[2] == 12);
        assert(v.size() == 3);

        //delete[] v.data();
    }

    // BACK OF CONST ARRAY
    {
        //const vector constV{3,3,new int[3]{0,0,221}};
        const vector v({0,0,221});
        assert(v.back() == 221);

        //delete[] constv.data();
    }

    // BACK OF CONST NULL
    {
        const vector constNull;
        // pre
        //   object is const
        //   A is nullptr
        assert(constNull.data() == nullptr);
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
        assert(constNull.data() == nullptr);
    }


    // BACK OF CONST EMPTY
    {
        //const vector constEmpty{1,0,new int[1]{}};
        const vector v(0);
        bool caught_expected_exception = false;
        try {
            v.back();
        } catch (const std::out_of_range& err) {
            caught_expected_exception = true;
        } catch (...) {}
        assert(caught_expected_exception);
        assert(v.data() != nullptr);

        //delete[] constEmpty.A;
    }
}

void test_at() {
    // ATTEMPT TO ACCESS NULL ARRAY
    {
        //vector v{1, 1, nullptr};
        vector v;
        // pre
        //   A is nullptr
        assert(v.data() == nullptr);
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
    }

    // ATTEMPT TO ACCESS EMPTY ARRAY
    {
        //vector v{5,0,new int[5]};
        vector v;
        v.reserve(5);
        // pre
        //   A is not null
        //   size = 0
        assert(v.data() != nullptr);
        assert(v.size() == 0);
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
        assert(v.size()== 0);

        //delete[] v.data();
    }

    // ACCESS MIDDLE OF ARRAY
    {
        //vector v{10, 10, new int[10]{9,-1,-2,0,-4,3,7,5,6,8}};
        vector v({9,-1,-2,0,-4,3,7,5,6,8});
        // pre
        //   A[8] is 6
        //   A[7] is 5
        //   A[3] is 0
        //   size is 10
        assert(v.data()[8] == 6);
        assert(v.data()[7] == 5);
        assert(v.data()[3] == 0);
        assert(v.size() == 10);
        // expect A at {8,7,3} to be {6,5,0}
        assert(v.at(8) == 6);
        assert(v.at(7) == 5);
        assert(v.at(3) == 0);
        // post
        //   A[8] is 6
        //   A[7] is 5
        //   A[3] is 0
        //   size is 10
        assert(v.data()[8] == 6);
        assert(v.data()[7] == 5);
        assert(v.data()[3] == 0);
        assert(v.size() == 10);
        
        //delete[] v.data();
    }

    // ATTEMPT TO ACCESS ARRAY OUT OF BOUNDS
    {
        //vector v{10, 5, new int[10]{1,2,3,4,5}};
        vector v({1,2,3,4,5});
        v.reserve(10);
        // pre
        //   size is 5
        assert(v.size() == 5);
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

        //delete[] v.data();
    }

    // ATTEMPT TO ACCESS CONST ARRAY OUT OF BOUNDS
    {
        //const vector v{10, 5, new int[10]{1,2,3,4,5}};
        const vector v({1,2,3,4,5});
        // pre
        //   size is 5
        assert(v.size() == 5);
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

        //delete[] v.data();
    }

    // AT RETURNS LVALUE REFERENCE
    {
        //vector v{10, 5, new int[10]{}};
        vector v(5);
        v.reserve(10);
        // pre
        //   size > 3
        //   A at 2 is not 7
        assert(v.size() > 3);
        assert(v.data()[2] != 7);
        size_t old_size = v.size();
        // expect at(A,size,2) = 7 to set A at 2 to 7
        v.at(2) = 7;
        // post
        //   size did not change
        //   A at 2 is 7
        assert(v.size() == old_size);
        assert(v.data()[2] == 7);

        //delete[] v.data();
    }

    // ACCESS CONST ARRAY
    {
        //const vector constV{3, 2, new int[3]{0,121}};
        const vector v({0,121,0});
        assert(v.at(1) == 121);

        //delete[] constv.data();
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
    {
        //vector v{10, 5, new int[10]{12,13,17,15,16}};
        vector v({12,13,17,15,16});
        v.reserve(10);
        // pre
        //   A is [12, 13, 17, 15, 16]
        //   size is 5
        //   capacity is 10
        assert(v.data()[0] == 12);
        assert(v.data()[1] == 13);
        assert(v.data()[2] == 17);
        assert(v.data()[3] == 15);
        assert(v.data()[4] == 16);
        assert(v.size() == 5);
        assert(v.capacity() == 10);
        // expect resize to double the capacity
        v.resize();
        // post
        //   A is [12, 13, 17, 15, 16]
        //   size is 5
        //   capacity is 20
        assert(v.data()[0] == 12);
        assert(v.data()[1] == 13);
        assert(v.data()[2] == 17);
        assert(v.data()[3] == 15);
        assert(v.data()[4] == 16);
        // zeros in new part of array
        assert(v.data()[10] == 0);
        assert(v.data()[19] == 0);
        assert(v.size() == 5);
        assert(v.capacity() == 20);

        // no easy way to tell if the allocation was _actually_ correct

        //delete[] v.data();
    }

}

void test_pop_front() {
    /* OBSOLETE
    // REMOVE FROM NULL ARRAY
    {
        vector v{1,1,nullptr};
        // preconditions
        //   A is null
        //   capacity is > 0 (lie)
        //   size is > 0 (lie)
        assert(v.data() == nullptr);
        assert(v.capacity() > 0);
        assert(v.size() > 0);
        size_t old_size = v.size();
        size_t old_capacity = v.capacity();
        // expect pop_front to throw invalid_argument exception
        bool threw_expected_exception = false;
        try {
            v.pop_front();
        } catch (const std::invalid_argument& err) {
            threw_expected_exception = true;
        } catch (...) {
            assert(!"pop_front from null array throws wrong type of exception");
        }
        assert(threw_expected_exception);
        // postconditions
        //   A is null
        //   capacity did not change
        //   size did not change
        assert(v.data() == nullptr);
        assert(v.capacity() == old_capacity);
        assert(v.size()== old_size);
    }
    */

    // REMOVE THE FIRST ELEMENT
    {
        //vector v{10, 10, new int[10]{1,2,3,4,5,6,7,8,9,10}};
        vector v({1,2,3,4,5,6,7,8,9,10});
        // preconditions
        //   capacity is > 1
        //   size is <= capacity and > 1
        //   A at 1 after front is 2
        //   A at front is 1
        assert(v.capacity() > 1);
        assert(v.size() <= v.capacity());
        assert(v.size() > 1);
        assert(v.data()[1] == 2);
        assert(v.data()[0] == 1);
        // expect pop_front to return 1
        size_t old_size = v.size();
        size_t old_capacity = v.capacity();
        assert(v.pop_front() == 1);
        // postconditions
        //   capacity did not change
        //   size is 1 less than previous
        //   A at front is 2
        assert(v.capacity() == old_capacity);
        assert(v.size() == old_size - 1);
        assert(v.data()[0] == 2);

        //delete[] v.data();
    }

    // REMOVE ALL ELEMENTS FROM FRONT
    {
        //vector v{9,9,new int[9]{1,2,3,4,5,6,7,8,9}};
        vector v({1,2,3,4,5,6,7,8,9});
        size_t old_capacity = v.capacity();
        for (int i = 1; i < 10; i++) {
            // preconditions
            //   capacity is > 0
            //   size is 10 - i
            //   A at front is i
            assert(v.size() == 10 - unsigned(i));
            assert(v.data()[0] == i);
            // expect pop_front to return i
            size_t old_size = 10 - unsigned(i);
            assert(v.pop_front() == i);
            // postconditions
            //   capacity did not change
            //   size decreases by 1
            //   A at index i-2 (end) is i-1
            assert(v.capacity() == old_capacity);
            assert(v.size() == old_size - 1);
            if (v.size() > 0) {
                assert(v.data()[0] == i+1);
            }
        }

        //delete[] v.data();
    }

    // ATTEMPT TO REMOVE FROM EMPTY NULL
    {
        vector v;
        // preconditions
        //   size is 0
        //   capacity is 0
        //   A is null
        assert(v.size()== 0);
        assert(v.capacity() == 0);
        assert(v.data() == nullptr);
        // expect pop_front to throw invalid_argument exception
        bool threw_expected_exception = false;
        try {
            v.pop_front();
        } catch (const std::invalid_argument& err) {
            threw_expected_exception = true;
        } catch(...) {
            cout << "pop_front threw the wrong type of exception" << endl;
        }
        assert(threw_expected_exception);
        // postconditions
        //   size is 0
        //   capacity is 0
        //   A is null
        assert(v.size()== 0);
        assert(v.capacity() == 0);
        assert(v.data() == nullptr);
    }

    // ATTEMPT TO REMOVE FROM EMPTY
    {
        //vector v{5,0,new int[5]{1}};
        vector v;
        v.reserve(5);
        // preconditions
        //   size is 0
        //   capacity is > 0
        //   A is not null
        assert(v.size() == 0);
        assert(v.capacity() > 0);
        assert(v.data() != nullptr);
        // expect pop_front to throw invalid_argument exception
        size_t old_capacity = v.capacity();
        const int* old_A = v.data();
        bool threw_expected_exception = false;
        try {
            v.pop_front();
        } catch (const std::out_of_range& err) {
            threw_expected_exception = true;
        } catch(...) {
            cout << "pop_front threw the wrong type of exception" << endl;
        }
        assert(threw_expected_exception);
        // postconditions
        //   size is 0
        //   capacity is unchanged
        //   A is unchanged
        assert(v.size()== 0);
        assert(v.capacity() == old_capacity);
        assert(v.data() == old_A);

        //delete[] v.data();
    }
}

void test_erase_1() {
    // ERASE FROM NULL
    {
        vector v;
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        assert(v.data() == nullptr);
        bool threw_exception = false;
        try {
            v.erase(0);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        assert(v.capacity() == 0);
        assert(v.size() == 0);
        assert(v.data() == nullptr);
    }

    // ERASE FROM EMPTY
    {
        //vector v{10,0,new int[10]{}};
        vector v;
        v.reserve(10);
        assert(v.capacity() == 10);
        assert(v.size() == 0);
        assert(v.data() != nullptr);
        const int* old_A = v.data();
        bool threw_exception = false;
        try {
            v.erase(0);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        assert(v.capacity() == 10);
        assert(v.size() == 0);
        assert(v.data() == old_A);
    }

    // ERASE OUT OF BOUNDS
    {
        //vector v{10,3,new int[10]{8,6,7}};
        vector v({8,6,7});
        v.reserve(10);
        assert(v.capacity() == 10);
        assert(v.size() == 3);
        assert(v.data() != nullptr);
        const int* old_A = v.data();
       bool threw_exception = false;
        try {
            v.erase(3);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        assert(v.capacity() == 10);
        assert(v.size() == 3);
        assert(v.data() == old_A);
        assert(v.data()[0] == 8);
        assert(v.data()[1] == 6);
        assert(v.data()[2] == 7);
    }

    // ERASE 1 ELEMENT
    //   FRONT
    {
        //vector v{10,3,new int[10]{8,6,7}};
        vector v({8,6,7});
        v.reserve(10);
        assert(v.data()[0] == 8);
        assert(v.data()[1] == 6);
        assert(v.capacity() == 10);
        assert(v.size() == 3);
        assert(v.data() != nullptr);
        const int* old_A = v.data();
        bool threw_exception = false;
        try {
            v.erase(0);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        assert(v.data()[0] == 6);
        assert(v.data()[1] == 7);
        assert(v.capacity() == 10);
        assert(v.size() == 2);
        assert(v.data() == old_A);
    }
    //   MIDDLE
    {
        //vector v{10,3,new int[10]{8,6,7}};
        vector v({8,6,7});
        v.reserve(10);
        assert(v.data()[1] == 6);
        assert(v.data()[2] == 7);
        assert(v.capacity() == 10);
        assert(v.size() == 3);
        assert(v.data() != nullptr);
        const int* old_A = v.data();
        bool threw_exception = false;
        try {
            v.erase(1);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        assert(v.data()[0] == 8);
        assert(v.data()[1] == 7);
        assert(v.capacity() == 10);
        assert(v.size() == 2);
        assert(v.data() == old_A);
    }
    //   BACK
    {
        //vector v{10,3,new int[10]{8,6,7}};
        vector v({8,6,7});
        v.reserve(10);
        assert(v.data()[2] == 7);
        assert(v.capacity() == 10);
        assert(v.size() == 3);
        assert(v.data() != nullptr);
        const int* old_A = v.data();
        bool threw_exception = false;
        try {
            v.erase(2);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        assert(v.data()[0] == 8);
        assert(v.data()[1] == 6);
        assert(v.capacity() == 10);
        assert(v.size() == 2);
        assert(v.data() == old_A);
    }
}

void test_erase_range() {
    // ERASE FROM NULL
    {
        vector v;
        bool threw_exception = false;
        try {
            v.erase(0,1);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
    }

    // ERASE FROM EMPTY
    {
        vector v;
        v.reserve(10);
        bool threw_exception = false;
        try {
            v.erase(0,1);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
    }

    // ERASE OUT OF BOUNDS
    {
        vector v({1,2,3,4,5});
        bool threw_exception = false;
        try {
            v.erase(3,6);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        // expect v: [1,2,3]
        assert(v.size() == 3);
        assert(v.data()[0] == 1);
        assert(v.data()[1] == 2);
        assert(v.data()[2] == 3);
    }

    // ERASE RANGE OF ELEMENTS
    //   1 ELEMENT
    {
        vector v({1,2,3,4,5});
        bool threw_exception = false;
        try {
            v.erase(3,4);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        // expect v: [1,2,3,5]
        assert(v.size() == 4);
        assert(v.data()[0] == 1);
        assert(v.data()[1] == 2);
        assert(v.data()[2] == 3);
        assert(v.data()[3] == 5);
    }
    //   FRONT
    {
        vector v({1,2,3,4,5});
        bool threw_exception = false;
        try {
            v.erase(0,2);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        // expect v: [3,4,5]
        assert(v.size() == 3);
        assert(v.data()[0] == 3);
        assert(v.data()[1] == 4);
        assert(v.data()[2] == 5);
    }
    //   MIDDLE
    {
        vector v({1,2,3,4,5});
        bool threw_exception = false;
        try {
            v.erase(2,4);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        // expect v: [1,2,5]
        assert(v.size() == 3);
        assert(v.data()[0] == 1);
        assert(v.data()[1] == 2);
        assert(v.data()[2] == 5);
    }
    //   BACK
    {
        vector v({1,2,3,4,5});
        bool threw_exception = false;
        try {
            v.erase(3,5);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        // expect v: [1,2,3]
        assert(v.size() == 3);
        assert(v.data()[0] == 1);
        assert(v.data()[1] == 2);
        assert(v.data()[2] == 3);
    }
    //   WHOLE THING
    {
        vector v({1,2,3,4,5});
        bool threw_exception = false;
        try {
            v.erase(0,5);
        } catch (...) {
            threw_exception = true;
        }
        assert(!threw_exception);
        // expect v: []
        assert(v.size() == 0);
    }
}

void test_rule_of_three() {
    // destructor
    // copy constructor
    // copy assignment

    // make a vector
    vector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    size_t original_size = v.size();
    size_t original_capacity = v.capacity();
    {
        // copy it
        vector copy = v;

        // verify copy correctly
        assert(v.size() == original_size);
        assert(v.capacity() == original_capacity);
        assert(copy.size() == v.size());
        assert(copy.capacity() == v.capacity());
        for (size_t i = 0; i < v.size(); i++) {
            assert(copy.at(i) == int(i+1));
            assert(copy.at(i) == int(v.at(i)));
        }

        // verify deep copy
        copy.push_back(4);
        v.push_back(5);
        assert(v.back() == 5);
        assert(copy.back() == 4);

        // copy assignment
        copy.push_back(5);
        // copy: [1, 2, 3, 4, 5]
        //    v: [1, 2, 3, 5]
        v = copy;
        // expect v: [1, 2, 3, 4, 5]

        // verify copy correctly
        assert(v.size() == copy.size());
        assert(v.capacity() == copy.capacity());
        assert(copy.size() == 5);
        assert(copy.capacity() == 8);
        for (size_t i = 0; i < copy.size(); i++) {
            assert(copy.at(i) == int(i+1));
            assert(copy.at(i) == int(v.at(i)));
        }

        // verify deep copy
        copy.push_back(6);
        v.push_back(7);
        assert(v.back() == 7);
        assert(copy.back() == 6);

        // destruct copy
    }

    // verify that v is still OK
    assert(v.size() == original_size+3);
    assert(v.capacity() == 2*original_capacity);
    for (size_t i = 0; i < original_size+2; i++) {
        assert(v.at(i) == int(i+1));
    }
    assert(v.back() == 7);

    // self-assignment
    v = v;
    assert(v.size() == original_size+3);
    assert(v.capacity() == 2*original_capacity);
    for (size_t i = 0; i < original_size+2; i++) {
        assert(v.at(i) == int(i+1));
    }
    assert(v.back() == 7);
}

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

    cout << "ALL TESTS PASSING" << endl;

    return 0;
} 

/*
void test_rule_of_three() {
    // destructor
    // copy constructor
    // copy assignment

    // make a vector
    vector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    size_t original_size = v.size();
    size_t original_capacity = v.capacity();
    {
        // copy it
        vector copy = v;

        // verify copy correctly
        assert(v.size() == original_size);
        assert(v.capacity() == original_capacity);
        assert(copy.size == v.size());
        assert(copy.capacity == v.capacity());
        for (size_t i = 0; i < v.size(); i++) {
            assert(copy.at(i) == int(i+1));
            assert(v.at(i) == int(i+1));
            assert(copy.at(i) == int(v.at(i)));
        }

        // verify deep copy
        copy.push_back(4);
        v.push_back(5);
        assert(v.back() == 5);
        assert(copy.back() == 4);

        // copy assignment
        copy.pop_back();
        v = copy;

        // verify copy correctly
        assert(v.size() == original_size);
        assert(v.capacity() == original_capacity);
        assert(copy.size == original_size);
        assert(copy.capacity == original_capacity);
        for (size_t i = 0; i < original_size; i++) {
            assert(v.at(i) == int(i+1));
            assert(copy.at(i) == int(i+1));  
            assert(v.at(i) == int(v.at(i)));
        }

        // verify deep copy
        copy.push_back(4);
        v.push_back(5);
        assert(v.back() == 5);
        assert(copy.back() == 4);

        // destruct copy
    }

    // verify that v is still OK
    assert(v.size() == original_size+1);
    assert(v.capacity() == original_capacity);
    for (size_t i = 0; i < original_size; i++) {
        assert(v.at(i) == int(i+1));
    }
    assert(v.back() == 5);

    v = v;
    assert(v.size() == original_size+1);
    assert(v.capacity() == original_capacity);
    for (size_t i = 0; i < original_size; i++) {
        assert(v.at(i) == int(i+1));
    }
    assert(v.back() == 5);
}
*/