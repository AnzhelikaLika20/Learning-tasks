#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> order;
    std::vector<std::string> list_of_names;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            order.push_front(student_actions[i].name);
        } else {
            order.push_back(student_actions[i].name);
        }
    }
    for (size_t i = 0; i < queries.size(); i++) {
        list_of_names.push_back(order[queries[i] - 1]);
    }
    return list_of_names;
}
