#pragma once

#include <algorithm>

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return end;
    }
    T cur = begin + 1;
    while (cur < end) {
        if (*begin != *cur) {
            std::swap(*(begin + 1), *cur);
            begin++;
        }
        cur++;
    }
    return ++begin;
}