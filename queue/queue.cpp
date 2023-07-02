#include "queue.h"

Queue::Queue() {
    tail_ = nullptr;
    front_ = nullptr;
    size_ = 0;
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    if (size_ == 0) {
        front_ = new Node(value, tail_);
        size_++;
        return;
    }
    if (size_ == 1) {
        tail_ = new Node(value, nullptr);
        front_->next = tail_;
    } else {
        tail_->next = new Node(value, nullptr);
        tail_ = tail_->next;
    }
    size_++;
}

void Queue::Pop() {
    if (Empty()) {
        return;
    }
    Node* node = front_->next;
    delete front_;
    front_ = node;
    size_--;
    if (size_ == 0) {
        tail_ = nullptr;
        front_ = nullptr;
    }
}

int32_t Queue::Front() const {
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    for (int i = 0; i < size_; ++i) {
        Pop();
    }
    size_ = 0;
}

bool Queue::Empty() const {
    return size_ == 0;
}
