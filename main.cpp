#include <iostream>
#include <cassert>
#include "vector.hpp"

using std::cout, std::endl;

template <size_t N>
bool push_back(int (&A)[N], size_t& size, int value) {
    if (size >= N) {
        return false;
    }
    A[size] = value;
    size++;
    return true;
}

int pop_back(int A[], size_t& size) {
    if (size == 0) {
        throw std::out_of_range("cannot pop from empty array");
    }
    int ret = A[size-1];
    size--;
    return ret;
}

int main() {
    //cout << "TODO: write code to use and test your vector methods." << endl;

    int A[10]{};
    size_t size = 0;

    // INSERT VALUE INTO EMPTY ARRAY
    // preconditions
    //   size is 0
    //   A at index 0 is 0
    assert(size == 0);
    assert(A[0] == 0);
    // expect push_back to succeed
    assert(push_back(A, size, 1));
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
        assert(push_back(A, size, i));
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
    assert(!push_back(A, size, 0));
    // postconditions
    //   size is 10
    assert(size == 10);

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

    // REMOVE THE REST OF THE ELEMENTS
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
    


    return 0;
} 