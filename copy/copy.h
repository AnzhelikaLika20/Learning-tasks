#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    for (T i = src_begin; i < src_end; ++i) {
        *(dest++) = *(i);
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    dest--;
    for (T i = src_end - 1; i >= src_begin; --i) {
        *(dest--) = *(i);
    }
    return ++dest;
}