#include "generator.hpp"

#include <numeric>
#include <tuple>

Generator::Generator(uint16_t v, uint8_t k) :
        vertices_(v),
        k_(k),
        ubound_((v - 1) / 2),
        current_(begin()) {}

Gen Generator::begin() const {
    Gen::data_type temp(k_);
    std::iota(temp.begin(), temp.end(), 1);
    return Gen(std::move(temp), vertices_);
}

Gen Generator::end() const {
    Gen::data_type temp(k_);
    std::iota(temp.begin(), temp.end(), ubound_ - k_ + 2);
    return Gen(std::move(temp), vertices_);
}

Gen Generator::ring_end() const {
    Gen::data_type temp(k_);
    std::iota(temp.begin(), temp.end(), 2);
    return Gen(std::move(temp), vertices_);
}

Gen Generator::current() const {
    return current_;
}

void Generator::next() {
    Gen::data_type data_ = current_.data();
    auto i = k_ - 1;
    for (; data_[i] >= ubound_ - k_ + i + 1 && i > 0; --i);
    data_[i] += 1;
    iota(data_.begin() + i, data_.end(), data_[i]);
    current_ = Gen(std::move(data_), vertices_);
}

bool operator==(const Generator &lhs, const Generator &rhs) {
    return std::tie(lhs.vertices_, lhs.k_) == std::tie(rhs.vertices_, rhs.k_);
}

uint16_t Generator::vertices() const {
    return vertices_;
}

bool operator!=(const Generator &lhs, const Generator &rhs) {
    return !(lhs == rhs);
}

uint8_t Generator::k() const {
    return k_;
}
