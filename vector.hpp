#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>

// TODO: declare vector class and methods here

// [TODO: define template here]

struct vector {
    // data
    size_t capacity;
    size_t size;
    int* A;

    // constructors
    vector();
    explicit vector(size_t, int=0);
    explicit vector(std::initializer_list<int>);
    vector(const vector&);
    ~vector();

    //vector(size_t c, size_t s, int* a) : capacity{c}, size{s}, A{a} {}

    // operator
    vector& operator=(const vector&);

    // methods
    void push_back(int value);
    void push_front(int value);
    void insert(size_t index, int value);
    int pop_back();
    int pop_front();
    void erase(size_t index);
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

/*
// constructors
    vector();
    vector(const vector&);
    ~vector();

    vector(size_t c, size_t s, int* a) : capacity{c}, size{s}, A{a} {}

    // operators
    vector& operator=(const vector&);
    */