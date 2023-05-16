#include <future>
#include "search.hpp"
#include "utils.hpp"
#include "constants.hpp"

Search::Search(uint16_t v, uint8_t k, bool r, bool s, int q_a) :
        generator_(v, k),
        ring_(r),
        opt_s_(s),
        quasi_amount(q_a) {}


uint16_t Search::index(uint32_t current, int32_t diff) const {
    return (generator_.vertices() + current + diff) % generator_.vertices();
}

std::vector<uint8_t> Search::BFS(const Gen &gen) const {
    uint8_t max = std::numeric_limits<uint8_t>::max();
    std::vector<uint8_t> result(generator_.vertices(), max);
    result[0] = 0;
    std::queue<uint16_t> q;
    q.push(0);

    uint8_t prev_step = 0;
    uint16_t cnt = 0;
    while (!q.empty()) {
        auto step = result[q.front()];

        if (opt_s_) {
            //// early-stop optimization
            //// used only for optimal circulants
            if (prev_step != step) {
                if (prev_step < optimal_diameter(generator_.vertices(), generator_.k()) - 3) {
                    if (cnt != steps[generator_.k()][prev_step + 1]) {
                        return std::vector<uint8_t>(generator_.vertices(), max);
                    }
                } else if (prev_step == optimal_diameter(generator_.vertices(), generator_.k()) - 3) {
                    if (cnt < static_cast<float>(steps[generator_.k()][prev_step + 1]) * 0.9) {
                        return std::vector<uint8_t>(generator_.vertices(), max);
                    }
                }
                cnt = 0;
            }
            prev_step = step;
        }

        auto idx = q.front();
        for (auto x: gen.data()) {
            auto next = index(idx, x);
            if (step + 1 < result[next]) {
                result[next] = step + 1;
                q.push(next);
                ++cnt;
            }
            next = index(idx, -x);
            if (step + 1 < result[next]) {
                result[next] = step + 1;
                q.push(next);
                ++cnt;
            }
        }
        q.pop();
    }
    if (*std::max_element(result.begin(), result.end()) == max) {
        return std::vector<uint8_t>(generator_.vertices(), max);
    }
    return result;
}


std::vector<GraphParameters> Search::batch_search(std::priority_queue<Gen> queue_) const {
    std::vector<GraphParameters> batch_opt;
    while (!queue_.empty()) {
        auto item = queue_.top();
        auto temp = GraphParameters(generator_.vertices(), item, BFS(item));


        if (opt_s_) {
            //// optimal search
            if (!batch_opt.empty()) {
                if (batch_opt[0].diameter() > temp.diameter()) {
                    batch_opt.clear();
                    batch_opt.push_back(temp);
                } else if (batch_opt[0].diameter() == temp.diameter() &&
                           batch_opt[0].average_distance() > temp.average_distance()) {
                    batch_opt.clear();
                    batch_opt.push_back(temp);
                } else if (batch_opt[0].diameter() == temp.diameter() &&
                           batch_opt[0].average_distance() == temp.average_distance()) {
                    batch_opt.push_back(temp);
                }
            } else {
                batch_opt.push_back(temp);
            }
        } else {
            ////quasi search
            if (temp.average_distance() < optimal_avg(generator_.vertices(),
                                                      generator_.k()) * (1 + static_cast<double>(generator_.k()) / 100.0)) {
                batch_opt.push_back(temp);
            }
        }
        queue_.pop();
    }
    return batch_opt;
}

void Search::search() {
    uint32_t lim = opt_s_ ? 600000 : 120000;
    int num_workers = 6;
    auto end = ring_ ? generator_.ring_end() : generator_.end();
    while (generator_.current() != end) {
        generatrix_.clear();
        generatrix_.reserve(lim);
        for (auto i = 0; generator_.current() != end && i < lim; ++i, generator_.next()) {
            auto g = generator_.current();
            if (g.score() != 0) {
                generatrix_.push_back(generator_.current());
            }
        }

        auto search_vectors = parts(generatrix_, num_workers);

        std::vector<std::future<std::vector<GraphParameters>>> async_results(num_workers);

        for (auto i = 0; i < search_vectors.size(); ++i) {
            async_results[i] = std::async(&Search::batch_search, this, search_vectors[i]);
        }

        int check = 0;
        while (check != num_workers) {
            for (auto &x: async_results) {
                if (x.valid()) {
                    auto result = x.get();
                    m.lock();
                    optimal_.insert(optimal_.end(), result.begin(), result.end());
                    ++check;
                    m.unlock();
                }
            }
        }

        if (opt_s_) {
            std::sort(optimal_.begin(), optimal_.end());

            auto it = std::find_if(optimal_.rbegin(), optimal_.rend(), [&](const auto &x) {
                return x.diameter() == optimal_.begin()->diameter()
                       && x.average_distance() == optimal_.begin()->average_distance();
            });
            optimal_.erase(optimal_.begin() + (optimal_.rend() - it), optimal_.end());
        } else if (optimal_.size() >= quasi_amount) {
            std::sort(optimal_.begin(), optimal_.end());
            return;
        }
    }
}

std::vector<GraphParameters> Search::optimal() const {
    return optimal_;
}
