#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int min_length = 8;
    const int max_length = 14;
    if (password.length() < min_length || password.length() > max_length) {
        return false;
    }
    bool lower_case_counter = false;
    bool upper_case_counter = false;
    bool digit_counter = false;
    bool other_symbols_counter = false;
    for (size_t i = 0; i < password.length(); i++) {
        const int lower_bound = 33;
        const int upper_bound = 126;
        if (password[i] < lower_bound || password[i] > upper_bound) {
            return false;
        }
        if (islower(password[i])) {
            lower_case_counter = true;
        } else if (isupper(password[i])) {
            upper_case_counter = true;
        } else if (isdigit(password[i])) {
            digit_counter = true;
        } else {
            other_symbols_counter = true;
        }
    }
    if (other_symbols_counter + lower_case_counter + upper_case_counter + digit_counter >= 3) {
        return true;
    } else {
        return false;
    }
}
