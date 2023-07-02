#pragma once

#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array() {
        size_ = 0;
        data_ = nullptr;
    }

    explicit Array(size_t size) {
        size_ = size;
        data_ = new T[size_];
    }

    Array(std::initializer_list<T> list) : Array(list.size()) {
        int i = 0;
        for (auto var : list) {
            data_[i++] = var;
        }
    }

    Array(const Array& other) : Array(other.size()) {
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other[i];
        }
    }

    Array& operator=(const Array& other) {
        if (data_ == other.data_) {
            return *this;
        }
        delete[] data_;
        size_ = other.size();
        T* arr = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            arr[i] = other[i];
        }
        data_ = arr;
        return *this;
    }

    ~Array() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        return *(data_ + index);
    }

    const T& operator[](size_t index) const {
        return *(data_ + index);
    }

    size_t size() const {  // NOLINT
        return size_;
    }

    class Iterator {
    public:
        Iterator(T* current) {  // NOLINT
            current_ = current;
        }

        Iterator& operator++() {
            current_ += 1;
            return *this;
        }

        T& operator*() {
            return *(current_);
        }

        bool operator!=(const Iterator& other) {
            return other.current_ != this->current_;
        }

    private:
        T* current_;
    };

    Iterator begin() const {  // NOLINT
        return data_;
    }  // NOLINT

    Iterator end() const {  // NOLINT
        return data_ + size_;
    }
};
