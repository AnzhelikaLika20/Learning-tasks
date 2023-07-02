#include "range.h"

#include <vector>

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> range;
    int p = from;
    if (step == 0 || (from == to) || (step < 0 && from < to) || (step > 0 && from > to)) {
        return range;
    }
    if (step < 0) {
        while (p > to) {
            range.push_back(p);
            p += step;
        }
    } else {
        while (p < to) {
            range.push_back(p);
            p += step;
        }
    }
    return range;
}
