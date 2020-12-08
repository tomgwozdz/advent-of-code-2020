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

    int mutationPc = 0;
    bool done = false;

    while (!done) {
        acc = 0;
        int pc = 0;

        for (auto & instruction : instructions) {
            instruction.visited = false;
        }

        while (pc >= 0 && pc < instructions.size() && instructions[pc].visited == false) {
            instructions[pc].visited = true;

            std::string instruction = instructions[pc].instruction;
            if (pc == mutationPc) {
                if (instruction == "nop") {
                    instruction = "jmp";
                } else if (instruction == "jmp") {
                    instruction = "nop";
                }
            }

            if (instruction == "nop") {
                pc++;
            } else if (instruction == "acc") {
                acc += instructions[pc].parameter;
                pc++;
            } else if (instruction == "jmp") {
                pc += instructions[pc].parameter;
            }
        }

        if (pc == instructions.size()) {
            done = true;
        } else {
            mutationPc++;
        }
    }

    std::cout << acc << std::endl;
}
