#pragma once

#include <queue>
#include <mutex>

#include "generator.hpp"
#include "graphparameters.hpp"

class Search {
public:
    Search() = delete;
    Search(uint16_t, uint8_t, bool = false, bool = true, int = 10);

    void search();
    std::vector<GraphParameters> optimal() const;

private:
    std::mutex m;
    Generator generator_;
    std::vector<GraphParameters> optimal_;
    std::vector<Gen> generatrix_;
    int quasi_amount;
    bool ring_;
    bool opt_s_;

    std::vector<uint8_t> BFS(const Gen &gen) const;

    std::vector<GraphParameters> batch_search(std::priority_queue<Gen>) const;

    uint16_t index(uint32_t current, int32_t) const;
};
