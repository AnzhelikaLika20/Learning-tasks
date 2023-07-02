#pragma once

template <typename T, typename U>
T FirstValue(T begin, T end, U value) {
    for (T i = begin; i < end; i++) {
        if (*i == value) {
            return i;
        }
    }
    return end;
}

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T current = FirstValue(begin, end, value);
    if (current == end) {
        return end;
    }
    for (T i = current + 1; i < end; i++) {
        if (*i != value) {
            *current = *i;
            current++;
        }
    }
    return current;
}
