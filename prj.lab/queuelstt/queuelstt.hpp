#ifndef MISIS2024S_23_01_GABDRAKHMANOV_Z_I_QUEUELSTT_H
#define MISIS2024S_23_01_GABDRAKHMANOV_Z_I_QUEUELSTT_H

#include <stdexcept>
#include <cstddef>

template<class T>
class QueueLstT {
public:
    QueueLstT() = default;
    QueueLstT(QueueLstT&& rhs) noexcept;

    QueueLstT(const QueueLstT& rhs);

    QueueLstT& operator=(QueueLstT&& rhs) noexcept;
    QueueLstT& operator=(const QueueLstT& rhs) noexcept;

    void Push(const T& rhs);

    void Pop() noexcept;

    T& Top();

    const T& Top() const;

    void Clear() noexcept;

    bool IsEmpty() const noexcept;

    int Size() const noexcept;

    ~QueueLstT();
private:
    struct Node {
        T value;
        Node* next_node = nullptr;
    };

    Node* first_ = nullptr;
    Node* last_ = nullptr;
};

template<class T>
int QueueLstT<T>::Size() const noexcept {
    int size = 0;

    Node* pointer = first_;
    while (pointer != nullptr) {
        size++;
        pointer = pointer->next_node;
    }

    return size;
}
template<class T>
bool QueueLstT<T>::IsEmpty() const noexcept {
    return last_ == nullptr;
}

template<class T>
void QueueLstT<T>::Push(const T& rhs) {
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

template<class T>
T& QueueLstT<T>::Top() {
    if (!IsEmpty()) {
        return last_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}

template<class T>
const T& QueueLstT<T>::Top() const {
    if (!IsEmpty()) {
        return last_->value;
    } else {
        throw std::logic_error("no elements on stack");
    }
}

template<class T>
void QueueLstT<T>::Pop() noexcept {
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

template<class T>
QueueLstT<T>::QueueLstT(const QueueLstT& rhs) {
    Node* pointer = rhs.first_;
    while (pointer != nullptr) {
        T cmpl = pointer->value;
        Push(cmpl);
        pointer = pointer->next_node;
    }
}

template<class T>
QueueLstT<T>::QueueLstT(QueueLstT&& rhs) noexcept
        : first_(rhs.first_), last_(rhs.last_)
{
    rhs.first_ = nullptr;
    rhs.last_ = nullptr;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(first_, rhs.first_);
        std::swap(last_, rhs.last_);
    }

    return *this;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT& rhs) noexcept {
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

template<class T>
void QueueLstT<T>::Clear() noexcept {
    while (!IsEmpty()) {
        Pop();
    }
}

template<class T>
QueueLstT<T>::~QueueLstT() {
    Clear();
}

#endif //MISIS2024S_23_01_GABDRAKHMANOV_Z_I_QUEUELSTT_H
