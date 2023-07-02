#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    int cnt = 0;
    for (Iterator i = begin; i < end; ++i) {
        ++cnt;
        for (Iterator j = begin; j < end - cnt; ++j) {
            if (!comparator(*j, *(j + 1))) {
                std::swap(*j, *(j + 1));
            }
        }
    }
}
