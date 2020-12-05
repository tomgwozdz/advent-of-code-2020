#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

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

    for (int i = 0; i < fields.size(); ++i) {
        std::regex extractRegex("^(\\w+):(.*)$");

        std::smatch match;
        if (std::regex_match(fields[i], match, extractRegex)) {
            std::string field = match[1];
            std::string data = match[2];

            if (field == "byr") {
                // byr (Birth Year) - four digits; at least 1920 and at most 2002.
                std::regex byr("^(\\d+)$");
                std::smatch result;
                if (std::regex_match(data, result, byr)) {
                    int year = std::stoi(result[1]);
                    if (year < 1920 || year > 2002) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (field == "iyr") {
                // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
                std::regex byr("^(\\d+)$");
                std::smatch result;
                if (std::regex_match(data, result, byr)) {
                    int year = std::stoi(result[1]);
                    if (year < 2010 || year > 2020) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (field == "eyr") {
                // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
                std::regex byr("^(\\d+)$");
                std::smatch result;
                if (std::regex_match(data, result, byr)) {
                    int year = std::stoi(result[1]);
                    if (year < 2020 || year > 2030) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (field == "hgt") {
                // hgt (Height) - a number followed by either cm or in:
                // If cm, the number must be at least 150 and at most 193.
                // If in, the number must be at least 59 and at most 76.
                std::regex byr("^(\\d+)(cm|in)$");
                std::smatch result;
                if (std::regex_match(data, result, byr)) {
                    int height = std::stoi(result[1]);
                    std::string unit = result[2];
                    if (unit == "cm" && (height < 150 || height > 193)) {
                        return false;
                    } else if (unit == "in" && (height < 59 || height > 76)) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (field == "hcl") {
                // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
                std::regex byr("^#[0-9a-f]{6}$");
                std::smatch result;
                if (!std::regex_match(data, result, byr)) {
                    return false;
                }
            } else if (field == "ecl") {
                // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
                std::regex byr("^(amb|blu|brn|gry|grn|hzl|oth)$");
                std::smatch result;
                if (!std::regex_match(data, result, byr)) {
                    return false;
                }
            } else if (field == "pid") {
                // pid (Passport ID) - a nine-digit number, including leading zeroes.
                std::regex byr("^[0-9]{9}$");
                std::smatch result;
                if (!std::regex_match(data, result, byr)) {
                    return false;
                }
            } else if (field == "cid") {
                // cid (Country ID) - ignored, missing or not.
            } else {
                return false;
            }
        } else {
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
