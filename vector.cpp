#include <iostream>
#include "vector.hpp"

// TODO: define vector methods here

bool vector::push_back(int value) {
    if (capacity == 0 || !A) {
        return false;
    }
    if (size >= capacity) {
        return false;
    }
    A[size] = value;
    size++;
    return true;
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