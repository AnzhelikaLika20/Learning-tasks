#include "provinces.h"

#include <cstdint>
#include <queue>
#include <vector>

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t count = 0;
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> provinces_copy(provinces.begin(),
                                                                                             provinces.end());
    int64_t first = 0;
    int64_t second = 0;
    while (provinces_copy.size() != 1) {
        first = provinces_copy.top();
        provinces_copy.pop();
        second = provinces_copy.top();
        provinces_copy.pop();
        provinces_copy.push(first + second);
        count += first + second;
    }
    return count;
}
