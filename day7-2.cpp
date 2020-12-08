#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <regex>

struct BagEntry {
    std::string name;
    int count;

    BagEntry(std::string name, int count) : name(std::move(name)), count(count) {}
};

int main() {
    std::ifstream file("data/day7.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::string line;
    std::unordered_map<std::string, std::vector<BagEntry>> bagContains;

    while (std::getline(file, line)) {
        std::regex split("^(.*) bags contain (.*)$");
        std::smatch splitResult;
        if (std::regex_match(line, splitResult, split)) {
            std::string bag = splitResult[1];
            std::string rest = splitResult[2];

            std::regex contain(R"((\d+) (\w+ \w+) bags?)");
            std::regex_iterator containBegin = std::sregex_iterator(rest.begin(), rest.end(), contain);
            std::regex_iterator containEnd = std::sregex_iterator();

            for (std::sregex_iterator i = containBegin; i != containEnd; ++i) {
                std::smatch match = *i;
                int size = std::stoi(match[1]);
                std::string subBag = match[2];

                if (subBag.find("no other bags") == std::string::npos) {
                    bagContains[bag].emplace_back(subBag, size);
                }
            }
        } else {
            std::cout << "Unable to parse: " << line << std::endl;
        }
    }

    std::vector<BagEntry> allBags;
    allBags.insert(allBags.begin(), bagContains["shiny gold"].begin(), bagContains["shiny gold"].end());

    int additionalBags = 0;
    bool madeChanges = true;
    while (madeChanges) {
        madeChanges = false;
        std::vector<BagEntry> newBags;
        for (auto entry : allBags) {
            if (bagContains.find(entry.name) != bagContains.end()) {
                additionalBags += entry.count;
                madeChanges = true;
                for (auto subEntry : bagContains[entry.name]) {
                    newBags.emplace_back(subEntry.name, subEntry.count * entry.count);
                }
            } else {
                newBags.push_back(entry);
            }
        }

        allBags = newBags;
    }

    int numBags = 0;
    for (auto entry : allBags) {
        numBags += entry.count;
    }

    std::cout << numBags + additionalBags << std::endl;
}
