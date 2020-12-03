#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("data/day1.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::vector<int> data;

    int value;
    while (file >> value) {
        data.push_back(value);
    }

    for (int i = 0; i < data.size(); ++i) {
        for (int j = i; j < data.size(); ++j) {
            for (int k = 0; k < data.size(); ++k) {
                if (data[i] + data[j] + data[k] == 2020) {
                    std::cout << data[i] << " + " << data[j] << " + " << data[k] << " = 2020, " << data[i] << " + " << data[j] << " + " << data[k] << " = " << (data[i] * data[j] * data[k]) << std::endl;
                }
            }
        }
    }

    return 0;
}
