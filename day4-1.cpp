#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string neededFields[] = {
    "byr",
    "iyr",
    "eyr",
    "hgt",
    "hcl",
    "ecl",
    "pid",
//    "cid",
};

bool validatePassport(const std::vector<std::string> &passport) {
    std::vector<std::string> fields;

    for (int i = 0; i < passport.size(); ++i) {
        std::string entry = passport[i];

        size_t space = 0;

        while ((space = entry.find(' ')) != std::string::npos) {
            std::string field = entry.substr(0, space);
            fields.push_back(field);
            entry.erase(0, space + 1);
        }

        if (entry != "") {
            fields.push_back(entry);
        }
    }

    for (int i = 0; i < sizeof(neededFields) / sizeof(neededFields[0]); ++i) {
        bool found = false;
        for (int j = 0; j < fields.size(); ++j) {
            if (fields[j].substr(0, neededFields[i].length()) == neededFields[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    std::ifstream file("data/day4.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::vector<std::string> passport;
    std::string line;

    int numValid = 0;
    while (std::getline(file, line)) {
        if (line == "") {
            if (validatePassport(passport)) {
                numValid++;
            }

            passport.clear();
        }
        else {
            passport.push_back(line);
        }
    }

    if (passport.size() > 0) {
        if (validatePassport(passport)) {
            numValid++;
        }
    }

    std::cout << numValid << std::endl;
}
