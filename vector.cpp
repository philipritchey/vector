#include <iostream>
#include "vector.hpp"

// TODO: define vector methods here

void vector::push_back(int value) {
    if (!A || capacity == 0) {
        delete[] A;
        A = new int[1]{};
        capacity = 1;
        size = 0;
    } else if (size >= capacity) {
        resize();
    }
    A[size] = value;
    size++;
}

void vector::push_front(int value) {
    if (!A || capacity == 0) {
        delete[] A;
        A = new int[1]{};
        capacity = 1;
        size = 0;
    } else if (size >= capacity) {
        resize();
    }
    // shift
    for (size_t index = size; index > 0; index--) {
        A[index] = A[index - 1];
    }
    // assign
    A[0] = value;
    size++;
}

void vector::insert(size_t index, int value) {
    if (index > size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    if (index == 0) {
        push_front(value);
    } else if (index == size) {
        push_back(value);
    } else {
        // middle
        // shift
        for (size_t i = size; i > index; i--) {
            A[i] = A[i - 1];
        }
        // assign
        A[index] = value;
        size++;
    }
}

int vector::pop_back() {
    if (!A) {
        throw std::invalid_argument("cannot pop from null array");
    }
    if (size == 0 || capacity == 0) {
        throw std::out_of_range("cannot pop from empty array");
    }
    int ret = A[size-1];
    size--;
    return ret;
}

int vector::front() const {
    if (A == nullptr) {
        throw std::invalid_argument("cannot get front of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get front of empty array");
    }
    return A[0];
}

int& vector::front() {
    if (A == nullptr) {
        throw std::invalid_argument("cannot get front of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get front of empty array");
    }
    return A[0];
}

int vector::back() const {
    //cout << __LINE__ << endl;
    if (A == nullptr) {
        throw std::invalid_argument("cannot get back of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get back of empty array");
    }
    return A[size-1];
}

int& vector::back() {
    //cout << __LINE__ << endl;
    if (A == nullptr) {
        throw std::invalid_argument("cannot get back of null array");
    }
    if (size == 0) {
        throw std::out_of_range("cannot get back of empty array");
    }
    return A[size-1];
}

int vector::at(size_t index) const {
    if (!A) {
        throw std::invalid_argument("cannot access null array");
    }
    if (index >= size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    return A[index];
}

int& vector::at(size_t index) {
    if (!A) {
        throw std::invalid_argument("cannot access null array");
    }
    if (index >= size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    return A[index];
}

void vector::resize() {
    // 1. make new and bigger
    int* B = new int[capacity * 2]{};

    // 2. copy old to new
    for (size_t index = 0; index < size; index++) {
        B[index] = A[index];
    }

    // 3. delete old
    delete[] A;

    // 4. update {array, capacity}
    A = B;
    capacity *= 2;
}