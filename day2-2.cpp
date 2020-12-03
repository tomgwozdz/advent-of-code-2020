#include <iostream>
#include <fstream>

// Index is 0 referenced
bool validChar(int index, char c, const std::string &password) {
    if (index < 0 || index >= password.size()) {
        return false;
    }

    return password[index] == c;
}

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
        if (validChar(low - 1, c, password)) {
            validCharCount++;
        }
        if (validChar(high - 1, c, password)) {
            validCharCount++;
        }

        if (validCharCount == 1) {
            validPasswordCount++;
        }
    }

    std::cout << "Valid passwords: " << validPasswordCount << std::endl;
}