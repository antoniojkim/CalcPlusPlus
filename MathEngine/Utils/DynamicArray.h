#pragma once

#include <exception>
#include <memory>

template<typename T>
class DynamicArray { // Fixed Size Stack
    const int capacity;
    std::unique_ptr<T[]> data;

    public:
        DynamicArray(const int size): capacity{size}, data{new T[size]} {}

        T& operator[](const int index){
            if (index < 0){
                if (-index <= capacity){
                    return data[index+capacity];
                }
            }
            else if (index < capacity){
                return data[index];
            }
            throw std::out_of_range("DynamicArray::operator[] out of range");
        }
        const T& operator[](const int index) const {
            if (index < 0){
                if (-index <= capacity){
                    return data[index+capacity];
                }
            }
            else if (index < capacity){
                return data[index];
            }
            throw std::out_of_range("DynamicArray::operator[] out of range");
        }

        size_t size() const { return capacity; }

        T* begin() { return data.get(); }
        const T* begin() const { return data.get(); }
        T* end() { return data.get()+capacity; }
        const T* end() const { return data.get()+capacity; }
};
