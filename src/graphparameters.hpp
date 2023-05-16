#pragma once

#include <cstdint>
#include <vector>
#include <ostream>

#include "gen.hpp"

class GraphParameters {
public:
    GraphParameters(uint16_t v, const Gen &gen, const std::vector<uint8_t> &dist);

    uint8_t diameter() const;

    uint8_t generatrix() const;

    int16_t bisection_width() const;

    uint16_t nodes() const;

    double average_distance() const;

    uint64_t connections() const;

    const Gen::data_type &generatrix_set() const;

    auto operator<=>(const GraphParameters&) const = default;

    friend std::ostream &operator<<(std::ostream &os, const GraphParameters &parameters);

private:
    uint16_t nodes_;
    uint8_t genx_;
    uint8_t diameter_;
    double avg_dist_;
    Gen::data_type genx_set_;
    int16_t bisection_width_;

    uint64_t connections_;

    int16_t calculate_bw(const Gen&) const;

    uint8_t calculate_d(const std::vector<uint8_t> &) const;

    double calculate_avg_d(const std::vector<uint8_t> &) const;
};

