#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

struct Instruction {
    std::string instruction;
    int parameter;
    bool visited;

    Instruction(std::string instruction, int parameter)
        : instruction(std::move(instruction)), parameter(parameter), visited(false)
    {}
};

int main() {
    std::ifstream file("data/day8.input");
    if (!file.is_open()) {
        std::cerr << "Couldn't open input file" << std::endl;
        return -1;
    }

    std::string line;
    std::vector<Instruction> instructions;

    while (std::getline(file, line)) {
        std::regex extract("^(\\w+) ([+-]?\\d+)$");
        std::smatch extractResult;
        if (std::regex_match(line, extractResult, extract)) {
            std::string instruction = extractResult[1];
            int parameter = std::stoi(extractResult[2]);

            instructions.emplace_back(instruction, parameter);
        }
    }

    int acc = 0;
    int pc = 0;

    while (instructions[pc].visited == false) {
        instructions[pc].visited = true;

        if (instructions[pc].instruction == "nop") {
            pc++;
        } else if (instructions[pc].instruction == "acc") {
            acc += instructions[pc].parameter;
            pc++;
        } else if (instructions[pc].instruction == "jmp") {
            pc += instructions[pc].parameter;
        }
    }

    std::cout << acc << std::endl;
}
