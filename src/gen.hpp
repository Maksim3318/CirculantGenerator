#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

class Gen {
public:
    using data_type = std::vector<uint16_t>;

    Gen() = default;
    explicit Gen(data_type &&temp, uint16_t v_);

    Gen(const Gen&) = default;
    Gen(Gen &&) = default;

    Gen &operator=(const Gen&) = default;
    Gen &operator=(Gen &&) = default;

    const data_type &data() const;

    uint16_t score() const;

    auto operator<=>(const Gen&) const = default;

    friend std::ostream &operator<<(std::ostream &os, const Gen &gen);

private:
    uint16_t score_{};
    data_type data_;

    void calculateScore(uint16_t v_);
};

