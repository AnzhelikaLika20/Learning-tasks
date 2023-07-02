#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t i = 0;
    size_t j = str.length() - 1;
    while (i < j) {
        while (i < j && str[i] == ' ') {
            i++;
        }
        while (i < j && str[j] == ' ') {
            j--;
        }
        if (i < j && str[i] != str[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}
