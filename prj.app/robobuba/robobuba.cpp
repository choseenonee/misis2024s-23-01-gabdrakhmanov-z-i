#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define DEBUG false

//todo: структуру данных команды и тащим ссылку на неё внутрь любой команды через менеджера

struct CmdData;

class Command {
public:
    virtual std::unique_ptr<Command> Create(std::string line) = 0;
    virtual void Do(CmdData& data) {};
    virtual bool IsSavebale() {return false;};
};

struct CmdData {
    std::ofstream& outputFile;
    std::vector<int> buffer;
    int cursor;
    std::vector<std::unique_ptr<Command>> parsed_commands;
};

class Left : public Command {
public:
    Left() = default;
    Left(int val) : val(val) {};

    std::unique_ptr<Command> Create(std::string line) override final {
        std::istringstream ss_line(line);
        std::string cmd;
        ss_line >> cmd >> val;
        if (cmd == "LEFT") {
            return std::make_unique<Left>(Left(val));
        }
        return nullptr;
    };

    virtual void Do(CmdData& data) final {
        data.cursor = std::abs(data.cursor - val) % int(data.buffer.size());
    };

    virtual bool IsSavebale() final {return true;};

private:
    int val = 0;
};

class Right : public Command {
public:
    Right() = default;
    Right(int val) : val(val) {};

    virtual std::unique_ptr<Command> Create(std::string line) final {
        std::istringstream ss_line(line);
        std::string cmd;
        ss_line >> cmd >> val;
        if (cmd == "RIGHT") {
            return std::make_unique<Right>(Right(val));
        }
        return nullptr;
    };

    virtual void Do(CmdData& data) final {
        data.cursor = std::abs(data.cursor + val) % int(data.buffer.size());
    };

    virtual bool IsSavebale() final {return true;};
private:
    int val = 0;
};

class Add : public Command {
public:
    Add() = default;
    Add(int val) : val(val) {};

    virtual std::unique_ptr<Command> Create(std::string line) final {
        std::istringstream ss_line(line);
        std::string cmd;
        ss_line >> cmd >> val;
        if (cmd == "ADD") {
            return std::make_unique<Add>(Add(val));
        }
        return nullptr;
    };

    virtual void Do(CmdData& data) final {
        data.buffer[data.cursor] += val;
    };

    virtual bool IsSavebale() final {return true;};
private:
    int val = 0;
};

class Sub : public Command {
public:
    Sub() = default;
    Sub(int val) : val(val) {};

    virtual std::unique_ptr<Command> Create(std::string line) final {
        std::istringstream ss_line(line);
        std::string cmd;
        ss_line >> cmd >> val;
        if (cmd == "SUB") {
            return std::make_unique<Sub>(Sub(val));
        }
        return nullptr;
    };

    virtual void Do(CmdData& data) final {
        data.buffer[data.cursor] -= val;
    };

    virtual bool IsSavebale() final {return true;};
private:
    int val = 0;
};

class Go : public Command {
public:
    Go() = default;
    Go(int val) : val(val) {};

    virtual std::unique_ptr<Command> Create(std::string line) final {
        std::istringstream ss_line(line);
        std::string cmd;
        ss_line >> cmd >> val;
        if (cmd == "GO") {
            return std::make_unique<Go>(Go(val));
        }
        return nullptr;
    };

    virtual void Do(CmdData& data) final {
        data.cursor = 0;
        data.buffer = std::vector<int>(val);

        for (auto& i : data.parsed_commands) {
            i->Do(data);
            if (DEBUG) {
                print(data.buffer, data.cursor);
            }
        }
        data.outputFile << data.buffer[data.cursor] << std::endl;
    };

    virtual bool IsSavebale() final {return false;};
private:
    int val;

    void print(std::vector<int>& buf, int cursor) {
        std::cout << "cursor: " << cursor << std::endl;
        for (int i : buf) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    };
};

class Rev : public Command {
public:
    Rev() = default;
    Rev(int val) : val(val) {};

    virtual std::unique_ptr<Command> Create(std::string line) final {
        std::istringstream ss_line(line);
        std::string cmd;
        ss_line >> cmd >> val;
        if (cmd == "REV") {
            return std::make_unique<Rev>(Rev(val));
        }
        return nullptr;
    };

    virtual void Do(CmdData& data) final {
        for (int i = 0; i < val; i++) {
            data.parsed_commands.pop_back();
        }
    };

    virtual bool IsSavebale() final {return false;};
private:
    int val;
};

class CmdManager {
public:
    CmdManager() {
        known_commands.push_back(std::make_unique<Left>(Left()));
        known_commands.push_back(std::make_unique<Right>(Right()));
        known_commands.push_back(std::make_unique<Add>(Add()));
        known_commands.push_back(std::make_unique<Sub>(Sub()));
        known_commands.push_back(std::make_unique<Go>(Go()));
        known_commands.push_back(std::make_unique<Rev>(Rev()));
    }
    void ParseFile(std::ifstream& inputFile, std::ofstream& outputFile) {
        std::string line;

        CmdData data = {outputFile, std::vector<int>(0), 0, std::vector<std::unique_ptr<Command>>(0)};

        while (std::getline(inputFile, line)) {
            for (auto& i : known_commands) {
                auto cmd_pointer = i->Create(line);
                if (cmd_pointer != nullptr) {
                    if (cmd_pointer->IsSavebale()) {
                        data.parsed_commands.emplace_back(std::move(cmd_pointer));
                    } else {
                        cmd_pointer->Do(data);
                    }
                }
            }
        }
    }
private:
    std::vector<std::unique_ptr<Command>> known_commands;
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

    CmdManager buba;
    buba.ParseFile(inputFile, outputFile);
}
