#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("data/day3.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::vector<std::string> map;

    while (!file.eof()) {
        std::string row;
        file >> row;
        map.push_back(row);
    }

    int x = 0;
    int y = 0;
    int numTrees = 0;

    while (y + 1 < map.size()) {
        y += 1;
        x = (x + 3) % map[y].length();

        if (map[y][x] == '#') {
            numTrees++;
        }
    }

    std::cout << numTrees << std::endl;
}
