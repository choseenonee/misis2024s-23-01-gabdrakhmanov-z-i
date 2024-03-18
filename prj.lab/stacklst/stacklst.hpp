#ifndef STACKLST
#define STACKLST

#include "complex/complex.hpp"

class StackLst {
public:
    StackLst() = default;
    StackLst(StackLst&& rhs) noexcept;
    StackLst(const StackLst& rhs);

    StackLst& operator=(StackLst&& rhs) noexcept;
    StackLst& operator=(const StackLst& rhs) noexcept;

    void Push(const Complex& rhs);

    void Pop() noexcept;

    Complex& Top();

    const Complex& Top() const;

    void Clear() noexcept;

    bool IsEmpty() const noexcept;

    ~StackLst();
private:
    struct Node {
        Complex value;
        Node* next_node = nullptr;
    };

    Node* findLast() noexcept;

    Node* head_ = nullptr;
//    it was a mistake...
//    Node* first_ = nullptr;
//    Node* last_ = nullptr;
};

#endif //STACKLST