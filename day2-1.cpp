#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("data/day2.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    int validPasswordCount = 0;

    while (!file.eof()) {
        int low, high;
        char c, dummy;
        std::string password;

        file >> low;

        if (file.eof()) {
            break;
        }

        file >> dummy;
        file >> high;
        file >> c;
        file >> dummy;
        file >> password;

        int validCharCount = 0;
        for (int i = 0; i < password.length(); ++i) {
            if (password[i] == c) {
                validCharCount++;
            }
        }

        if (validCharCount >= low && validCharCount <= high) {
            validPasswordCount++;
        }
    }

    std::cout << "Valid passwords: " << validPasswordCount << std::endl;
}