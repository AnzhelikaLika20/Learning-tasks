#include "stack.h"

Node::Node(int32_t val, Node* prev) {
    value = val;
    previous = prev;
}

Stack::Stack() {
    head_ = nullptr;
    size_ = 0;
}

Stack::~Stack() {
    Clear();
}
void Stack::Push(int32_t value) {
    Node* node = new Node(value, head_);
    head_ = node;
    size_++;
}

void Stack::Pop() {
    if (Empty()) {
        return;
    }
    Node* node = head_->previous;
    delete head_;
    head_ = node;
    size_--;
}

bool Stack::Empty() const {
    return size_ == 0;
}

void Stack::Clear() {
    for (int i = 0; i < size_; ++i) {
        Pop();
    }
    size_ = 0;
}

int32_t Stack::Size() const {
    return size_;
}

int32_t Stack::Top() const {
    return head_->value;
}
