#include "stacklist/stacklist.hpp"


bool StackList::IsEmpty() const noexcept {
    return last_ == nullptr;
}

void StackList::Push(const Complex& rhs) {
    Node* newNodePointer = new Node;

    newNodePointer->value = rhs;
    newNodePointer->next_node = nullptr;

    if (first_ == nullptr) {
        first_ = newNodePointer;
        last_ = newNodePointer;
    } else {
        last_->next_node = newNodePointer;
        last_ = newNodePointer;
    }
}

Complex& StackList::Top() {
    if (!IsEmpty()) {
        return last_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


const Complex& StackList::Top() const {
    if (!IsEmpty()) {
        return last_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


void StackList::Pop() noexcept {
    delete last_;
    if (first_ == last_) {
        first_ = nullptr;
        last_ = nullptr;
    } else {
        Node* pointer = first_;
        while (true) {
            if (pointer->next_node == last_) {
                pointer->next_node = nullptr;
                last_ = pointer;
                break;
            }
            pointer = pointer->next_node;
        }
    }
}


StackList::StackList(const StackList& rhs) {
    Node* pointer = rhs.first_;
    while (pointer != nullptr) {
        Complex cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
}


StackList& StackList::operator=(const StackList& rhs) noexcept {
    Node* pointer = rhs.first_;
    while (pointer != nullptr) {
        Complex cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
    return *this;
}


void StackList::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}


StackList::~StackList() {
    Clear();
}