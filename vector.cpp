#include <iostream>
#include "vector.hpp"

// TODO: define vector methods here

vector::vector() : the_capacity{0}, the_size{0}, A{nullptr} {}

vector::vector(size_t count, int value) : the_capacity{count}, the_size{the_capacity}, A{new int[the_capacity]{}} {
    for (size_t index = 0; index < the_size; index++) {
        A[index] = value;
    }
}

vector::vector(std::initializer_list<int> init) : the_capacity{init.size()}, the_size{init.size()}, A{new int[the_capacity]{}} {
    size_t index = 0;
    for (int n : init) {
        A[index++] = n;
    }
}

vector::vector(const vector& other) : the_capacity{other.the_capacity}, the_size{other.the_size}, A{new int[the_capacity]{}} {
    for (size_t index = 0; index < the_size; index++) {
        A[index] = other.A[index];
    }
}

vector::~vector() {
    delete[] A;
}

vector& vector::operator=(const vector& rhs) {
    if (this != &rhs) {
        the_size = rhs.the_size;
        the_capacity = rhs.the_capacity;
        delete[] A;
        A = new int[the_capacity];
        for (size_t index = 0; index < the_size; index++) {
            A[index] = rhs.A[index];
        }
    }
    return *this;
}

void vector::push_back(int value) {
    if (!A || the_capacity == 0) {
        delete[] A;
        A = new int[1]{};
        the_capacity = 1;
        the_size = 0;
    } else if (the_size >= the_capacity) {
        resize();
    }
    A[the_size] = value;
    the_size++;
}

void vector::push_front(int value) {
    if (!A || the_capacity == 0) {
        delete[] A;
        A = new int[1]{};
        the_capacity = 1;
        the_size = 0;
    } else if (the_size >= the_capacity) {
        resize();
    }
    // shift
    for (size_t index = the_size; index > 0; index--) {
        A[index] = A[index - 1];
    }
    // assign
    A[0] = value;
    the_size++;
}

void vector::insert(size_t index, int value) {
    if (index > the_size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    if (index == 0) {
        push_front(value);
    } else if (index == the_size) {
        push_back(value);
    } else {
        // middle
        // shift
        for (size_t i = the_size; i > index; i--) {
            A[i] = A[i - 1];
        }
        // assign
        A[index] = value;
        the_size++;
    }
}

int vector::pop_back() {
    if (!A) {
        throw std::invalid_argument("cannot pop from null array");
    }
    if (the_size == 0 || the_capacity == 0) {
        throw std::out_of_range("cannot pop from empty array");
    }
    int ret = A[the_size-1];
    the_size--;
    return ret;
}

int vector::pop_front() {
    if (!A) {
        throw std::invalid_argument("cannot pop from null array");
    }
    if (the_size == 0 || the_capacity == 0) {
        throw std::out_of_range("cannot pop from empty array");
    }
    int ret = A[0];
    the_size--;
    for (size_t i = 0; i < the_size; i++) {
        A[i] = A[i+1];
    }
    return ret;
}

void vector::erase(size_t index) {
    if (!A || the_size == 0 || the_capacity == 0 || index >= the_size) {
        // fail silently
        return;
    }
    if (index == 0) {
        pop_front();
    } else if (index == the_size - 1) {
        pop_back();
    } else {
        the_size--;
        for (size_t i = index; i < the_size; i++) {
            A[i] = A[i+1];
        }
    }
}

void vector::erase(size_t first, size_t last) {
    if (!A || the_size == 0 || the_capacity == 0 || first >= the_size) {
        // fail silently
        return;
    }
    if (last > the_size) {
        // don't erase past the end of the array
        last = the_size;
    }
    for (size_t index = first; index + last - first < the_size; index++) {
        A[index] = A[index + last - first];
    }
    the_size -= last - first;
}

int vector::front() const {
    if (A == nullptr) {
        throw std::invalid_argument("cannot get front of null array");
    }
    if (the_size == 0) {
        throw std::out_of_range("cannot get front of empty array");
    }
    return A[0];
}

int& vector::front() {
    if (A == nullptr) {
        throw std::invalid_argument("cannot get front of null array");
    }
    if (the_size == 0) {
        throw std::out_of_range("cannot get front of empty array");
    }
    return A[0];
}

int vector::back() const {
    //cout << __LINE__ << endl;
    if (A == nullptr) {
        throw std::invalid_argument("cannot get back of null array");
    }
    if (the_size == 0) {
        throw std::out_of_range("cannot get back of empty array");
    }
    return A[the_size-1];
}

int& vector::back() {
    //cout << __LINE__ << endl;
    if (A == nullptr) {
        throw std::invalid_argument("cannot get back of null array");
    }
    if (the_size == 0) {
        throw std::out_of_range("cannot get back of empty array");
    }
    return A[the_size-1];
}

int vector::at(size_t index) const {
    if (!A) {
        throw std::invalid_argument("cannot access null array");
    }
    if (index >= the_size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    return A[index];
}

int& vector::at(size_t index) {
    if (!A) {
        throw std::invalid_argument("cannot access null array");
    }
    if (index >= the_size) {
        throw std::out_of_range("refuse to access out of bounds");
    }
    return A[index];
}

void vector::resize() {
    if (the_capacity > UINT64_MAX/2) {
        throw std::invalid_argument("cannot resize: too many elements");
    }
    reserve(the_capacity * 2);
}

void vector::reserve(size_t new_the_capacity) {
    if (new_the_capacity > the_capacity) {
        // 1. make new and bigger
        int* B = new int[new_the_capacity]{};

        // 2. copy old to new
        for (size_t index = 0; index < the_size; index++) {
            B[index] = A[index];
        }

        // 3. delete old
        delete[] A;

        // 4. update {array, the_capacity}
        A = B;
        the_capacity = new_the_capacity;
    }
}

const int* vector::data() const { return A; }

size_t vector::size() const { return the_size; }
size_t vector::capacity() const { return the_capacity; }