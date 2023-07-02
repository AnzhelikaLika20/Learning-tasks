#pragma once

#include <string>

template <class T>
class WeakPtr;

struct Counter {
    size_t strong_count;
    size_t weak_count;
};

template <class T>
class SharedPtr {
public:
    friend WeakPtr<T>;
    explicit SharedPtr(T* ptr = nullptr) : pointer_{ptr}, counter_{new Counter{1, 0}} {
    }
    explicit SharedPtr(const WeakPtr<T>& rhs) : pointer_{rhs.pointer_}, counter_{rhs.counter_} {
        if (rhs.IsExpired()) {
            pointer_ = nullptr;
        }
        counter_->strong_count++;
    }
    SharedPtr(SharedPtr<T>&& rhs) : pointer_{rhs.pointer_}, counter_{rhs.counter_} {
        rhs.counter_ = nullptr;
        rhs.pointer_ = nullptr;
    }
    SharedPtr(SharedPtr<T>& rhs) : pointer_{rhs.pointer_}, counter_{rhs.counter_} {
        counter_->strong_count++;
    }
    T* Get() {
        return pointer_;
    }
    void Reset(T* ptr = nullptr) {
        if (pointer_ == ptr) {
            return;
        }
        Delete();
        pointer_ = ptr;
        counter_ = new Counter{1, 0};
    }
    T& operator*() {
        return *pointer_;
    }
    SharedPtr& operator=(SharedPtr& other) {
        if (pointer_ == other.pointer_) {
            return *this;
        }
        Delete();
        pointer_ = other.pointer_;
        counter_ = other.counter_;
        ++counter_->strong_count;
        return *this;
    }
    SharedPtr& operator=(T* pointer) {
        if (pointer == pointer_) {
            return *this;
        }
        Delete();
        pointer_ = pointer;
        if (pointer_ != nullptr) {
            counter_ = new Counter{1, 0};
        }
    }
    SharedPtr& operator=(SharedPtr&& other) {
        if (other.pointer_ == pointer_) {
            return *this;
        }
        Delete();
        pointer_ = other.pointer_;
        counter_ = other.counter_;
        other.pointer_ = nullptr;
        other.counter_ = nullptr;
        return *this;
    }
    void Delete() {
        if (counter_ == nullptr) {
            return;
        }
        --counter_->strong_count;
        if (counter_->strong_count == 0) {
            delete pointer_;
            if (counter_->weak_count == 0) {
                delete counter_;
            }
        }
    }
    ~SharedPtr() {
        Delete();
    }

private:
    T* pointer_;
    Counter* counter_;
};

template <class T>
class WeakPtr {
    T* pointer_;
    Counter* counter_;

public:
    explicit WeakPtr() : pointer_{nullptr}, counter_{new Counter{0, 1}} {
    }
    WeakPtr(const WeakPtr<T>& rhs) : pointer_{rhs.pointer_}, counter_{rhs.counter_} {
        counter_->weak_count++;
    }
    WeakPtr(WeakPtr<T>&& rhs) : pointer_{rhs.pointer_}, counter_{rhs.counter_} {
        rhs.pointer_ = nullptr;
        rhs.counter_ = nullptr;
    }
    friend class SharedPtr<T>;
    explicit WeakPtr(SharedPtr<T>& rhs) : pointer_{rhs.pointer_}, counter_{rhs.counter_} {
        counter_->weak_count++;
    }
    WeakPtr& operator=(WeakPtr& other) {
        if (pointer_ == other.pointer_) {
            return *this;
        }
        Delete();
        pointer_ = other.pointer_;
        counter_ = other.counter_;
        ++counter_->weak_count;
        return *this;
    }
    WeakPtr& operator=(WeakPtr&& other) {
        if (pointer_ == other.pointer_) {
            return *this;
        }
        Delete();
        pointer_ = other.pointer_;
        counter_ = other.counter_;
        other.pointer_ = nullptr;
        other.counter_ = nullptr;
        return *this;
    }
    SharedPtr<T> Lock() {
        return IsExpired() ? SharedPtr<T>() : SharedPtr<T>(*this);
    }
    bool IsExpired() const {
        return counter_->strong_count == 0;
    }
    void Delete() {
        if (counter_ == nullptr) {
            return;
        }
        --counter_->weak_count;
        if (counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
        }
    }
    ~WeakPtr() {
        Delete();
    }
};
