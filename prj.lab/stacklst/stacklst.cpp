#include "stacklst/stacklst.hpp"

StackLst::Node* StackLst::findLast() noexcept {
    Node* pointer = head_;
    if (pointer == nullptr) {
        return nullptr;
    }
    while (pointer->next_node != nullptr) {
        pointer = pointer->next_node;
    }
    return pointer;
}

StackLst::StackLst(StackLst&& rhs) noexcept
        : head_(rhs.head_)
{
    rhs.head_ = nullptr;
}

StackLst& StackLst::operator=(StackLst &&rhs) noexcept {
    if (this != &rhs) {
        std::swap(head_, rhs.head_);
    }

    return *this;
}

bool StackLst::IsEmpty() const noexcept {
    Node* pointer = head_;
    if (pointer == nullptr) {
        return true;
    }
    while (pointer->next_node != nullptr) {
        pointer = pointer->next_node;
    }
    return pointer == nullptr;
}

void StackLst::Push(const Complex& rhs) {
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

Complex& StackLst::Top() {
    if (!IsEmpty()) {
        Node* last = findLast();
        return last->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


const Complex& StackLst::Top() const {
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


void StackLst::Pop() noexcept {
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


StackLst::StackLst(const StackLst& rhs) {
    Node* pointer = rhs.head_;
    while (pointer != nullptr) {
        Complex cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
}


StackLst& StackLst::operator=(const StackLst& rhs) noexcept {
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


void StackLst::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}


StackLst::~StackLst() {
    Clear();
}