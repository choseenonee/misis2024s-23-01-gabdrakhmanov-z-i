#include <iostream>
#include <vector>
#include <string>


class Command {
public:
    virtual void Do(int& to_modify_cursor, int& to_modify_val, int buf_size) {};
};

class Left : public Command {
public:
    Left(int val) : val(val) {};

    void Do(int& to_modify_cursor, int& to_modify_val, int buf_size) final {
        val--;
        to_modify_cursor = std::abs(to_modify_cursor - val) % buf_size;
    };
private:
    int val = 0;
};

class Right : public Command {
public:
    Right(int val) : val(val) {
        val = val;
    };

    void Do(int& to_modify_cursor, int& to_modify_val, int buf_size) final {
        val--;
        to_modify_cursor = std::abs(to_modify_cursor + val) % buf_size;
    };
private:
    int val = 0;
};

class Add : public Command {
public:
    Add(int val) : val(val) {
        val = val;
    };

    void Do(int& to_modify_cursor, int& to_modify_val, int buf_size) final {
        to_modify_val += val;
    };
private:
    int val = 0;
};

class Sub : public Command {
public:
    Sub(int val) : val(val) {};

    void Do(int& to_modify_cursor, int& to_modify_val, int buf_size) final {
        to_modify_val -= val;
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

int go(std::vector<Command>& commands, int buf_size) {
    int cursor = 0;
    std::vector<int> buffer(buf_size);
    for (auto i : commands) {
        i.Do(cursor, buffer[cursor], buf_size);
        print(buffer, cursor);
    }

    return buffer[cursor];
};

int main() {
    std::vector<Command> commands = {};

    while (true) {
        std::string cmd;
        int val;

        std::cin >> cmd >> val;

        if (cmd == "LEFT") {
            commands.push_back(Left(val));
        } else if (cmd == "RIGHT") {
            commands.push_back(Right(val));
        } else if (cmd == "ADD") {
            commands.push_back(Add(val));
        } else if (cmd == "SUB") {
            commands.push_back(Sub(val));
        } else if (cmd == "GO") {
            go(commands, val);
        } else if (cmd == "REV") {
            for (int i = 0; i < val; i++) {
                commands.pop_back();
            }
        } else {
            std::cout << "WTF??? " << cmd << " " << val;
            break;
        }
    };

//    commands.push_back(Add());
//
//    std::vector<int> a = {1, 2, 3};
//    for (auto i : commands) {
//        i.Do(a[0], 1, 0);
//    }
//
//    std::cout << a[0];
}
