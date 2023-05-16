#include "constants.hpp"

uint32_t ncr(uint8_t n, uint8_t k) {
    return static_cast<uint32_t>(factorials[n] / factorials[n - k] / factorials[k]);
}

uint8_t optimal_diameter(int x, int k) {
    return std::find_if(diameter_limits[k].begin(), diameter_limits[k].end(), [x](auto it) {
        return x <= it;
    }) - diameter_limits[k].begin();
}

double optimal_avg(int x, int k) {
    size_t sum = 0;
    for (size_t i = 0, lim = 0; i < steps[k].size() && lim < x; lim += steps[k][i], ++i) {
        sum += std::min(steps[k][i], x - lim) * i;
    }
    return static_cast<double>(sum) / (x - 1);
}

extern const std::vector<double> factorials = [] {
    std::vector<double> result(max_d + 1, 1);
    for (auto i = 2; i < max_d + 1; ++i) {
        result[i] = result[i - 1] * i;
    }
    return result;
}();

extern const std::vector<std::vector<size_t>> steps = [] {
    std::vector<std::vector<size_t>> result(max_k + 1);
    result[0] = std::move(std::vector<size_t>({0}));
    result[1] = std::move(std::vector<size_t>({0}));
    for (auto k = 2; k < max_k + 1; ++k) {
        int size = 10;
        if (k == 2) {
            size = 50;
        }
        if (k == 3) {
            size = 20;
        }
        auto sum = std::vector<size_t>(size + 1, 0);
        sum[0] = 1;
        for (auto i = 1; i < size + 1; ++i) {
            for (auto j = 1; j < std::min(i, k) + 1; ++j) {
                sum[i] += static_cast<size_t>(std::pow(2, j))
                          * ncr(k, j)
                          * ncr(i - 1, j - 1);
            }
        }
        result[k] = sum;
    }
    return result;
}();

extern const std::vector<std::vector<size_t>> diameter_limits = [] {
    auto result = steps;
    for (auto &vec: result) {
        for (auto i = 1; i < vec.size(); ++i) {
            vec[i] += vec[i - 1];
        }
    }
    return result;
}();