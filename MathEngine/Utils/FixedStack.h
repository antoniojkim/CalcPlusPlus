#pragma once

#include <exception>
#include <iostream>

template<typename T>
class FixedStack { // Fixed Size Stack
    size_t capacity;
    std::unique_ptr<T[]> data;
    int tail;

    public:
        FixedStack(const size_t size): capacity(size), data(new T[size]), tail(0) {}
        FixedStack(const FixedStack<T>& fs): capacity(fs.capacity), data(new T[capacity]), tail(fs.tail) {
            for(int i = 0; i < fs.tail; ++i){
                data[i] = fs.data[i];
            }
        }
        FixedStack(FixedStack<T>&& fs): capacity(fs.capacity), data(std::move(fs.data)), tail(fs.tail) {}

        FixedStack<T>& operator=(const FixedStack<T>& fs){
            if (this->capacity < fs.capacity){
                this->capacity = fs.capacity;
                this->data = std::unique_ptr<T[]>(new T[this->capacity]);
            }
            this->tail = fs.tail;
            for(int i = 0; i < fs.tail; ++i){
                data[i] = fs.data[i];
            }
        }
        FixedStack<T>& operator=(FixedStack<T>&& fs){
            this->capacity = fs.capacity;
            this->tail = fs.tail;
            this->data = std::move(fs.data);
        }

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

        void push(T& item){
            if (tail >= (int) capacity){
                throw std::out_of_range("FixedStack::push out of range");
            }
            data[tail++] = item;
        }
        void push(T&& item){
            if (tail >= (int) capacity){
                throw std::out_of_range("FixedStack::push out of range");
            }
            data[tail++] = item;
        }
        void push(FixedStack<T>& fs){
            for(auto& t : fs){
                push(t);
            }
        }
        void push(FixedStack<T>&& fs){
            for(auto& t : fs){
                push(std::move(t));
            }
            fs.clear();
        }
        T& peek(){ return data[tail-1]; }
        T pop(){ return data[--tail]; }
        void clear(){ tail = 0; }

        T* begin(){ return data.get(); }
        T* end(){ return data.get()+tail; }

        friend std::ostream& operator<<(std::ostream& out, FixedStack<T>& fs){
            out << "[";
            for (size_t i = 0; i < fs.size(); ++i){
                if (i != 0){ out << ", "; }
                out << fs[i];
            }
            return out << "]";
        }
};
