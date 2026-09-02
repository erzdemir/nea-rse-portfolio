// process_pipeline — C++ Project 5
//
// Job mapping
//   Exploratory research code AND production software.
//   Integrated pipelines for nuclear physics data.
//
// This program is the production shape:
//   1. read declared identifiers from a tape   (Project 3)
//   2. load the named table                    (Project 1)
//   3. take a thermal lookup                   (Project 1)
//   4. write an audit record another system can store
//
// In production the heavy processor is NJOY or FRENDY inside a pinned
// container. The C++ around it still looks like this file.

#include "nea/xs_table.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct Card {
    std::string material;
    int mf;
    int mt;
    double temperature_k;
    nea::Interpolation law;
    std::string table_file;
};

std::vector<Card> parse_pipeline_tape(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open tape: " + path);
    const std::regex re(
        R"(^MAT=(\S+)\s+MF=(\d+)\s+MT=(\d+)\s+T=([0-9.]+)\s+LAW=(\S+)\s+FILE=(\S+)\s*$)");
    std::vector<Card> cards;
    std::string line;
    std::size_t n = 0;
    while (std::getline(in, line)) {
        ++n;
        if (line.empty() || line[0] == '#') continue;
        std::smatch m;
        if (!std::regex_match(line, m, re)) {
            throw std::runtime_error(
                "line " + std::to_string(n) +
                ": need MAT=/MF=/MT=/T=/LAW=/FILE= (refusing to guess)");
        }
        Card c;
        c.material = m[1].str();
        c.mf = std::stoi(m[2].str());
        c.mt = std::stoi(m[3].str());
        c.temperature_k = std::stod(m[4].str());
        c.law = nea::interpolation_from_string(m[5].str());
        c.table_file = m[6].str();
        cards.push_back(c);
    }
    if (cards.empty()) throw std::runtime_error("tape contains no control cards");
    return cards;
}

int main(int argc, char** argv) {
    std::string tape_path;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--tape") {
            if (i + 1 >= argc) return 2;
            tape_path = argv[++i];
        } else if (arg == "--help") {
            std::cerr << "usage: process_pipeline --tape FILE\n";
            return 0;
        }
    }
    if (tape_path.empty()) {
        std::cerr << "usage: process_pipeline --tape FILE\n";
        return 2;
    }

    try {
        const auto cards = parse_pipeline_tape(tape_path);
        const fs::path tape_dir = fs::path(tape_path).parent_path();
        std::cout << std::setprecision(8);
        std::cout << "{\n  \"tape\": \"" << tape_path << "\",\n  \"products\": [\n";
        for (std::size_t i = 0; i < cards.size(); ++i) {
            const auto& c = cards[i];
            const fs::path table_path = tape_dir / c.table_file;
            const auto table = nea::XsTable::from_csv(table_path.string(), c.law);
            const double thermal = table.lookup(0.0253).xs_barn;
            std::cout << "    {\n"
                      << "      \"key\": \"" << c.material << "|MF=" << c.mf
                      << "|MT=" << c.mt << "|T=" << c.temperature_k << "\",\n"
                      << "      \"file\": \"" << table_path.generic_string() << "\",\n"
                      << "      \"law\": \"" << nea::to_string(c.law) << "\",\n"
                      << "      \"n\": " << table.size() << ",\n"
                      << "      \"thermal_xs_b\": " << thermal << "\n"
                      << "    }" << (i + 1 == cards.size() ? "\n" : ",\n");
        }
        std::cout << "  ]\n}\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
