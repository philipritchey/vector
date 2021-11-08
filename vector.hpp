#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>

template <typename T>
class vector {
    // data
    size_t the_capacity;
    size_t the_size;
    T* A;

 public:
    typedef T* iterator;

    vector() : the_capacity{0}, the_size{0}, A{nullptr} {}

    vector(size_t count, const T& value={}) : the_capacity{count}, the_size{the_capacity}, A{new T[the_capacity]{}} {
        for (size_t index = 0; index < the_size; index++) {
            A[index] = value;
        }
    }

    vector(std::initializer_list<T> init) : the_capacity{init.size()}, the_size{init.size()}, A{new T[the_capacity]{}} {
        size_t index = 0;
        for (T n : init) {
            A[index++] = n;
        }
    }

    vector(const vector& other) : the_capacity{other.the_capacity}, the_size{other.the_size}, A{new T[the_capacity]{}} {
        for (size_t index = 0; index < the_size; index++) {
            A[index] = other.A[index];
        }
    }

    ~vector() {
        delete[] A;
    }

    vector& operator=(const vector& rhs) {
        if (this != &rhs) {
            the_size = rhs.the_size;
            the_capacity = rhs.the_capacity;
            delete[] A;
            A = new T[the_capacity];
            for (size_t index = 0; index < the_size; index++) {
                A[index] = rhs.A[index];
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (!A || the_capacity == 0) {
            delete[] A;
            A = new T[1]{};
            the_capacity = 1;
            the_size = 0;
        } else if (the_size >= the_capacity) {
            resize();
        }
        A[the_size] = value;
        the_size++;
    }

    void push_front(const T& value) {
        if (!A || the_capacity == 0) {
            delete[] A;
            A = new T[1]{};
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

    void insert(size_t index, const T& value) {
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

    T pop_back() {
        if (!A) {
            throw std::invalid_argument("cannot pop from null array");
        }
        if (the_size == 0 || the_capacity == 0) {
            throw std::out_of_range("cannot pop from empty array");
        }
        T ret = A[the_size-1];
        the_size--;
        return ret;
    }

    T pop_front() {
        if (!A) {
            throw std::invalid_argument("cannot pop from null array");
        }
        if (the_size == 0 || the_capacity == 0) {
            throw std::out_of_range("cannot pop from empty array");
        }
        T ret = A[0];
        the_size--;
        for (size_t i = 0; i < the_size; i++) {
            A[i] = A[i+1];
        }
        return ret;
    }

    void erase(size_t index) {
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

    void erase(size_t first, size_t last) {
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

    const T& front() const {
        if (A == nullptr) {
            throw std::invalid_argument("cannot get front of null array");
        }
        if (the_size == 0) {
            throw std::out_of_range("cannot get front of empty array");
        }
        return A[0];
    }

    T& front() {
        if (A == nullptr) {
            throw std::invalid_argument("cannot get front of null array");
        }
        if (the_size == 0) {
            throw std::out_of_range("cannot get front of empty array");
        }
        return A[0];
    }

    const T& back() const {
        //cout << __LINE__ << endl;
        if (A == nullptr) {
            throw std::invalid_argument("cannot get back of null array");
        }
        if (the_size == 0) {
            throw std::out_of_range("cannot get back of empty array");
        }
        return A[the_size-1];
    }

    T& back() {
        //cout << __LINE__ << endl;
        if (A == nullptr) {
            throw std::invalid_argument("cannot get back of null array");
        }
        if (the_size == 0) {
            throw std::out_of_range("cannot get back of empty array");
        }
        return A[the_size-1];
    }

    const T& at(size_t index) const {
        if (!A) {
            throw std::invalid_argument("cannot access null array");
        }
        if (index >= the_size) {
            throw std::out_of_range("refuse to access out of bounds");
        }
        return A[index];
    }

    T& at(size_t index) {
        if (!A) {
            throw std::invalid_argument("cannot access null array");
        }
        if (index >= the_size) {
            throw std::out_of_range("refuse to access out of bounds");
        }
        return A[index];
    }

    void resize() {
        if (the_capacity > UINT64_MAX/2) {
            throw std::invalid_argument("cannot resize: too many elements");
        }
        reserve(the_capacity * 2);
    }

    void reserve(size_t new_the_capacity) {
        if (new_the_capacity > the_capacity) {
            // 1. make new and bigger
            T* B = new T[new_the_capacity]{};

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

    const T* data() const { return A; }

    size_t size() const { return the_size; }

    size_t capacity() const { return the_capacity; }

    iterator begin() {
        return A; // &A[0] <--> &(*(A+0)) <--> A 
    }

    iterator end() {
        return &A[the_size];
    }
};

#endif  // VECTOR_HPP
