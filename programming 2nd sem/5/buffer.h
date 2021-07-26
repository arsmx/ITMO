#pragma once

#include <iostream>
#include <iterator>
#include <initializer_list>

using namespace std;

template <class T>
class CCircleBuffer {
private:
    size_t _size = 0;
    size_t _capacity = 0;
    T *_value = nullptr;

public:
    class iter : public std::iterator<random_access_iterator_tag, T> {
    private:
        T *value = nullptr;

    public:
        using difference_type = typename std::iterator<random_access_iterator_tag, T>::difference_type;
        difference_type operator-(const iter &s) const {
            return value - s.value;
        }

        explicit iter(T* start) {
            value = start;
        }
        iter(const iter& num) {
            value = num.value;
        }

        T &operator*() {
            return *value;
        }
        T *operator->() {
            return value;
        }

        iter operator++() {
            ++value;
            return *this;
        }
        iter operator--() {
            --value;
            return *this;
        }
        iter operator+(int x) {
            value = value + x;
            return *this;
        }
        iter operator-(int x) {
            value = value - x;
            return *this;
        }

        bool operator==(const iter &s) const {
            return value == s.value;
        }
        bool operator!=(const iter &s) const {
            return value != s.value;
        }
        bool operator<(const iter &s) const {
            return value < s.value;
        }
        bool operator<=(const iter &s) const {
            return value <= s.value;
        }
        bool operator>(const iter &s) const {
            return value > s.value;
        }
        bool operator>=(const iter &s) const {
            return value >= s.value;
        }

        ~iter() = default;
    };

    // Конструкторы
    explicit CCircleBuffer(size_t capacity) {
        _capacity = capacity;
        _value = new T[_capacity];
    }
    CCircleBuffer(const CCircleBuffer& other) :
            _size(other._size),
            _capacity(other._capacity),
            _value(other.value) {
    }

    // начало и конец
    iter begin() const {
        return iter(_value);
    }
    iter end() const {
        return iter(_value + _size);
    }

    size_t capacity() const {
        return this->_capacity;
    }
    size_t size() const {
        return this->_size;
    }

    // Методы
    void push_front(T x);
    void pop_front();
    void push_back(T x);
    void pop_back();
    void set(iter pos, T x);
    void resize(size_t new_capacity);
    void show();

    // операторы
    T operator[] (size_t s) {
        return _value[s % _capacity];
    }

    CCircleBuffer& operator=(initializer_list<T> list) {
        _capacity = list.size();
        _value = new T[list.size()];
        for (auto i = list.begin(); i != list.end(); i++)
            push_back(*i);
        return *this;
    }

    ~CCircleBuffer() = default;
};