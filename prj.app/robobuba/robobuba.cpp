#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define DEBUG true

class Command {
public:
    virtual void Do(int& cursor, std::vector<int>& buffer) {};
};

class Left : public Command {
public:
    Left(int val) : val(val) {};

    void Do(int& cursor, std::vector<int>& buffer) final {
        cursor = std::abs(cursor - val) % int(buffer.size());
    };
private:
    int val = 0;
};

class Right : public Command {
public:
    Right(int val) : val(val) {
        val = val;
    };

    void Do(int& cursor, std::vector<int>& buffer) final {
        cursor = std::abs(cursor + val) % int(buffer.size());
    };
private:
    int val = 0;
};

class Add : public Command {
public:
    Add(int val) : val(val) {
        val = val;
    };

    void Do(int& cursor, std::vector<int>& buffer) final {
        buffer[cursor] += val;
    };
private:
    int val = 0;
};

class Sub : public Command {
public:
    Sub(int val) : val(val) {};

    void Do(int& cursor, std::vector<int>& buffer) final {
        buffer[cursor] -= val;
    };
private:
    int val = 0;
};

void print(std::vector<int>& val, int cursor) {
    std::cout << "cursor: " << cursor << std::endl;
    for (int i : val) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
};

void go(std::vector<std::unique_ptr<Command>>& commands, int buf_size, std::ofstream& outputFile) {
    int cursor = 0;
    std::vector<int> buffer(buf_size);
    for (auto& i : commands) {
        i->Do(cursor, buffer);
        if (DEBUG) {
            print(buffer, cursor);
        }
    }

    outputFile << buffer[cursor] << std::endl;
};

int main(int argc, char* argv[]) {
    std::string inputFilePath;
    std::string outputFilePath;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-i" && i + 1 < argc) {
            inputFilePath = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFilePath = argv[++i];
        }
    }

    if (inputFilePath.empty()) {
        std::cout << "no input file provided: " << inputFilePath;
        return 1;
    }
    if (outputFilePath.empty()) {
        std::cout << "no output file provided: " << outputFilePath;
        return 1;
    }

    std::ifstream inputFile;
    inputFile.open(inputFilePath);

    std::ofstream outputFile;
    outputFile.open(outputFilePath);


    std::vector<std::unique_ptr<Command>> commands = {};

    while (true) {
        std::string cmd;
        int val;

        inputFile >> cmd >> val;

        if (cmd == "LEFT") {
            commands.push_back(std::make_unique<Left>(Left(val)));
        } else if (cmd == "RIGHT") {
            commands.push_back(std::make_unique<Right>(Right(val)));
        } else if (cmd == "ADD") {
            commands.push_back(std::make_unique<Add>(Add(val)));
        } else if (cmd == "SUB") {
            commands.push_back(std::make_unique<Sub>(Sub(val)));
        } else if (cmd == "GO") {
            go(commands, val, outputFile);
        } else if (cmd == "REV") {
            for (int i = 0; i < val; i++) {
                commands.pop_back();
            }
        } else {
            std::cout << "WTF??? " << cmd << " " << val;
            break;
        }
    };
}
