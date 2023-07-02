#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> vect;
    for (size_t i = 0; i < items.size(); ++i) {
        vect.push_back(std::make_unique<T>(*items[i]));
    }
    return vect;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::map<T, std::shared_ptr<T>> map;
    std::vector<std::shared_ptr<T>> vect;
    for (size_t i = 0; i < items.size(); ++i) {
        map[*(items[i])] = std::make_shared<T>(*items[i]);
    }
    for (size_t i = 0; i < items.size(); ++i) {
        vect.push_back(map[*(items[i])]);
    }
    return vect;
}
