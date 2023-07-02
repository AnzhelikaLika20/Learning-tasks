#include "caesar_cipher.h"

#include <string>

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string decipher = cipher;
    for (size_t i = 0; i < cipher.length(); ++i) {
        if (decipher[i] - shift < 'A') {
            decipher[i] = static_cast<char>('Z' - (shift - decipher[i] + 'A' - 1));
            continue;
        }
        decipher[i] = static_cast<char>(decipher[i] - shift);
    }
    return decipher;
}
