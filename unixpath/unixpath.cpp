#include "unixpath.h"

#include <stack>

std::deque<std::string_view> GetNameOfCatalogs(std::string_view path) {
    std::deque<std::string_view> names;
    size_t i = 0;
    size_t prev_pos = 0;
    while (i < path.length()) {
        if (path[prev_pos] == '/') {
            prev_pos++;
            i = prev_pos + 1;
            continue;
        }
        if (path[i] == '/') {
            names.push_back(path.substr(prev_pos, i - prev_pos));
            prev_pos = i + 1;
            i++;
        }
        i++;
    }
    if (path.back() != '/') {
        names.push_back(path.substr(prev_pos, path.length() - prev_pos));
    }
    return names;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::deque<std::string_view> current_catalogs = GetNameOfCatalogs(current_working_dir);
    std::deque<std::string_view> path_catalogs = GetNameOfCatalogs(path);
    if (path[0] == '/') {
        current_catalogs.clear();
    }
    while (!path_catalogs.empty()) {
        if (path_catalogs.front() == "." || (path_catalogs.front() == ".." && current_catalogs.empty())) {
            path_catalogs.pop_front();
            continue;
        } else if (path_catalogs.front() == "..") {
            current_working_dir.remove_suffix(current_catalogs.back().size() + 1);
            current_catalogs.pop_back();
        } else {
            current_catalogs.push_back(path_catalogs.front());
        }
        path_catalogs.pop_front();
    }
    std::string absolute_path = "/";
    while (!current_catalogs.empty()) {
        absolute_path += current_catalogs.front();
        absolute_path += current_catalogs.size() == 1 ? "" : "/";
        current_catalogs.pop_front();
    }
    return absolute_path;
}
