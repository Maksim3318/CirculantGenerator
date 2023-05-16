#include <numeric>
#include "graphparameters.hpp"
#include "utils.hpp"

GraphParameters::GraphParameters(uint16_t v, const Gen &gen, const std::vector<uint8_t> &dist) :
        nodes_(v),
        genx_(gen.data().size()),
        bisection_width_(calculate_bw(gen)),
        diameter_(calculate_d(dist)),
        connections_(v * gen.data().size()),
        avg_dist_(calculate_avg_d(dist)),
        genx_set_(gen.data()) {}

uint8_t GraphParameters::diameter() const {
    return diameter_;
}

uint8_t GraphParameters::generatrix() const {
    return genx_;
}

int16_t GraphParameters::bisection_width() const {
    return bisection_width_;
}

uint16_t GraphParameters::nodes() const {
    return nodes_;
}

double GraphParameters::average_distance() const {
    return avg_dist_;
}

uint64_t GraphParameters::connections() const {
    return connections_;
}

const Gen::data_type &GraphParameters::generatrix_set() const {
    return genx_set_;
}

int16_t GraphParameters::calculate_bw(const Gen &g) const {
    return -2 * std::accumulate(g.data().begin(), g.data().end(), 0);
}

uint8_t GraphParameters::calculate_d(const std::vector<uint8_t> &d) const {
    return *std::max_element(d.begin(), d.end());
}

double GraphParameters::calculate_avg_d(const std::vector<uint8_t> &d) const {
    return static_cast<double>(std::accumulate(d.begin(), d.end(), 0))
           / static_cast<double>(d.size() - 1);
}

std::ostream &operator<<(std::ostream &os, const GraphParameters &parameters) {
    os << " nodes_: " << parameters.nodes_
       << " genx_: " << +parameters.genx_
       << " genx_set_: " << parameters.genx_set_
       << " diameter_: " << +parameters.diameter_
       << " avg_dist_: " << parameters.avg_dist_
       << " bw_: " << -parameters.bisection_width_
       << " connections_: " << parameters.connections_ << std::endl;
    return os;
}
