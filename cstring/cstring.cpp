#include "cstring.h"

#include <algorithm>

size_t Strlen(const char *str) {
    const char *end = str;
    while (*end != '\0') {
        end++;
    }
    return end - str;
}

int Strcmp(const char *first, const char *second) {
    for (size_t i = 0; i < std::min(Strlen(first), Strlen(second)); ++i) {
        if (first[i] < second[i]) {
            return -1;
        }
        if (second[i] < first[i]) {
            return 1;
        }
    }
    if (Strlen(first) < Strlen(second)) {
        return -1;
    } else if (Strlen(first) > Strlen(second)) {
        return 1;
    }
    return 0;
}

int Strncmp(const char *first, const char *second, size_t count) {
    for (size_t i = 0; i < std::min(Strlen(first), std::min(Strlen(second), count)); ++i) {
        if (first[i] < second[i]) {
            return -1;
        }
        if (second[i] < first[i]) {
            return 1;
        }
    }
    if (Strlen(first) < count || Strlen(second) < count) {
        if (Strlen(first) < Strlen(second)) {
            return -1;
        } else if (Strlen(first) > Strlen(second)) {
            return 1;
        }
    }
    return 0;
}

char *Strcpy(char *dest, const char *src) {
    if (src == nullptr) {
        dest = nullptr;
        return dest;
    }
    for (size_t i = 0; i < Strlen(src); ++i) {
        dest[i] = src[i];
    }
    dest[Strlen(src)] = '\0';
    return dest;
}

char *Strncpy(char *dest, const char *src, size_t count) {
    if (src == nullptr || dest == nullptr) {
        dest = nullptr;
        return dest;
    }
    size_t len = Strlen(src);
    for (size_t i = 0; i < count; ++i) {
        if (i >= len) {
            dest[i] = '\0';
            continue;
        }
        dest[i] = src[i];
    }
    if (count >= len) {
        dest[count] = '\0';
    }
    return dest;
}

char *Strcat(char *dest, const char *src) {
    if (src == nullptr || dest == nullptr) {
        return dest;
    }
    size_t len = Strlen(dest);
    size_t len_src = Strlen(src);
    for (size_t i = 0; i < len_src; ++i) {
        dest[i + len] = src[i];
    }
    return dest;
}

char *Strncat(char *dest, const char *src, size_t count) {
    if (src == nullptr || dest == nullptr) {
        return dest;
    }
    size_t len = Strlen(dest);
    for (size_t i = 0; i < count; ++i) {
        dest[len + i] = src[i];
        if (src[i] == '\0') {
            break;
        }
    }
    dest[len + count] = '\0';
    return dest;
}

const char *Strchr(const char *str, char symbol) {
    if (str == nullptr) {
        return nullptr;
    }
    for (size_t i = 0; i <= Strlen(str); ++i) {
        if (str[i] == symbol) {
            return str + i;
        }
    }
    return nullptr;
}

const char *Strrchr(const char *str, char symbol) {
    if (str == nullptr) {
        return nullptr;
    }
    for (size_t i = 0; i <= Strlen(str); ++i) {
        if (str[Strlen(str) - i] == symbol) {
            return str + Strlen(str) - i;
        }
    }
    return nullptr;
}

size_t Strspn(const char *dest, const char *src) {
    for (size_t i = 0; i < Strlen(dest); ++i) {
        if (Strchr(src, dest[i]) == nullptr) {
            return i;
        }
    }
    return Strlen(dest);
}

size_t Strcspn(const char *dest, const char *src) {
    for (size_t i = 0; i < Strlen(dest); ++i) {
        if (Strchr(src, dest[i]) != nullptr) {
            return i;
        }
    }
    return Strlen(dest);
}

const char *Strpbrk(const char *dest, const char *breakset) {
    for (size_t i = 0; i < Strlen(dest); ++i) {
        if (Strchr(breakset, dest[i]) != nullptr) {
            return dest + i;
        }
    }
    return nullptr;
}

const char *Strstr(const char *str, const char *pattern) {
    if (Strlen(pattern) == 0) {
        return str;
    }
    for (size_t i = 0; i < Strlen(str); ++i) {
        for (size_t j = 0; j < Strlen(pattern); j++) {
            if (str[i + j] != pattern[j]) {
                break;
            }
            if (j == Strlen(pattern) - 1) {
                return str + i;
            }
        }
    }
    return nullptr;
}
