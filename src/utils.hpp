#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

template<class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &s) {
    bool first = true;
    for (const auto &x: s) {
        if (!first) {
            os << " ";
        }
        first = false;
        os << x;
    }
    return os;
}


template<class T>
std::vector<std::priority_queue<T>> parts(const std::vector<T> &vec, uint8_t parts) {
    std::vector<std::priority_queue<T>> result(parts);
    for (auto i = 0; i < vec.size(); ++i) {
        result[i % parts].push(vec[i]);
    }
    return result;
}
