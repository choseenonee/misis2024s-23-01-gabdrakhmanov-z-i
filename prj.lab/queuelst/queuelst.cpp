#include "QueueLst/QueueLst.hpp"

int QueueLst::Size() const noexcept {
    int size = 0;

    Node* pointer = first_;
    while (pointer != nullptr) {
        size++;
        pointer = pointer->next_node;
    }

    return size;
}

bool QueueLst::IsEmpty() const noexcept {
    return last_ == nullptr;
}

void QueueLst::Push(const Complex& rhs) {
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

Complex& QueueLst::Top() {
    if (!IsEmpty()) {
        return first_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


const Complex& QueueLst::Top() const {
    if (!IsEmpty()) {
        return first_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}


void QueueLst::Pop() noexcept {
    if (IsEmpty()) {
        return;
    }
    if (first_ == last_) {
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
    } else {
        Node* to_delete = first_;
        first_ = first_->next_node;
        delete to_delete;
    }
}


QueueLst::QueueLst(const QueueLst& rhs) {
    Node* pointer = rhs.first_;
    while (pointer != nullptr) {
        Complex cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
}

QueueLst::QueueLst(QueueLst&& rhs) noexcept
        : first_(rhs.first_), last_(rhs.last_)
{
    rhs.first_ = nullptr;
    rhs.last_ = nullptr;
}

QueueLst& QueueLst::operator=(QueueLst&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(first_, rhs.first_);
        std::swap(last_, rhs.last_);
    }

    return *this;
}

QueueLst& QueueLst::operator=(const QueueLst& rhs) noexcept {
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


void QueueLst::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}


QueueLst::~QueueLst() {
    Clear();
}
