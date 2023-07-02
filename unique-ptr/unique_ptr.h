#pragma once

template <class T>
class UniquePtr {
public:
    UniquePtr() : ptr_{nullptr} {
    }
    explicit UniquePtr(T* object) : ptr_{object} {
    }
    UniquePtr(UniquePtr&& unique_ptr) : ptr_{unique_ptr.ptr_} {
        unique_ptr.ptr_ = nullptr;
    }
    ~UniquePtr() {
        delete ptr_;
    }
    void Reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
    }
    T* operator->() {
        return ptr_;
    }
    UniquePtr& operator=(UniquePtr&& ptr) {
        delete ptr_;
        ptr_ = ptr.ptr_;
        ptr.ptr_ = nullptr;
        return *this;
    }

private:
    T* ptr_;
};
