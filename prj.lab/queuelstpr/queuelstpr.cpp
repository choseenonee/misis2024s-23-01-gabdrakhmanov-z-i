#include <queuelstpr/queuelstpr.hpp>
#include <iostream>

bool QueueLstPr::IsEmpty() const noexcept {
    return head_ == nullptr;
}

QueueLstPr& QueueLstPr::operator=(const QueueLstPr& rhs) {
    Clear();
    if (!rhs.IsEmpty()) {
        Node* pointer = rhs.head_;
        while (pointer != nullptr) {
            Push(pointer->data);
            pointer = pointer->next_node;
        }
    }
    return *this;
}

QueueLstPr::QueueLstPr(const QueueLstPr& rhs) {
    if (!rhs.IsEmpty()) {
        Node* pointer = rhs.head_;
        while (pointer != nullptr) {
            Push(pointer->data);
            pointer = pointer->next_node;
        }
    }
}

void QueueLstPr::Pop() {
    if (!IsEmpty()) {
        Node* to_delete = head_;
        head_ = head_->next_node;
        delete to_delete;
    } else {
        throw std::logic_error("trying to pop from empty queue");
    }
}

const float& QueueLstPr::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("trying to pop from empty queue");
    }
    return head_->data;
}

float& QueueLstPr::Top() {
    if (IsEmpty()) {
        throw std::logic_error("trying to pop from empty queue");
    }
    return head_->data;
}

void QueueLstPr::Push(const float& rhs) {
    if (head_ == nullptr) {
        Node* new_node = new Node;
        new_node->data = rhs;
        head_ = new_node;
        tail_ = new_node;
    } else if (rhs <= head_->data) {
        Node* new_node = new Node;
        new_node->data = rhs;
        new_node->next_node = head_;
        head_ = new_node;
    } else if (rhs >= tail_->data) {
        Node* new_node = new Node;
        new_node->data = rhs;
        tail_->next_node = new_node;
        tail_ = new_node;
    } else {
        Node* pointer = head_;
        while (pointer != nullptr) {
            if (rhs <= pointer->next_node->data) {
                Node* new_node = new Node;
                new_node->data = rhs;
                new_node->next_node = pointer->next_node;
                pointer->next_node = new_node;
                break;
            }
            pointer = pointer->next_node;
        }
    }
}

void QueueLstPr::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}

QueueLstPr::~QueueLstPr() {
    Clear();
}