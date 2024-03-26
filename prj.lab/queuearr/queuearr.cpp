#include "queuearr/queuearr.hpp"

QueueArr::QueueArr(const QueueArr& rhs)
    : capacity(rhs.capacity), size_(rhs.size_), head_(rhs.head_), tail_(rhs.tail_)
{
    data_ = new Complex[rhs.capacity];
    for (std::ptrdiff_t i = 0; i < rhs.size_; i++) {
        data_[i] = rhs.data_[i];
    }
}

bool QueueArr::IsEmpty() const noexcept {
    return size_ == 0;
}

Complex& QueueArr::Top() {
    if (IsEmpty()) {
        throw std::logic_error("no elements to show top");
    }
    return data_[head_];
}

const Complex& QueueArr::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("no elements to show top");
    }
    return data_[head_];
}

void QueueArr::Push(const Complex &rhs) {
    if (head_==-1) {
        head_++;
        if (tail_==-1) {
            tail_++;
            if (data_ == nullptr) {
                capacity = 2;
                data_ = new Complex[capacity];
            }
            data_[tail_] = rhs;
            size_++;
            return;
        }
    }
    if (tail_ > head_) {
        if (tail_ + 1 < capacity) {
            tail_++;
            data_[tail_] = rhs;
        } else {
            if (head_ > 1) {
                tail_ = 0;
                data_[tail_] = rhs;
            } else {
                auto* new_data = new Complex[capacity*2+2];
                for (std::ptrdiff_t i = 0; i < capacity; i++) {
                    new_data[i] = data_[i];
                }
                tail_++;
                new_data[tail_] = rhs;

                delete data_;
                data_ = new_data;

                capacity = capacity*2+2;
            }
        }
    }
    else if (tail_ < head_) {
        if (tail_ + 1 < head_) {
            tail_++;
            data_[tail_] = rhs;
        } else {
            auto* new_data = new Complex[capacity*2+2];
            for (std::ptrdiff_t i = head_; i < capacity; i++) {
                new_data[i-head_] = data_[i];
            }
            for (std::ptrdiff_t i = 0; i <= tail_; i++) {
                new_data[i+head_] = data_[i];
            }
            tail_ = tail_ + head_ + 1;
            new_data[tail_] = rhs;
            capacity = capacity*2+2;

            delete data_;
            data_ = new_data;
        }
    }
    else {
        if (tail_ + 1 < capacity) {
            tail_++;
            data_[tail_] = rhs;
        } else {
            tail_ = 0;
            auto* new_data = new Complex[capacity*2+2];
            if (data_ != nullptr) {
                for (std::ptrdiff_t i = 0; i < capacity; i++) {
                    new_data[i] = data_[i];
                }
                delete data_;
                data_ = new_data;
                capacity = capacity*2+2;
            } else {
                data_ = new_data;
            }
            data_[tail_] = rhs;
        }
    }

    size_++;
}

void QueueArr::Pop() noexcept {
    if (head_ == tail_) {
        head_ = -1;
        tail_ = -1;
    } else {
        head_++;
        if (head_+1 > capacity) {
            head_ = 0;
        }
    }
    if (size_ > 0) {
        size_--;
    }
}

QueueArr::QueueArr(QueueArr&& rhs) noexcept
        : head_(rhs.head_), tail_(rhs.tail_), size_(rhs.size_), capacity(rhs.capacity), data_(rhs.data_)
{
    rhs.head_ = -1;
    rhs.tail_ = -1;
    rhs.size_ = 0;
    rhs.capacity = 0;
    rhs.data_ = nullptr;
}

QueueArr& QueueArr::operator=(QueueArr &&rhs) noexcept {
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    std::swap(size_, rhs.size_);
    std::swap(capacity, rhs.capacity);
    std::swap(data_, rhs.data_);

    return *this;
}

QueueArr& QueueArr::operator=(const QueueArr& rhs) noexcept {
    size_ = rhs.size_;
    head_ = rhs.head_;
    tail_ = rhs.tail_;
    if (capacity < rhs.capacity) {
        delete data_;
        data_ = new Complex[rhs.capacity];
        capacity = rhs.capacity;
    }
    for (std::ptrdiff_t i = 0; i < rhs.size_; i++) {
        data_[i] = rhs.data_[i];
    }

    return *this;
}

void QueueArr::Clear() noexcept {
    size_ = 0;
    head_ = -1;
    tail_ = -1;
    capacity = 0;
    delete data_;
    data_ = nullptr;
}

QueueArr::~QueueArr() {
    Clear();
}

int QueueArr::Size() const noexcept {
    return size_;
}