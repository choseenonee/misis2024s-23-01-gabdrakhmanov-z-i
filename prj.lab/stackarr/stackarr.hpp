#ifndef STACK
#define STACK

#include "complex/complex.hpp"
#include <cstddef>

class StackArr {
public:
    StackArr() = default;
    StackArr(const StackArr& rhs);

    StackArr& operator=(const StackArr& rhs);

    void Push(Complex& rhs);
    void Pop() noexcept;
    Complex& Top();
    bool IsEmpty() noexcept;

    ~StackArr() = default;
private:
//    текущий индекс - индекс последнего внесённого элемента (НЕ следующего)
    int current_index = -1;
    std::ptrdiff_t capacity = 0;
    Complex* data_ = nullptr;
};

#endif //STACK
