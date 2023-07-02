#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator position = last;
    for (Iterator i = first; i < last; ++i) {
        if (*i == val) {
            position = i;
        }
    }
    return position;
}
