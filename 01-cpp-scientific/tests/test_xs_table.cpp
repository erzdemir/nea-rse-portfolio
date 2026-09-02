#include "nea/xs_table.hpp"
#include <cmath>
#include <iostream>
int failures = 0;
void expect(bool ok, const char* w) {
    if (!ok) { std::cerr << "FAIL " << w << "\n"; ++failures; }
    else std::cout << "ok   " << w << "\n";
}
int main() {
    nea::XsTable lin({1.0, 10.0, 100.0}, {1.0, 10.0, 100.0}, nea::Interpolation::LinLin);
    nea::XsTable log({1.0, 10.0, 100.0}, {1.0, 10.0, 100.0}, nea::Interpolation::LogLog);
    expect(std::abs(lin.lookup(55.0).xs_barn - 55.0) < 1e-12, "lin-lin mid");
    expect(std::abs(log.lookup(std::sqrt(10.0)).xs_barn - std::sqrt(10.0)) < 1e-12, "log-log mid");
    bool low = false;
    try { (void)lin.lookup(0.5); } catch (const std::out_of_range&) { low = true; }
    expect(low, "no silent extrapolation");
    bool bad = false;
    try { nea::XsTable({1.0, 0.5}, {1.0, 2.0}, nea::Interpolation::LinLin); }
    catch (const std::invalid_argument&) { bad = true; }
    expect(bad, "reject unsorted grid");
    if (failures) return 1;
    std::cout << "all tests passed\n";
    return 0;
}
