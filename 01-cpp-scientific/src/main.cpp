// xs_lookup — Project 1 CLI
// Job: scientific C++ kernel with an explicit numerical contract.
#include "nea/xs_table.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char** argv) {
    std::string table_path, law_name = "log-log";
    std::vector<double> energies;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto need = [&](const char*) {
            if (i + 1 >= argc) std::exit(2);
            return std::string(argv[++i]);
        };
        if (arg == "--table") table_path = need("--table");
        else if (arg == "--law") law_name = need("--law");
        else if (arg == "--energy") energies.push_back(std::stod(need("--energy")));
        else if (arg == "--help") {
            std::cerr << "usage: xs_lookup --table FILE --law lin-lin|log-log --energy eV\n";
            return 0;
        }
    }
    if (table_path.empty()) return 2;
    try {
        auto table = nea::XsTable::from_csv(table_path, nea::interpolation_from_string(law_name));
        std::cout << std::setprecision(8);
        std::cout << "law=" << nea::to_string(table.law())
                  << " n=" << table.size() << "\n";
        for (double e : energies) {
            auto r = table.lookup(e);
            std::cout << "E=" << r.energy_eV << " xs=" << r.xs_barn << " b\n";
        }
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
