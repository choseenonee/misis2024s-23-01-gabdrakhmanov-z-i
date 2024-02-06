#ifndef STACK
#define STACK

#include "complex/complex.hpp"
#include <cstddef>

class Stack {
public:
    Stack() = default;
    Stack(const Stack& rhs);

    Stack& operator=(const Stack& rhs);

    void Push(Complex& rhs);
    void Pop() noexcept;
    Complex& Top();
    bool IsEmpty() noexcept;

    ~Stack() = default;
private:
//    текущий индекс - индекс последнего внесённого элемента (НЕ следующего)
    int current_index = -1;
    std::ptrdiff_t capacity = 0;
    Complex* data_ = nullptr;
};

#endif //STACK
