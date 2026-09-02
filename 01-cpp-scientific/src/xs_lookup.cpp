// Illustrative C++17 kernel for interview discussion.
// Synthetic pointwise cross-section lookup with explicit interpolation law.
// Not a production nuclear-data library.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

enum class Interpolation { LinLin, LogLog };

class XsTable {
public:
    XsTable(std::vector<double> energy_eV,
            std::vector<double> xs_barn,
            Interpolation law)
        : e_(std::move(energy_eV)), xs_(std::move(xs_barn)), law_(law) {
        if (e_.size() < 2 || e_.size() != xs_.size()) {
            throw std::invalid_argument("grid and values must have equal length >= 2");
        }
        for (std::size_t i = 1; i < e_.size(); ++i) {
            if (!(e_[i] > e_[i - 1])) {
                throw std::invalid_argument("energy grid must be strictly increasing");
            }
        }
        if (law_ == Interpolation::LogLog) {
            for (std::size_t i = 0; i < e_.size(); ++i) {
                if (!(e_[i] > 0.0 && xs_[i] > 0.0)) {
                    throw std::invalid_argument("log-log requires strictly positive E and xs");
                }
            }
        }
    }

    double lookup(double energy_eV) const {
        if (energy_eV < e_.front() || energy_eV > e_.back()) {
            throw std::out_of_range("energy outside tabulated range (no silent extrapolation)");
        }
        auto it = std::lower_bound(e_.begin(), e_.end(), energy_eV);
        if (it == e_.begin()) {
            return xs_.front();
        }
        const std::size_t hi = static_cast<std::size_t>(it - e_.begin());
        const std::size_t lo = hi - 1;
        const double e0 = e_[lo], e1 = e_[hi];
        const double x0 = xs_[lo], x1 = xs_[hi];
        if (law_ == Interpolation::LinLin) {
            const double t = (energy_eV - e0) / (e1 - e0);
            return x0 + t * (x1 - x0);
        }
        const double t = std::log(energy_eV / e0) / std::log(e1 / e0);
        return x0 * std::pow(x1 / x0, t);
    }

    std::size_t size() const { return e_.size(); }

private:
    std::vector<double> e_;
    std::vector<double> xs_;
    Interpolation law_;
};

int main() {
    // Synthetic 1/v-like table (not a real evaluation).
    const XsTable table(
        {1.0e-5, 1.0e-2, 1.0, 1.0e3, 1.0e6},
        {200.0, 6.32, 0.632, 0.020, 0.001},
        Interpolation::LogLog);

    const double e = 0.0253;  // thermal
    std::cout << "E = " << e << " eV, xs = " << table.lookup(e)
              << " b, n = " << table.size() << "\n";
    return 0;
}
