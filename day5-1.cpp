#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("data/day5.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    int maxSeatNumber = 0;

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

        maxSeatNumber = (seatNumber > maxSeatNumber) ? seatNumber : maxSeatNumber;
    }

    std::cout << maxSeatNumber << std::endl;
}
