#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <regex>

int main() {
    std::ifstream file("data/day7.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::string line;
    std::unordered_map<std::string, std::vector<std::string>> containedBy;

    while (std::getline(file, line)) {
        std::regex split("^(.*) bags contain (.*)$");
        std::smatch splitResult;
        if (std::regex_match(line, splitResult, split)) {
            std::string bag = splitResult[1];
            std::string rest = splitResult[2];

            std::regex contain(R"(\d+ (\w+ \w+) bags?)");
            std::regex_iterator containBegin = std::sregex_iterator(rest.begin(), rest.end(), contain);
            std::regex_iterator containEnd = std::sregex_iterator();

            for (std::sregex_iterator i = containBegin; i != containEnd; ++i) {
                std::smatch match = *i;
                std::string subBag = match[1];

                if (subBag.find("no other bags") == std::string::npos) {
                    containedBy[subBag].push_back(bag);
                }
            }
        } else {
            std::cout << "Unable to parse: " << line << std::endl;
        }
    }

    std::unordered_set<std::string> goldContainingBags;
    goldContainingBags.insert(containedBy["shiny gold"].begin(), containedBy["shiny gold"].end());

    int lastCount = 0;
    while (lastCount != goldContainingBags.size()) {
        lastCount = goldContainingBags.size();

        std::unordered_set<std::string> newBags;
        for (std::string bag : goldContainingBags) {
            newBags.insert(containedBy[bag].begin(), containedBy[bag].end());
        }

        goldContainingBags.merge(newBags);
    }

    std::cout << goldContainingBags.size() << std::endl;
}
