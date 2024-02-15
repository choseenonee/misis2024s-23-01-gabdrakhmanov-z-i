#ifndef STACKLIST
#define STACKLIST

#include "complex/complex.hpp"

class StackList {
public:
    StackList() = default;
    StackList(const StackList& rhs);

    StackList& operator=(const StackList& rhs) noexcept;

    void Push(const Complex& rhs);
    void Pop() noexcept;
    Complex& Top();

    const Complex& Top() const;

    void Clear() noexcept;

    bool IsEmpty() const noexcept;

    ~StackList();
private:
    struct Node {
        Complex value;
        Node* next_node = nullptr;
    };

    Node* first_ = nullptr;
    Node* last_ = nullptr;
};

#endif //STACKLIST