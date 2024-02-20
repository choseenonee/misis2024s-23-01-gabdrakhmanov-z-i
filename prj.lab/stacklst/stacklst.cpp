#include "stacklst/stacklst.hpp"


bool StackLst::IsEmpty() const noexcept {
    return last_ == nullptr;
}

void StackLst::Push(const Complex& rhs) {
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

Complex& StackLst::Top() {
    if (!IsEmpty()) {
        return last_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


const Complex& StackLst::Top() const {
    if (!IsEmpty()) {
        return last_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


void StackLst::Pop() noexcept {
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


StackLst::StackLst(const StackLst& rhs) {
    Node* pointer = rhs.first_;
    while (pointer != nullptr) {
        Complex cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
}

// TODO: переписать чтобы было без Clear а по умному
StackLst& StackLst::operator=(const StackLst& rhs) noexcept {
    if (rhs.IsEmpty()) {
        Clear();
    } else {
        Node* rhs_pointer = rhs.first_;
        Node* lhs_pointer = first_;
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
                while (last_ != lhs_pointer) {
                    Pop();
                }
                Node* refresh_pointer = first_;
                while (refresh_pointer->next_node != lhs_pointer) {
                    refresh_pointer = refresh_pointer->next_node;
                }
                last_ = refresh_pointer;
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