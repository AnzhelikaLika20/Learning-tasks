#pragma once

#include <algorithm>

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    for (Iterator i = begin; i < end; ++i) {
        std::swap(*(begin++), *(--end));
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}