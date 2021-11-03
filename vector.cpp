#include <iostream>
#include "vector.hpp"

// TODO: define vector methods here

vector::vector() : capacity{0}, size{0}, A{nullptr} {}

vector::vector(size_t capacity, int value) : capacity{capacity}, size{capacity}, A{new int[capacity]{}} {
    for (size_t index = 0; index < size; index++) {
        A[index] = value;
    }
}

vector::vector(std::initializer_list<int> init) : capacity{init.size()}, size{init.size()}, A{new int[capacity]{}} {
    size_t index = 0;
    for (int n : init) {
        A[index++] = n;
    }
}

vector::vector(const vector& other) : capacity{other.capacity}, size{other.size}, A{new int[capacity]{}} {
    for (size_t index = 0; index < size; index++) {
        A[index] = other.A[index];
    }
}

vector::~vector() {
    delete[] A;
}

vector& vector::operator=(const vector& rhs) {
    if (this != &rhs) {
        size = rhs.size;
        capacity = rhs.capacity;
        delete[] A;
        A = new int[capacity];
        for (size_t index = 0; index < size; index++) {
            A[index] = rhs.A[index];
        }
    }
    return *this;
}

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

int vector::pop_front() {
    if (!A) {
        throw std::invalid_argument("cannot pop from null array");
    }
    if (size == 0 || capacity == 0) {
        throw std::out_of_range("cannot pop from empty array");
    }
    int ret = A[0];
    size--;
    for (size_t i = 0; i < size; i++) {
        A[i] = A[i+1];
    }
    return ret;
}

void vector::erase(size_t index) {
    if (!A || size == 0 || capacity == 0) {
        throw std::out_of_range("cannot erase from empty array");
    }
    if (index >= size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    if (index == 0) {
        pop_front();
    } else if (index == size - 1) {
        pop_back();
    } else {
        size--;
        for (size_t i = index; i < size; i++) {
            A[i] = A[i+1];
        }
    }
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
    if (capacity > UINT64_MAX/2) {
        throw std::invalid_argument("cannot resize: too many elements");
    }
    reserve(capacity * 2);
}

void vector::reserve(size_t new_capacity) {
    if (new_capacity > capacity) {
        // 1. make new and bigger
        int* B = new int[new_capacity]{};

        // 2. copy old to new
        for (size_t index = 0; index < size; index++) {
            B[index] = A[index];
        }

        // 3. delete old
        delete[] A;

        // 4. update {array, capacity}
        A = B;
        capacity = new_capacity;
    }
}

const int* vector::data() const { return A; }