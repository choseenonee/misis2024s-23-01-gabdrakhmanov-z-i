#ifndef QUEUELST
#define QUEUELST

#include "complex/complex.hpp"

class QueueLst {
public:
    QueueLst() = default;
    QueueLst(QueueLst&& rhs) noexcept;

    QueueLst(const QueueLst& rhs);

    QueueLst& operator=(QueueLst&& rhs) noexcept;
    QueueLst& operator=(const QueueLst& rhs) noexcept;

    void Push(const Complex& rhs);

    void Pop() noexcept;

    Complex& Top();

    const Complex& Top() const;

    void Clear() noexcept;

    bool IsEmpty() const noexcept;

    ~QueueLst();
private:
    struct Node {
        Complex value;
        Node* next_node = nullptr;
    };

    Node* first_ = nullptr;
    Node* last_ = nullptr;
};

#endif //QUEUELST
