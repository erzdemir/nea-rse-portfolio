// tape_audit — C++ Project 3
//
// Job mapping
//   Consistency of business logic and system behaviour.
//   Frameworks for collection and management of nuclear physics data.
//
// A tape without MAT/MF/MT/T is not an input. It is an incident.
// In production this guard sits in front of NJOY or FRENDY.

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct TapeCard {
    std::string material;
    int mf;
    int mt;
    double temperature_k;
};

std::string business_key(const TapeCard& card) {
    std::ostringstream os;
    os << card.material << "|MF=" << card.mf << "|MT=" << card.mt
       << "|T=" << card.temperature_k;
    return os.str();
}

std::vector<TapeCard> parse_tape(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open tape: " + path);
    const std::regex card_re(
        R"(^MAT=(\S+)\s+MF=(\d+)\s+MT=(\d+)\s+T=([0-9.]+)\s*$)");
    std::vector<TapeCard> cards;
    std::string line;
    std::size_t line_no = 0;
    while (std::getline(in, line)) {
        ++line_no;
        if (line.empty() || line[0] == '#') continue;
        std::smatch m;
        if (!std::regex_match(line, m, card_re)) {
            throw std::runtime_error(
                "line " + std::to_string(line_no) +
                ": missing MAT=/MF=/MT=/T= (refusing to guess identifiers)");
        }
        TapeCard card;
        card.material = m[1].str();
        card.mf = std::stoi(m[2].str());
        card.mt = std::stoi(m[3].str());
        card.temperature_k = std::stod(m[4].str());
        if (card.mf <= 0 || card.mt <= 0 || !(card.temperature_k > 0.0)) {
            throw std::runtime_error("MF, MT and T must be positive");
        }
        cards.push_back(card);
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
            std::cerr << "usage: tape_audit --tape FILE\n";
            return 0;
        }
    }
    if (tape_path.empty()) {
        std::cerr << "usage: tape_audit --tape FILE\n";
        return 2;
    }
    try {
        const auto cards = parse_tape(tape_path);
        std::cout << "source=" << tape_path << "\n"
                  << "n_cards=" << cards.size() << "\n";
        for (const auto& card : cards) {
            std::cout << "key=" << business_key(card) << "\n";
        }
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
}
