#include <iostream>
#include <fstream>
#include <vector>

int countTrees(int xIncrement, int yIncrement, const std::vector<std::string> &map) {
    int x = 0;
    int y = 0;
    int numTrees = 0;

    while (y + yIncrement < map.size()) {
        y += yIncrement;
        x = (x + xIncrement) % map[y].length();

        if (map[y][x] == '#') {
            numTrees++;
        }
    }

    return numTrees;
}

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

    int treeMultiple = countTrees(1, 1, map);
    treeMultiple *= countTrees(3, 1, map);
    treeMultiple *= countTrees(5, 1, map);
    treeMultiple *= countTrees(7, 1, map);
    treeMultiple *= countTrees(1, 2, map);

    std::cout << treeMultiple << std::endl;
}
