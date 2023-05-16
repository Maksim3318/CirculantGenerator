#pragma once

#include <vector>
#include <cstdint>
#include <cmath>

uint32_t ncr(uint8_t n, uint8_t k);

uint8_t optimal_diameter(int x, int k);

double optimal_avg(int x, int k);

const int max_d = 50;
const int max_k = 10;

extern const std::vector<double> factorials;
extern const std::vector<std::vector<size_t>> steps;
extern const std::vector<std::vector<size_t>> diameter_limits;