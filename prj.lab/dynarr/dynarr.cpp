#include "dynarr.hpp"


DynArr::DynArr(const std::ptrdiff_t size)
        : size_(size), capacity(size)
{
    if (size <= 0) {
        throw std::invalid_argument("array size must be more than 0");
    }
    data_ = new float[size];
    for (std::ptrdiff_t i = 0; i < size; i++) {
        data_[i] = 0.0f;
    }
}


DynArr::DynArr(const DynArr& rhs)
: size_(rhs.Size()), capacity(rhs.Size())
{
    data_ = new float[rhs.Size()];
    for (std::ptrdiff_t i = 0; i < rhs.Size(); i++) {
        data_[i] = rhs[i];
    }
}


void DynArr::Resize(const std::ptrdiff_t size) {
    if (size <= 0) {
        throw std::invalid_argument("size cannot be less than 0");
    }
    if (size > capacity) {
        float* new_data = new float[size]();
        for (std::ptrdiff_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = size;
        capacity = size;
    }
    else {
        size_ = size;
    }
}


std::ptrdiff_t DynArr::Size() const noexcept {
    return size_;
}


std::ptrdiff_t DynArr::Capacity() const noexcept {
    return capacity;
}


float& DynArr::operator[](const std::ptrdiff_t idx) {
    if (idx >= size_ || idx < 0) {
        throw std::out_of_range("Array index is out of range");
    }
    return data_[idx];
}

DynArr::DynArr(DynArr&& rhs) noexcept
        : size_(rhs.size_), capacity(rhs.capacity), data_(rhs.data_)
{
    rhs.size_ = 0;
    rhs.capacity = 0;
    rhs.data_ = nullptr;
}

DynArr& DynArr::operator=(DynArr&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(size_, rhs.size_);
        std::swap(capacity, rhs.capacity);
        std::swap(data_, rhs.data_);
    }

    return *this;
}

DynArr& DynArr::operator=(const DynArr& rhs) {
    if (capacity < rhs.Size()) {
        delete[] data_;
        data_ = new float[rhs.Size()];
        for (std::ptrdiff_t i = 0; i < rhs.Size(); i++) {
            data_[i] = rhs.data_[i];
        }
        size_ = rhs.Size();
        capacity = rhs.Size();
    }
    else {
        size_ = rhs.Size();
        for (std::ptrdiff_t i = 0; i < rhs.Size(); i++) {
            data_[i] = rhs[i];
        }
    }

    return *this;
}


const float& DynArr::operator[](const std::ptrdiff_t idx) const {
    if (idx >= size_ || idx < 0) {
        throw std::out_of_range("Array index is out of range");
    }
    return data_[idx];
}


DynArr::~DynArr() {
    delete[] data_;
}