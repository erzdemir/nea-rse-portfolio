#include "nea/xs_table.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace nea {
namespace {
void validate_grid(const std::vector<double>& e, const std::vector<double>& xs,
                   Interpolation law) {
    if (e.size() < 2 || e.size() != xs.size())
        throw std::invalid_argument("grid and values must have equal length >= 2");
    for (std::size_t i = 1; i < e.size(); ++i)
        if (!(e[i] > e[i - 1]))
            throw std::invalid_argument("energy grid must be strictly increasing");
    if (law == Interpolation::LogLog)
        for (std::size_t i = 0; i < e.size(); ++i)
            if (!(e[i] > 0.0 && xs[i] > 0.0))
                throw std::invalid_argument("log-log requires positive E and xs");
}
double lerp(double x0, double y0, double x1, double y1, double x, Interpolation law) {
    if (law == Interpolation::LinLin) {
        const double t = (x - x0) / (x1 - x0);
        return y0 + t * (y1 - y0);
    }
    const double t = std::log(x / x0) / std::log(x1 / x0);
    return y0 * std::pow(y1 / y0, t);
}
}
const char* to_string(Interpolation law) noexcept {
    return law == Interpolation::LinLin ? "lin-lin" : "log-log";
}
Interpolation interpolation_from_string(const std::string& name) {
    if (name == "lin-lin" || name == "linlin" || name == "LinLin")
        return Interpolation::LinLin;
    if (name == "log-log" || name == "loglog" || name == "LogLog")
        return Interpolation::LogLog;
    throw std::invalid_argument("unknown interpolation law: " + name);
}
XsTable::XsTable(std::vector<double> e, std::vector<double> xs,
                 Interpolation law, std::string label)
    : energy_eV_(std::move(e)), xs_barn_(std::move(xs)), law_(law), label_(std::move(label)) {
    validate_grid(energy_eV_, xs_barn_, law_);
}
XsTable XsTable::from_csv(const std::string& path, Interpolation law) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open table file: " + path);
    std::vector<double> e, xs;
    std::string line;
    std::size_t n = 0;
    while (std::getline(in, line)) {
        ++n;
        if (line.empty() || line[0] == '#') continue;
        for (char& c : line) if (c == ',') c = ' ';
        std::istringstream ss(line);
        double ev = 0.0, v = 0.0;
        if (!(ss >> ev >> v))
            throw std::runtime_error("malformed row at line " + std::to_string(n));
        e.push_back(ev);
        xs.push_back(v);
    }
    return XsTable(std::move(e), std::move(xs), law, path);
}
std::optional<LookupResult> XsTable::interpolate(double energy_eV) const {
    if (energy_eV < energy_eV_.front() || energy_eV > energy_eV_.back())
        return std::nullopt;
    auto it = std::lower_bound(energy_eV_.begin(), energy_eV_.end(), energy_eV);
    if (it == energy_eV_.begin())
        return LookupResult{energy_eV, xs_barn_.front(), law_, 0, 0};
    const auto hi = static_cast<std::size_t>(it - energy_eV_.begin());
    const auto lo = hi - 1;
    const double value = lerp(energy_eV_[lo], xs_barn_[lo], energy_eV_[hi],
                              xs_barn_[hi], energy_eV, law_);
    return LookupResult{energy_eV, value, law_, lo, hi};
}
LookupResult XsTable::lookup(double energy_eV) const {
    auto r = interpolate(energy_eV);
    if (!r)
        throw std::out_of_range("energy outside tabulated range (no silent extrapolation)");
    return *r;
}
std::optional<LookupResult> XsTable::try_lookup(double energy_eV) const {
    return interpolate(energy_eV);
}
}
