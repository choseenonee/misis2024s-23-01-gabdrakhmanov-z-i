#include "stackarr/stackarr.hpp"

StackArr::StackArr(const StackArr& rhs)
        : current_index(rhs.current_index), capacity(rhs.capacity) {
    data_ = new Complex[capacity];
    for (std::ptrdiff_t i = 0; i < capacity; i++) {
        data_[i] = rhs.data_[i];
    }
}

StackArr::StackArr(StackArr&& rhs) noexcept
        : current_index(rhs.current_index), capacity(rhs.capacity), data_(rhs.data_)
{
    rhs.current_index = -1;
    rhs.capacity = 0;
    rhs.data_ = nullptr;
}

StackArr& StackArr::operator=(StackArr&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(current_index, rhs.current_index);
        std::swap(capacity, rhs.capacity);
        std::swap(data_, rhs.data_);
    }

    return *this;
}

StackArr& StackArr::operator=(const StackArr& rhs) {
    if (capacity < rhs.capacity) {
        capacity = rhs.capacity;
        delete[] data_;
        data_ = new Complex[capacity];
        for (std::ptrdiff_t i = 0; i < capacity; i++) {
            data_[i] = rhs.data_[i];
        }
    } else {
//        ошибка, теряю контроль над capacity - rhs.capacity элементами
//        capacity = rhs.capacity;
        for (std::ptrdiff_t i = 0; i < rhs.capacity; i++) {
            data_[i] = rhs.data_[i];
        }
    }
    current_index = rhs.current_index;

    return *this;
}

void StackArr::Push(const Complex& rhs) {
    if (current_index + 1 < capacity && data_ != nullptr) {
        data_[current_index + 1] = rhs;
    } else {
        Complex* data = new Complex[(capacity + 1) * 2];
        if (data_ != nullptr) {
            for (std::ptrdiff_t i = 0; i < capacity; i++) {
                data[i] = data_[i];
            }
            delete[] data_;
        }
        data_ = data;
        capacity = (capacity + 1) * 2;
        data_[current_index + 1] = rhs;
    }
    current_index++;
}

void StackArr::Pop() noexcept {
    if (!IsEmpty()) {
        data_[current_index] = Complex();
        if (current_index > -1) {
            current_index--;
        }
    }
}

Complex& StackArr::Top() {
    if (IsEmpty()) {
        throw std::logic_error("StackArr is empty");
    }

    return data_[current_index];
}

const Complex& StackArr::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("StackArr is empty");
    }
    return data_[current_index];
}

bool StackArr::IsEmpty() const noexcept {
    return current_index == -1;
}

void StackArr::Clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    capacity = 0;
    current_index = -1;
}

StackArr::~StackArr() {
    delete[] data_;
}