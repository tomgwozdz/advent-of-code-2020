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

    std::sort(data.begin(), data.end());

    for (int i = 0; i < data.size(); ++i) {
        value = data[i];
        int otherValue = 2020 - value;

        if (std::binary_search(data.begin(), data.end(), otherValue)) {
            std::cout << value << " + " << otherValue << " = 2020, " << value << " + " << otherValue << " = " << (value * otherValue) << std::endl;
        }
    }

    return 0;
}
