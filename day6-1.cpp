#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int main() {
    std::ifstream file("data/day6.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    int totalAnswers = 0;
    std::unordered_set<char> answers;
    std::string line;

    while (std::getline(file, line)) {
        for (char &c : line) {
            if (isalpha(c)) {
                answers.insert(c);
            }
        }

        if (line == "" || file.eof()) {
            totalAnswers += answers.size();
            answers.clear();
        }
    }

    std::cout << totalAnswers << std::endl;
}
