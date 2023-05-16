#include <iostream>
#include <filesystem>
#include <fstream>

#include "profile.hpp"
#include "search.hpp"
#include "utils.hpp"


int main() {
    LOG_DURATION("total")
    std::string query;
    const std::string err_msg = "Incorrect query";
    const std::string save_msg = "Result saved to ";
    while (getline(std::cin, query)) {
        if (query == "!q") {
            break;
        }
        uint16_t v, k, amount = 10;
        bool r = false, o = true;
        std::istringstream task (query);
        task >> v >> k;
        if (!task.eof()) {
            std::string s;
            task >> s;
            if (s.find('q') != std::string::npos) {
                o = false;
            }
            if (s.find('r') != std::string::npos) {
                r = true;
            }
            if (static_cast<int>(!o) + static_cast<int>(r) != s.size()) {
                std::cout << err_msg << std::endl;
                continue;
            }
        }
        if (!task.eof()) {
            task >> amount;
            if (o) {
                std::cout << err_msg << std::endl;
                continue;
            }
        }

        std::string rs = r ? "r" : "";
        std::string os = o ? "" : "q";
        std::string ks = std::to_string(k);
        std::filesystem::path filepath = std::string(os + "data/dim" + ks + rs + "/" + ks + rs + "_" + std::to_string(v) + ".csv");
        bool filepathExists = std::filesystem::is_directory(filepath.parent_path());
        if (!filepathExists) {
            std::filesystem::create_directory(filepath.parent_path());
        }

        std::ofstream out(filepath);
        std::string sep = ",";
        out << "Vertices,Gen set,Diameter,Average distance,BW,Connections" << std::endl;

        LOG_DURATION("C(" + std::to_string(v) + ", " + std::to_string(k) + ")");
        Search s(v, k, r, o, amount);
        s.search();
        auto res = s.optimal();
        sort(res.begin(), res.end());

        for (const auto &item: res) {
            out << item.nodes() << sep
                << item.generatrix_set() << sep
                << +item.diameter() << sep
                << item.average_distance() << sep
                << -item.bisection_width() << sep
                << item.connections()
                << std::endl;
        }
        out.close();
        std::cout << save_msg << filepath << std::endl;
    }

    return 0;
}
