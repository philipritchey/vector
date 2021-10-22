#include <iostream>
#include <cassert>
#include "vector.hpp"

using std::cout, std::endl;

bool push_back(int A[], size_t& size, size_t capacity, int value) {
    if (!A) {
        return false;
    }
    if (size >= capacity) {
        return false;
    }
    A[size] = value;
    size++;
    return true;
}

int pop_back(int A[], size_t& size) {
    if (!A) {
        throw std::invalid_argument("cannot pop from null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot pop from empty array");
    }
    int ret = A[size-1];
    size--;
    return ret;
}

int front(const int A[], size_t size) {
    if (!A) {
        throw std::invalid_argument("cannot get front of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get front of empty array");
    }
    return A[0];
}

int& front(int A[], size_t size) {
    if (!A) {
        throw std::invalid_argument("cannot get front of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get front of empty array");
    }
    return A[0];
}

int back(const int A[], size_t size) {
    //cout << __LINE__ << endl;
    if (!A) {
        throw std::invalid_argument("cannot get back of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get back of empty array");
    }
    return A[size-1];
}

int& back(int A[], size_t size) {
    //cout << __LINE__ << endl;
    if (!A) {
        throw std::invalid_argument("cannot get back of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get back of empty array");
    }
    return A[size-1];
}

int at(const int A[], size_t size, size_t index) {
    if (!A) {
        throw std::invalid_argument("cannot access null array");
    }
    if (index >= size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    return A[index];
}

int& at(int A[], size_t size, size_t index) {
    if (!A) {
        throw std::invalid_argument("cannot access null array");
    }
    if (index >= size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    return A[index];
}

void foo(const int A[], size_t size) {
    cout << __FUNCTION__ << endl;
    cout << back(A, size) << endl;
}

int* resize(int* A, size_t size, size_t& capacity) {
    // 1. make new and bigger
    int* B = new int[capacity * 2];

    // 2. copy old to new
    for (int index = 0; index < size; index++) {
        B[index] = A[index];
    }

    // 3. delete old
    delete[] A;

    // 4. update {array, capacity}
    A = B;
    capacity *= 2;

    // [5. return array]
    return A;
}

void test_push_back() {
    size_t capacity = 10;
    size_t size = 0;
    int* A = new int[capacity]{};

    // INSERT INTO NULL ARRAY
    int* A_is_nullptr = nullptr;
    // preconditions
    //   A is null
    //   capacity is 10
    //   size is 0
    assert(A_is_nullptr == nullptr);
    assert(capacity == 10);
    assert(size == 0);
    // expect push_back to fail
    assert(!push_back(A_is_nullptr, size, capacity, 1));
    // postconditions
    //   A is null
    //   capacity is 10
    //   size is 0
    assert(A_is_nullptr == nullptr);
    assert(capacity == 10);
    assert(size == 0);

    // INSERT INTO NULL ARRAY (LIE ABOUT SIZE)
    // preconditions
    //   A is null
    //   capacity is 10
    //   size is 1 (lie)
    size_t size_is_1 = 1;
    assert(A_is_nullptr == nullptr);
    assert(capacity == 10);
    assert(size_is_1 == 1);
    // expect push_back to fail
    assert(!push_back(A_is_nullptr, size_is_1, capacity, 1));
    // postconditions
    //   A is null
    //   capacity is 10
    //   size is 1 (lie)
    assert(A_is_nullptr == nullptr);
    assert(capacity == 10);
    assert(size_is_1 == 1);

    // INSERT VALUE INTO ARRAY WITH CAPACITY 0
    size_t capacity_is_zero = 0;
    size = 0;
    A[0] = 1;
    // preconditions
    //   capacity is 0 (lie)
    //   size is 0
    //   A at index 0 is 1
    assert(size == 0);
    assert(A[0] == 1);
    // expect push_back to fail
    assert(!push_back(A, size, capacity_is_zero, -1));
    // postconditions
    //   capacity is 0
    //   size is 0
    //   A at index 0 is 1
    assert(capacity_is_zero == 0);
    assert(size == 0);
    assert(A[0] == 1);

    // INSERT VALUE INTO EMPTY ARRAY
    A[0] = 0;
    // preconditions
    //   size is 0
    //   A at index 0 is not 1
    assert(size == 0);
    assert(A[0] != 1);
    // expect push_back to succeed
    assert(push_back(A, size, capacity, 1));
    // postconditions
    //   size is 1
    //   A at index 0 is 1
    assert(size == 1);
    assert(A[0] == 1);

    // FILL UP THE ARRAY
    for (int i = 2; i <= 10; i++) {
        // preconditions
        //   size is i-1
        //   A at index i-1 is 0
        assert(size == i-1);
        assert(A[i-1] == 0);
        // expect push_back to succeed
        assert(push_back(A, size, capacity, i));
        // postconditions
        //   size is i
        //   A at index i-1 is i
        assert(size == i);
        assert(A[i-1] == i);
    }

    // ATTEMPT TO INSERT INTO A FULL ARRAY
    // preconditions
    //   size is 10
    // expect push_back to fail
    assert(!push_back(A, size, capacity, 0));
    // postconditions
    //   size is 10
    assert(size == 10);

    delete[] A;
}

void test_pop_back() {
    size_t capacity = 10;
    size_t size = 10;
    int* A = new int[capacity]{1,2,3,4,5,6,7,8,9,10};

    // REMOVE FROM NULL ARRAY
    int* A_is_nullptr = nullptr;
    // preconditions
    //   A is null
    //   capacity is 10
    //   size is > 0
    assert(A_is_nullptr == nullptr);
    assert(capacity == 10);
    assert(size > 0);
    size_t old_size = size;
    // expect pop_back to throw invalid_argument exception
    try {
        pop_back(A_is_nullptr, size);
        assert(!"pop_back from null array");
    } catch (const std::invalid_argument& err) {
        assert(true);
    } catch (...) {
        assert(!"pop_back from null array throws wrong type of exception");
    }
    // postconditions
    //   A is null
    //   capacity is 10
    //   size did not change
    assert(A_is_nullptr == nullptr);
    assert(capacity == 10);
    assert(size == old_size);

    // REMOVE THE LAST ELEMENT
    // preconditions
    //   size is 10
    //   A at index 9 (end) is 10
    assert(size == 10);
    assert(A[size-1] == 10);
    // expect pop_back to return 10
    assert(pop_back(A, size) == 10);
    // postconditions
    //   size is 9
    //   A at index 8 (end) is 9
    assert(size == 9);
    assert(A[size-1] == 9);

    // REMOVE THE REST OF THE ELEMENTS FROM BACK
    for (int i = 9; i > 0; i--) {
        // preconditions
        //   size is i
        //   A at index i-1 (end) is i
        assert(size == i);
        assert(A[size-1] == i);
        // expect pop_back to return i
        assert(pop_back(A, size) == i);
        // postconditions
        //   size is i-1
        //   A at index i-2 (end) is i-1
        assert(size == i-1);
        assert(A[size-1] == i-1);
    }

    // ATTEMPT TO REMOVE FROM EMPTY
    // preconditions
    //   size is 0
    assert(size == 0);
    // expect pop_back to throw exception
    try {
        pop_back(A, size);
        assert(!"pop from empty");
    } catch (const std::exception& err) {
        assert(true);
    }
    // postconditions
    //   size is 0
    assert(size == 0);

    delete[] A;
}

void test_front() {
    size_t capacity = 10;
    int* A = new int[capacity]{};
    size_t size = 0;

    // ATTEMPT TO GET FRONT OF NULL ARRAY
    int* A_is_nullptr = nullptr;
    size_t size_is_1 = 1;
    // pre
    //   A is nullptr
    //   size is > 0 (lie)
    // expect front of null to throw invalid_argument exception
    assert(A_is_nullptr == nullptr);
    assert(size_is_1 == 1);
    try {
        front(A_is_nullptr, size_is_1);
        assert(!"front of null array");
    } catch (const std::invalid_argument& err) {
        assert(true);
    } catch (...) {
        assert(!"front of null array threw wrong kind of exception");
    }
    // post
    //   invalid_argument exception was caught
    //   size = 1 (lie)
    assert(size_is_1 == 1);

    // ATTEMPT TO GET FRONT OF EMPTY ARRAY
    // pre
    //   A is not null
    //   size = 0
    assert(A);
    assert(size == 0);
    // expect fornt of empty to throw out_of_range exception
    try {
        front(A, size);
        assert(!"front of empty array");
    } catch (const std::out_of_range& err) {
        assert(true);
    } catch (...) {
        assert(!"front of empty array threw wrong kind of exception");
    }
    // post
    //   out_of_range exception was caught
    //   size = 0
    assert(size == 0);

    // GET FRONT OF NON-EMPTY ARRAY
    A[0] = 10;
    A[1] = 11;
    size = 2;
    // pre
    //   A[0] is 10
    //   A[1] is 11
    //   size is 1,2
    size_t size_is_2 = 2;
    assert(A[0] == 10);
    assert(A[1] == 11);
    assert(size_is_2 == 2);
    assert(size_is_1 == 1);
    // expect front of {10} to be 10
    assert(front(A, size_is_1) == 10);
    // expect front of {10, 11} to be 10
    assert(front(A, size_is_2) == 10);
    // post
    //   A[0] is 10
    //   A[1] is 11
    //   size is 2
    assert(A[0] == 10);
    assert(A[1] == 11);
    assert(size_is_2 == 2);
    assert(size_is_1 == 1);

    // FRONT RETURNS LVALUE REFERENCE
    front(A, size) = 12;
    assert(A[0] == 12);
    assert(A[1] == 11);
    assert(size == 2);

    // FRONT OF CONST ARRAY
    const int constA[3]{102};
    assert(front(constA, 3) == 102);

    delete[] A;
}

void test_back() {
    size_t capacity = 10;
    int* A = new int[capacity]{};
    size_t size = 0;

    // ATTEMPT TO GET BACK OF NULL ARRAY
    int* A_is_nullptr = nullptr;
    size_t size_is_1 = 1;
    // pre
    //   A is nullptr
    //   size is > 0 (lie)
    assert(A_is_nullptr == nullptr);
    assert(size_is_1 == 1);
    // expect back of null to throw invalid_argument exception
    try {
        back(A_is_nullptr, size_is_1);
        assert(!"back of null array");
    } catch (const std::invalid_argument& err) {
        assert(true);
    } catch (...) {
        assert(!"back of null array threw wrong kind of exception");
    }
    // post
    //   invalid_argument exception was caught
    //   size = 1 (lie)
    assert(size_is_1 == 1);

    // ATTEMPT TO GET BACK OF EMPTY ARRAY
    // pre
    //   A is not null
    //   size = 0
    assert(A);
    assert(size == 0);
    // expect back of empty to throw out_of_range exception
    try {
        back(A, size);
        assert(!"back of empty array did not fail");
    } catch (const std::out_of_range& err) {
        assert(true);
    } catch (...) {
        assert(!"back of empty array threw wrong kind of exception");
    }
    // post
    //   out_of_range exception was caught
    //   size = 0
    assert(size == 0);

    // GET BACK OF NON-EMPTY ARRAY
    A[0] = 10;
    A[1] = 11;
    size = 2;
    // pre
    //   A[0] is 10
    //   A[1] is 11
    //   size is 1,2
    size_t size_is_2 = 2;
    assert(A[0] == 10);
    assert(A[1] == 11);
    assert(size_is_2 == 2);
    assert(size_is_1 == 1);
    // expect back of {10} to be 10
    assert(back(A, size_is_1) == 10);
    // expect back of {10, 11} to be 11
    assert(back(A, size_is_2) == 11);
    // post
    //   A[0] is 10
    //   A[1] is 11
    //   size is 2
    assert(A[0] == 10);
    assert(A[1] == 11);
    assert(size_is_2 == 2);
    assert(size_is_1 == 1);

    // BACK RETURNS LVALUE REFERENCE
    back(A, size) = 12;
    assert(A[0] == 10);
    assert(A[1] == 12);
    assert(size == 2);

    // BACK OF CONST ARRAY
    const int constA[3]{0,0,221};
    assert(back(constA, 3) == 221);

    delete[] A;
}

void test_at() {
    size_t capacity = 10;
    int* A = new int[capacity]{};
    size_t size = 0;

    // ATTEMPT TO ACCESS NULL ARRAY
    int* A_is_nullptr = nullptr;
    size_t size_is_1 = 1;
    // pre
    //   A is nullptr
    //   size is > 0 (lie)
    assert(A_is_nullptr == nullptr);
    assert(size_is_1 == 1);
    // expect at of null to throw invalid_argument exception
    try {
        at(A_is_nullptr, size_is_1, 0);
        assert(!"at of null array");
    } catch (const std::invalid_argument& err) {
        assert(true);
    } catch (...) {
        assert(!"at of null array threw wrong kind of exception");
    }
    // post
    //   invalid_argument exception was caught
    //   size = 1 (lie)
    assert(size_is_1 == 1);

    // ATTEMPT TO ACCESS EMPTY ARRAY
    // pre
    //   A is not null
    //   size = 0
    assert(A);
    assert(size == 0);
    // expect at of empty to throw out_of_range exception
    try {
        at(A, size, 0);
        assert(!"at of empty array did not fail");
    } catch (const std::out_of_range& err) {
        assert(true);
    } catch (...) {
        assert(!"at of empty array threw wrong kind of exception");
    }
    // post
    //   out_of_range exception was caught
    //   size = 0
    assert(size == 0);

    // ACCESS MIDDLE OF ARRAY
    A[8] = 6;
    A[7] = 5;
    A[3] = 9;
    size = 10;
    // pre
    //   A[8] is 6
    //   A[7] is 5
    //   A[3] is 0
    //   size is 10
    assert(A[8] == 6);
    assert(A[7] == 5);
    assert(A[3] == 9);
    assert(size == 10);
    // expect A at {8,7,3} to be {6,5,9}
    assert(at(A, size, 8) == 6);
    assert(at(A, size, 7) == 5);
    assert(at(A, size, 3) == 9);
    // post
    //   A[8] is 6
    //   A[7] is 5
    //   A[3] is 9
    //   size is 10
    assert(A[8] == 6);
    assert(A[7] == 5);
    assert(A[3] == 9);
    assert(size == 10);

    // ATTEMPT TO ACCESS ARRAY OUT OF BOUNDS
    size = 5;
    // pre
    //   size is 5
    assert(size == 5);
    // expect A at 5 to throw out_of_range exception
    try {
        at(A, size, 5);
        assert(!"rvalue at some out of bounds index");
    } catch (const std::out_of_range& err) {
        assert(true);
    } catch (...) {
        assert(!"at threw the wrong type of exception");
    }
    try {
        at(A, size, 5) = 0;
        assert(!"lvalue at some out of bounds index");
    } catch (const std::out_of_range& err) {
        assert(true);
    } catch (...) {
        assert(!"at threw the wrong type of exception");
    }

    // AT RETURNS LVALUE REFERENCE
    size = 5;
    A[2] = 0;
    // pre
    //   size > 3
    //   A at 2 is not 7
    assert(size > 3);
    assert(A[2] != 7);
    size_t old_size = size;
    // expect at(A,size,2) = 7 to set A at 2 to 7
    at(A, size, 2) = 7;
    // post
    //   size did not change
    //   A at 2 is 7
    assert(size == old_size);
    assert(A[2] == 7);

    // ACCESS CONST ARRAY
    const int constA[3]{0,121,0};
    assert(at(constA, 3, 1) == 121);

    const int* constB = nullptr;
    try {
        at(constB, 1, 0);
        assert(!"at of null const array");
    } catch (const std::invalid_argument& err) {
        assert(true);
    } catch (...) {
        assert(!"at of null const array threw wrong kind of exception");
    }

    delete[] A;
}

void test_resize() {
    size_t capacity = 10;
    int* A = new int[capacity]{12,13,17,15,16};
    size_t size = 5;

    // pre
    //   A is [12, 13, 17, 15, 16]
    //   size is 5
    //   capacity is 10
    assert(A[0] == 12);
    assert(A[1] == 13);
    assert(A[2] == 17);
    assert(A[3] == 15);
    assert(A[4] == 16);
    assert(size == 5);
    assert(capacity == 10);
    // expect resize to return a copy of the array with double the capacity
    A = resize(A, size, capacity);
    // post
    //   A is [12, 13, 17, 15, 16]
    //   size is 5
    //   capacity is 20
    assert(A[0] == 12);
    assert(A[1] == 13);
    assert(A[2] == 17);
    assert(A[3] == 15);
    assert(A[4] == 16);
    // zeros in new part of array
    assert(A[10] == 0);
    assert(A[19] == 0);
    assert(size == 5);
    assert(capacity == 20);

    // no easy way to tell if the allocation was _actually_ correct
}

int main() {

    test_push_back();
    test_pop_back();
    test_front();
    test_back();
    test_at();
    test_resize();

    return 0;
} 