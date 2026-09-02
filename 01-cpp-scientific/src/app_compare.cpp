// xs_compare — C++ Project 2
//
// Job mapping
//   Data analysis software; JANIS-style comparison of two evaluations;
//   consistency of business logic (the tolerance is the rule).
//
// This program reuses Project 1 (XsTable). It does not re-implement lookup.
// It is not JANIS. JANIS is the Data Bank Java tool I have used on JEFF/ENDF/EXFOR.

#include "nea/xs_table.hpp"

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Point {
    double energy_eV;
    double xs_a;
    double xs_b;
    double rel_diff;
};

int main(int argc, char** argv) {
    std::string path_a, path_b, law_a = "log-log", law_b = "log-log";
    double tol = 0.02;
    std::vector<double> energies{0.0253, 1.0, 1.0e3};

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        auto need = [&](const char*) {
            if (i + 1 >= argc) std::exit(2);
            return std::string(argv[++i]);
        };
        if (arg == "--a") path_a = need("--a");
        else if (arg == "--b") path_b = need("--b");
        else if (arg == "--law-a") law_a = need("--law-a");
        else if (arg == "--law-b") law_b = need("--law-b");
        else if (arg == "--tol") tol = std::stod(need("--tol"));
        else if (arg == "--energy") energies.push_back(std::stod(need("--energy")));
        else if (arg == "--help") {
            std::cerr << "usage: xs_compare --a FILE --b FILE --tol REL\n";
            return 0;
        }
    }
    if (path_a.empty() || path_b.empty()) {
        std::cerr << "usage: xs_compare --a FILE --b FILE --tol REL\n";
        return 2;
    }

    try {
        const auto a = nea::XsTable::from_csv(path_a, nea::interpolation_from_string(law_a));
        const auto b = nea::XsTable::from_csv(path_b, nea::interpolation_from_string(law_b));
        double max_abs = 0.0;
        std::vector<Point> points;
        for (double e : energies) {
            const double xa = a.lookup(e).xs_barn;
            const double xb = b.lookup(e).xs_barn;
            if (xa == 0.0) throw std::runtime_error("reference xs is zero");
            const double rel = (xb - xa) / xa;
            max_abs = std::max(max_abs, std::abs(rel));
            points.push_back(Point{e, xa, xb, rel});
        }
        const bool ok = max_abs <= tol;
        std::cout << std::setprecision(6);
        std::cout << "a=" << a.label() << "\n"
                  << "b=" << b.label() << "\n"
                  << "tolerance=" << tol << "\n"
                  << "max_abs_rel_diff=" << max_abs << "\n"
                  << "within_tolerance=" << (ok ? "true" : "false") << "\n";
        for (const auto& p : points) {
            std::cout << "E=" << p.energy_eV
                      << " xs_a=" << p.xs_a
                      << " xs_b=" << p.xs_b
                      << " rel_diff=" << p.rel_diff << "\n";
        }
        return ok ? 0 : 1;
    } catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
