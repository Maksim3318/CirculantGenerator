#include "gen.hpp"

#include <numeric>
#include "constants.hpp"

Gen::Gen(data_type &&temp, uint16_t v_) :
        data_(std::move(temp)) {
    calculateScore(v_);
}

const Gen::data_type &Gen::data() const {
    return data_;
}

uint16_t Gen::score() const {
    return score_;
}

void Gen::calculateScore(uint16_t v_) {
    score_ = 1;

    if (data_[data_.size() - 1] * (optimal_diameter(v_, data_.size()) + 1) < (v_ - 1) / 2) {
        score_ = 0;
        return;
    }

    auto gcd = v_;
    for (auto x : data_) {
        gcd = std::gcd(gcd, x);
    }
    if (gcd != 1) {
        score_ = 0;
        return;
    }
}

std::ostream &operator<<(std::ostream &os, const Gen &gen) {
    os << "score_: " << gen.score_ << std::endl << " data_: ";
    for (auto x: gen.data_) {
        os << x << " ";
    }
    os << std::endl;
    return os;
}
