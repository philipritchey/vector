#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>

// TODO: declare vector class and methods here

// [TODO: define template here]

class vector {
    // data
    size_t the_capacity;
    size_t the_size;
    int* A;

 public:
    // constructors
    vector();
    explicit vector(size_t, int=0);
    explicit vector(std::initializer_list<int>);
    vector(const vector&);
    ~vector();

    // operator
    vector& operator=(const vector&);

    // methods
    size_t size() const;
    size_t capacity() const;
    void push_back(int value);
    void push_front(int value);
    void insert(size_t index, int value);
    int pop_back();
    int pop_front();
    void erase(size_t index);
    void erase(size_t first, size_t last);
    int front() const;
    int& front();
    int back() const;
    int& back();
    int at(size_t index) const;
    int& at(size_t index);
    void resize();

    void reserve(size_t new_capacity);
    const int* data() const;
};

#endif  // VECTOR_HPP
