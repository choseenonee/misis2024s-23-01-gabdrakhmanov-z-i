#ifndef StackLstT1
#define StackLstT1

#include <cstddef>
#include <stdexcept>

template<class T>
class StackLstT {
public:
    StackLstT() = default;
    StackLstT(StackLstT&& rhs) noexcept;
    StackLstT(const StackLstT& rhs);

    StackLstT& operator=(StackLstT&& rhs) noexcept;
    StackLstT& operator=(const StackLstT& rhs) noexcept;

    void Push(const T& rhs);

    void Pop() noexcept;

    T& Top();

    const T& Top() const;

    void Clear() noexcept;

    bool IsEmpty() const noexcept;

    ~StackLstT();
private:
    struct Node {
        T value;
        Node* next_node = nullptr;
    };

    Node* findLast() noexcept;

    Node* head_ = nullptr;
};

template<class T>
StackLstT<T>::StackLstT::Node* StackLstT<T>::StackLstT::findLast() noexcept {
    Node* pointer = head_;
    if (pointer == nullptr) {
        return nullptr;
    }
    while (pointer->next_node != nullptr) {
        pointer = pointer->next_node;
    }
    return pointer;
}

template<class T>
StackLstT<T>::StackLstT(StackLstT&& rhs) noexcept
        : head_(rhs.head_)
{
    rhs.head_ = nullptr;
}

template<class T>
StackLstT<T>& StackLstT<T>::operator=(StackLstT &&rhs) noexcept {
    if (this != &rhs) {
        std::swap(head_, rhs.head_);
    }

    return *this;
}

template<class T>
bool StackLstT<T>::IsEmpty() const noexcept {
    Node* pointer = head_;
    if (pointer == nullptr) {
        return true;
    }
    while (pointer->next_node != nullptr) {
        pointer = pointer->next_node;
    }
    return pointer == nullptr;
}

template<class T>
void StackLstT<T>::Push(const T& rhs) {
    Node* newNodePointer = new Node;

    newNodePointer->value = rhs;
    newNodePointer->next_node = nullptr;

    if (head_ == nullptr) {
        head_ = newNodePointer;
    } else {
        Node* last = findLast();
        last->next_node = newNodePointer;
    }
}

template<class T>
T& StackLstT<T>::Top() {
    if (!IsEmpty()) {
        Node* last = findLast();
        return last->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}

template<class T>
const T& StackLstT<T>::Top() const {
    if (!IsEmpty()) {
        Node* pointer = head_;
        while (pointer->next_node != nullptr) {
            pointer = pointer->next_node;
        }
        return pointer->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}

template<class T>
void StackLstT<T>::Pop() noexcept {
    Node* last = findLast();
    delete last;
    if (head_ == last) {
        head_ = nullptr;
    } else {
        Node* pointer = head_;
        while (true) {
            if (pointer->next_node == last) {
                pointer->next_node = nullptr;
                break;
            }
            pointer = pointer->next_node;
        }
    }
}

template<class T>
StackLstT<T>::StackLstT(const StackLstT& rhs) {
    Node* pointer = rhs.head_;
    while (pointer != nullptr) {
        T cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
}

template<class T>
StackLstT<T>& StackLstT<T>::operator=(const StackLstT& rhs) noexcept {
    if (rhs.IsEmpty()) {
        Clear();
    } else {
        Node* rhs_pointer = rhs.head_;
        Node* lhs_pointer = head_;
        if (lhs_pointer == nullptr) {
            while (rhs_pointer != nullptr) {
                Push(rhs_pointer->value);
                rhs_pointer = rhs_pointer->next_node;
            }
        } else {
            while (rhs_pointer != nullptr) {
                lhs_pointer->value = rhs_pointer->value;
                lhs_pointer = lhs_pointer->next_node;
                rhs_pointer = rhs_pointer->next_node;
                if (lhs_pointer == nullptr) {
                    while (rhs_pointer != nullptr) {
                        Push(rhs_pointer->value);
                        rhs_pointer = rhs_pointer->next_node;
                    }
                }
            }
            if (lhs_pointer != nullptr) {
                Node* last = findLast();
                while (last != lhs_pointer) {
                    Pop();
                    last = findLast();
                }
                Node* refresh_pointer = head_;
                while (refresh_pointer->next_node != lhs_pointer) {
                    refresh_pointer = refresh_pointer->next_node;
                }
                refresh_pointer->next_node = nullptr;
//                last_ = refresh_pointer;
                delete lhs_pointer;
            }
        }
    }
    return *this;
}

template<class T>
void StackLstT<T>::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}

template<class T>
StackLstT<T>::~StackLstT() {
    Clear();
}

#endif //StackLstT