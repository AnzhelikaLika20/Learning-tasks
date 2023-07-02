#pragma once

#include <algorithm>

template <class T>
class Vector {
public:
    Vector();

    explicit Vector(size_t size);

    Vector(std::initializer_list<int> list);

    Vector(Vector &vector);

    Vector(Vector &&vector);

    ~Vector();

    const T &operator[](size_t idx) const;

    T &operator[](size_t idx);

    Vector<T> &operator=(Vector<T> &vector);

    Vector &operator=(Vector &&vector);

    size_t Size() const;

    size_t Capacity() const;

    void Clear();

    void Swap(Vector &other);

    void PopBack();

    void PushBack(T c);

    void Reserve(size_t new_capacity);

    class Iterator : std::iterator<std::random_access_iterator_tag, T> {
    public:
        Iterator() : ptr_{nullptr} {
        }

        explicit Iterator(T *ptr) : ptr_(ptr){};

        T operator*() {
            return *ptr_;
        }

        Iterator &operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr_;
            return tmp;
        }

        Iterator &operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --ptr_;
            return tmp;
        }

        Iterator operator+=(int a) {
            this->ptr_ += a;
            return *this;
        }

        Iterator operator-=(int a) {
            this->ptr_ -= a;
            return *this;
        }

        Iterator operator-(int i) {
            return this->ptr_ - i;
        }

        Iterator operator+(int i) {
            return Iterator(ptr_ + i);
        }

        size_t operator-(Iterator it) {
            return this->ptr_ - it.ptr_;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return (a.ptr_ == b.ptr_);
        }

        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return (a.ptr_ != b.ptr_);
        }

        T *operator->() {
            return this->ptr_;
        }

    private:
        T *ptr_;
    };

    Iterator begin() {  // NOLINT
        return Iterator(&data_[0]);
    }

    Iterator end() {  // NOLINT
        return Iterator(&data_[size_]);
    }

    Iterator Begin() {
        return begin();
    }

    Iterator End() {
        return end();
    }

private:
    size_t size_;
    size_t capacity_;
    T *data_;
};

template <class T>
Vector<T>::Vector() : size_{0}, capacity_{0}, data_{nullptr} {
}

template <class T>
Vector<T>::Vector(size_t size) : size_{size}, capacity_{size}, data_{nullptr} {
    if (size_ != 0) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }
}

template <class T>
Vector<T>::Vector(std::initializer_list<int> list) : size_{list.size()}, capacity_{list.size()}, data_{nullptr} {
    if (size_ != 0) {
        int i = 0;
        data_ = new T[capacity_];
        for (auto a : list) {
            data_[i++] = a;
        }
    }
}

template <class T>
Vector<T>::Vector(Vector &other) : size_{other.size_}, capacity_{other.capacity_}, data_{nullptr} {
    if (size_ != 0) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

template <class T>
Vector<T>::Vector(Vector &&other) : size_{other.size_}, capacity_{size_}, data_{other.data_} {
    other.data_ = nullptr;
}

template <class T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <class T>
size_t Vector<T>::Size() const {
    return size_;
}

template <class T>
const T &Vector<T>::operator[](size_t idx) const {
    return data_[idx];
}

template <class T>
T &Vector<T>::operator[](size_t idx) {
    return data_[idx];
}

template <class T>
size_t Vector<T>::Capacity() const {
    return capacity_;
}

template <class T>
void Vector<T>::Clear() {
    size_ = 0;
}

template <class T>
void Vector<T>::Swap(Vector &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

template <class T>
void Vector<T>::PopBack() {
    size_--;
}

template <class T>
void Vector<T>::PushBack(T c) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 2 : capacity_ * 2);
    }
    data_[size_] = c;
    size_++;
}

template <class T>
void Vector<T>::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        T *new_data = new T[new_capacity];
        capacity_ = new_capacity;
        if (data_) {
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
        }
        delete[] data_;
        data_ = new_data;
    }
}

template <class T>
Vector<T> &Vector<T>::operator=(Vector<T> &vector) {
    size_ = 0;
    for (size_t i = 0; i < vector.Size(); ++i) {
        PushBack(vector[i]);
    }
    return *this;
}

template <class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&vector) {
    delete[] data_;
    data_ = vector.data_;
    capacity_ = vector.capacity_;
    size_ = vector.size_;
    vector.data_ = nullptr;
    return *this;
}
