#include "cppstring.h"

String::String() : size_{0}, capacity_{0}, data_{nullptr} {
}

String::String(size_t size, char symbol) : size_{size}, capacity_{size * 2}, data_{nullptr} {
    if (size_ != 0) {
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = symbol;
        }
    }
}

String::String(const char *src) : String() {
    const char *begin = src;
    while (*begin != '\0') {
        begin++;
        size_++;
    }
    if (size_ != 0) {
        capacity_ = 2 * size_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = src[i];
        }
    }
}
String::String(const char *src, size_t size) : size_{size}, capacity_{size * 2}, data_{nullptr} {
    if (size_ != 0) {
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = src[i];
        }
    }
}
String::~String() {
    delete[] data_;
}
String::String(const String &other) : size_{other.size_}, capacity_{size_ * 2}, data_{nullptr} {
    if (size_ != 0) {
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}
String &String::operator=(const String &other) {
    size_ = other.size_;
    capacity_ = size_ * 2;
    delete[] data_;
    data_ = nullptr;
    if (size_ != 0) {
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}
const char &String::operator[](size_t idx) const {
    return data_[idx];
}
char &String::operator[](size_t idx) {
    return data_[idx];
}
const char &String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}
char &String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}
const char &String::Front() const {
    return data_[0];
}
char &String::Front() {
    return data_[0];
}
const char &String::Back() const {
    return data_[size_ - 1];
}
char &String::Back() {
    return data_[size_ - 1];
}
const char *String::Data() const {
    return data_;
}
char *String::Data() {
    return data_;
}
const char *String::CStr() const {
    return data_;
}
char *String::CStr() {
    return data_;
}
bool String::Empty() const {
    return size_ == 0;
}
size_t String::Size() const {
    return size_;
}
size_t String::Length() const {
    return size_;
}
size_t String::Capacity() const {
    return capacity_;
}
void String::Clear() {
    size_ = 0;
}
void String::Swap(String &other) {
    std::swap(*this, other);
}
void String::PopBack() {
    size_--;
}
void String::PushBack(char c) {
    if (size_ == capacity_) {
        Reserve(capacity_ == 0 ? 2 : capacity_ * 2);
    }
    data_[size_] = c;
    size_++;
}
void String::Resize(size_t new_size, char symbol) {
    if (new_size < size_) {
        size_ = new_size;
    } else {
        if (new_size > capacity_) {
            Reserve(std::max(capacity_ * 2, new_size));
        }
        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = symbol;
        }
        size_ = new_size;
    }
}
void String::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        char *new_data = new char[new_capacity];
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
void String::ShrinkToFit() {
    capacity_ = size_;
}
int String::Compare(const String &other) const {
    for (size_t i = 0; i < std::min(other.size_, size_); ++i) {
        if (data_[i] < other.data_[i]) {
            return -1;
        } else if (data_[i] > other.data_[i]) {
            return 1;
        }
    }
    if (size_ < other.size_) {
        return -1;
    } else if (size_ > other.size_) {
        return 1;
    }
    return 0;
}
String &String::operator+=(const String &other) {
    for (size_t i = 0; i < other.size_; ++i) {
        PushBack(other.data_[i]);
    }
    return *this;
}
String operator+(const String &first, const String &second) {
    String new_string = first;
    new_string += second;
    return new_string;
}
std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (size_t i = 0; i < string.Size(); ++i) {
        stream << string.Data()[i];
    }
    return stream;
}
bool operator==(const String &first, const String &second) {
    return first.Compare(second) == 0;
}
bool operator!=(const String &first, const String &second) {
    return !(first == second);
}
bool operator>(const String &first, const String &second) {
    return first.Compare(second) == 1;
}
bool operator<(const String &first, const String &second) {
    return first.Compare(second) == -1;
}
bool operator>=(const String &first, const String &second) {
    return !(first < second);
}
bool operator<=(const String &first, const String &second) {
    return !(first > second);
}
void SafeCpy(char *dest, const char *src, size_t len) {
}
