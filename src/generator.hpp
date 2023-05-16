#pragma once

#include <cstdint>
#include "gen.hpp"

class Generator {
public:
    Generator() = delete;
    explicit Generator(uint16_t v, uint8_t k);
    Generator &operator=(const Generator &) = default;
    Generator &operator=(Generator &&) = default;

    Gen begin() const;

    Gen end() const;
    Gen ring_end() const;

    Gen current() const;
    void next();

    uint16_t vertices() const;
    uint8_t k() const;

    friend bool operator==(const Generator &lhs, const Generator &rhs);

    friend bool operator!=(const Generator &lhs, const Generator &rhs);

private:
    uint16_t vertices_;
    uint16_t ubound_;
    uint8_t k_;
    Gen current_;
};
