#include "reduce_fraction.h"

int64_t Gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return a;
    } else {
        return Gcd(b, a % b);
    }
}

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t gcd = Gcd(numerator, denominator);
    return numerator / gcd + denominator / gcd;
}
