#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    std::ifstream file("data/day6.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    int totalAnswers = 0;
    int peopleInGroup = 0;
    std::unordered_map<char, int> answers;
    std::string line;

    while (std::getline(file, line)) {
        if (line != "") {
            peopleInGroup++;
        }

        for (char &c : line) {
            if (isalpha(c)) {
                answers[c]++;
            }
        }

        if (line == "" || file.eof()) {
            for (std::pair<const char, int> entry : answers) {
                if (entry.second == peopleInGroup) {
                    totalAnswers++;
                }
            }

            answers.clear();
            peopleInGroup = 0;
        }
    }

    std::cout << totalAnswers << std::endl;
}
