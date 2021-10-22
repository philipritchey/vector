#ifndef VECTOR_HPP
#define VECTOR_HPP

// TODO: declare vector class and methods here

// [TODO: define template here]

struct vector {
    // data
    size_t capacity = 0;
    size_t size = 0;
    int* A = nullptr;    

    // methods
    bool push_back(int value);
    int pop_back();
    int front() const;
    int& front();
    int back() const;
    int& back();
    int at(size_t index) const;
    int& at(size_t index);
    void resize();
};

#endif  // VECTOR_HPP
