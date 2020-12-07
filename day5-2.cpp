#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("data/day5.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::vector<int> seatNumbers;

    std::string line;
    while (std::getline(file, line)) {
        int seatNumber = 0;
        while (line.length() > 0) {
            char charBit = line[0];
            line.erase(line.begin());

            int bit = charBit == 'B' || charBit == 'R';
            seatNumber <<= 1;
            seatNumber |= bit;
        }

        seatNumbers.push_back(seatNumber);
    }

    std::sort(seatNumbers.begin(), seatNumbers.end());

    for (int i = 0; i < seatNumbers.size() - 1; ++i) {
        if (seatNumbers[i + 1] - seatNumbers[i] == 2) {
            std::cout << seatNumbers[i] + 1 << std::endl;
        }
    }
}
