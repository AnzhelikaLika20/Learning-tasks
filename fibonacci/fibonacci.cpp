#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t a = 0;
    int64_t b = 1;
    for (int i = 1; i <= n; i++) {
        int64_t temp = a;
        a = b;
        b += temp;
    }
    return a;
}
