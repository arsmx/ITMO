#include "buffer.h"
using namespace std;
template<typename T>
void CCircleBuffer<T>::push_front(T s) {
    if (_size < _capacity) {
        for (size_t i = _size; i > 0; i--) {
            _value[i] = _value[i - 1];
        }
        _value[0] = s;
        _size++;
    }
    else {
        for (size_t i = _capacity - 1; i > 0; i--) {
            _value[i] = _value[i - 1];
        }
        _value[0] = s;
    }
}

template<typename T>
void CCircleBuffer<T>::pop_front() {
    for (size_t i = 0; i < _size - 1; i++) {
        _value[i] = _value[i + 1];
    }
    _size--;
}

template<typename T>
void CCircleBuffer<T>::push_back(T x) {
    if (_size < _capacity) {
        _value[_size] = x;
        _size++;
    }
    else {
        for (size_t i = 1; i < _capacity; i++) {
            _value[i - 1] = _value[i];
        }
        _value[_capacity - 1] = x;
    }
}

template<typename T>
void CCircleBuffer<T>::pop_back() {
    if (_size > 0) {
        _size--;
    }
}

template<typename T>
void CCircleBuffer<T>::resize(size_t new_capacity) {
    T* new_value = new T[new_capacity];
    _size = min(_size, new_capacity);
    for (size_t i = 0; i < _size; i++) {
        new_value[i] = _value[i];
    }
    delete _value;
    _value = new_value;
    _capacity = new_capacity;
}

template<typename T>
void CCircleBuffer<T>::set(iter pos, T x) {
    *(begin() + (pos - begin()) % _size) = x;
}

template<typename T>
void CCircleBuffer<T>::show() {
    cout << "Capacity: " << capacity() << endl;
    cout << "Size: " << size() << endl;
    for (size_t i = 0; i < _size; i++) {
        cout << *(begin() + i) << " ";
    }
    cout << "\n\n";
}