#include "stack/stack.hpp"

Stack::Stack(const Stack& rhs)
        : current_index(rhs.current_index), capacity(rhs.capacity) {
    data_ = new Complex[capacity];
    for (std::ptrdiff_t i = 0; i < capacity; i++) {
        data_[i] = rhs.data_[i];
    }
}

Stack& Stack::operator=(const Stack& rhs) {
    if (capacity < rhs.capacity) {
        capacity = rhs.capacity;
        delete[] data_;
        data_ = new Complex[capacity];
        for (std::ptrdiff_t i = 0; i < capacity; i++) {
            data_[i] = rhs.data_[i];
        }
    } else {
        capacity = rhs.capacity;
        for (std::ptrdiff_t i = 0; i < capacity; i++) {
            data_[i] = rhs.data_[i];
        }
    }
    current_index = rhs.current_index;

    return *this;
}

void Stack::Push(Complex& rhs) {
    if (current_index + 1 < capacity && data_ != nullptr) {
        data_[current_index + 1] = rhs;
    } else {
        Complex* data = data_;
        delete[] data_;
        data_ = new Complex[(capacity + 1) * 2];
        for (std::ptrdiff_t i = 0; i < capacity; i++) {
            data_[i] = data[i];
        }
        capacity = (capacity + 1) * 2;
        data_[current_index + 1] = rhs;
    }
    current_index++;
}

void Stack::Pop() noexcept {
    if (!IsEmpty()) {
        data_[current_index] = Complex();
        if (current_index > -1) {
            current_index--;
        }
    }
}

Complex& Stack::Top() {
    if (IsEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return data_[current_index];
}

bool Stack::IsEmpty() noexcept {
    return current_index == -1;
}