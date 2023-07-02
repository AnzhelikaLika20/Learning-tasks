#include "factorization.h"

#include <cstdint>

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> divisors;
    int cnt = 0;
    for (int64_t i = 2; i * i <= x; i++) {
        cnt = 0;
        while (x % i == 0) {
            x /= i;
            cnt++;
        }
        if (cnt != 0) {
            divisors.emplace_back(i, cnt);
        }
    }
    if (x != 1) {
        divisors.emplace_back(x, 1);
    }
    return divisors;
}
