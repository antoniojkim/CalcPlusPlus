#pragma once

#include <exception>

template<typename T>
class FixedStack { // Fixed Size Stack
    const size_t capacity;
    T* data;
    int tail = 0;

    public:
        FixedStack(const size_t size): capacity{size}, data{new T[size]} {}
        ~FixedStack(){ delete[] data; }

        T& operator[](const size_t index){
            if (index < capacity){
                return data[index];
            }
            throw std::out_of_range("FixedStack::operator[] out of range");
        }
        const T& operator[](const size_t index) const {
            if (index < capacity){
                return data[index];
            }
            throw std::out_of_range("FixedStack::operator[] out of range");
        }

        bool empty() const { return tail == 0; }
        size_t size() const { return tail; }
        size_t maxSize() const { return capacity; }

        void push(T&& item){
            if (tail >= (int) capacity){
                throw std::out_of_range("FixedStack::push out of range");
            }
            data[tail++] = item;
        }
        T& peek(){ return data[tail-1]; }
        T& pop(){ return data[--tail]; }

        T* begin(){ return data; }
        T* end(){ return data+tail; }
};
