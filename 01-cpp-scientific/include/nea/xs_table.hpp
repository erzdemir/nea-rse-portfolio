#pragma once
#include <cstddef>
#include <optional>
#include <string>
#include <vector>
namespace nea {
enum class Interpolation { LinLin, LogLog };
struct LookupResult {
    double energy_eV;
    double xs_barn;
    Interpolation law;
    std::size_t interval_lo;
    std::size_t interval_hi;
};
class XsTable {
public:
    XsTable(std::vector<double> energy_eV, std::vector<double> xs_barn,
            Interpolation law, std::string label = {});
    static XsTable from_csv(const std::string& path, Interpolation law);
    LookupResult lookup(double energy_eV) const;
    std::optional<LookupResult> try_lookup(double energy_eV) const;
    const std::string& label() const noexcept { return label_; }
    Interpolation law() const noexcept { return law_; }
    std::size_t size() const noexcept { return energy_eV_.size(); }
    double e_min() const noexcept { return energy_eV_.front(); }
    double e_max() const noexcept { return energy_eV_.back(); }
    const std::vector<double>& energy_eV() const noexcept { return energy_eV_; }
    const std::vector<double>& xs_barn() const noexcept { return xs_barn_; }
private:
    std::optional<LookupResult> interpolate(double energy_eV) const;
    std::vector<double> energy_eV_;
    std::vector<double> xs_barn_;
    Interpolation law_;
    std::string label_;
};
const char* to_string(Interpolation law) noexcept;
Interpolation interpolation_from_string(const std::string& name);
}
