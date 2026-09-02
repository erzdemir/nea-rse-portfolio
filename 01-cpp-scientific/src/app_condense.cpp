// xs_condense — C++ Project 4
//
// Job mapping
//   Nuclear data processing: pointwise evaluations are not what every
//   application consumes. Group structures are a processed product.
//   At the Data Bank this is NJOY GROUPR / FRENDY work.
//
// This program shows the C++ contract around those codes:
//   declared group bounds, declared averaging law, no silent fill.
// It does not replace NJOY.

#include "nea/xs_table.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Groups {
    std::string label;
    std::vector<double> upper_eV;
};

Groups load_groups(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open group file: " + path);
    Groups g;
    g.label = path;
    std::string line;
    std::size_t n = 0;
    while (std::getline(in, line)) {
        ++n;
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        double e = 0.0;
        if (!(ss >> e)) throw std::runtime_error("bad group bound at line " + std::to_string(n));
        g.upper_eV.push_back(e);
    }
    if (g.upper_eV.size() < 2)
        throw std::invalid_argument("need at least two group bounds");
    for (std::size_t i = 1; i < g.upper_eV.size(); ++i)
        if (!(g.upper_eV[i] > g.upper_eV[i - 1]))
            throw std::invalid_argument("group bounds must increase");
    return g;
}

double lethargy_average(const nea::XsTable& table, double e0, double e1) {
    const int nseg = 8;
    const double u0 = std::log(e0);
    const double u1 = std::log(e1);
    const double du = (u1 - u0) / nseg;
    double acc = 0.0;
    double xs_prev = table.lookup(e0).xs_barn;
    for (int i = 1; i <= nseg; ++i) {
        const double e = std::exp(u0 + du * i);
        const double xs = table.lookup(e).xs_barn;
        acc += 0.5 * (xs_prev + xs) * du;
        xs_prev = xs;
    }
    return acc / (u1 - u0);
}

int main(int argc, char** argv) {
    std::string table_path, groups_path, law_name = "log-log";
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        auto need = [&](const char*) {
            if (i + 1 >= argc) std::exit(2);
            return std::string(argv[++i]);
        };
        if (arg == "--table") table_path = need("--table");
        else if (arg == "--groups") groups_path = need("--groups");
        else if (arg == "--law") law_name = need("--law");
        else if (arg == "--help") {
            std::cerr << "usage: xs_condense --table FILE --groups FILE --law log-log\n";
            return 0;
        }
    }
    if (table_path.empty() || groups_path.empty()) {
        std::cerr << "usage: xs_condense --table FILE --groups FILE --law log-log\n";
        return 2;
    }
    try {
        const auto table = nea::XsTable::from_csv(table_path, nea::interpolation_from_string(law_name));
        const auto groups = load_groups(groups_path);
        std::cout << std::setprecision(8);
        std::cout << "pointwise_n=" << table.size() << "\n"
                  << "energy_eV,xs_barn\n";
        int n_out = 0;
        for (std::size_t i = 1; i < groups.upper_eV.size(); ++i) {
            const double lo = std::max(groups.upper_eV[i - 1], table.e_min());
            const double hi = std::min(groups.upper_eV[i], table.e_max());
            if (!(hi > lo) || !(lo > 0.0)) continue;
            const double xs = lethargy_average(table, lo, hi);
            std::cout << hi << "," << xs << "\n";
            ++n_out;
        }
        if (n_out < 2) throw std::runtime_error("condensation produced fewer than two groups");
        std::cout << "groups_n=" << n_out << "\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
