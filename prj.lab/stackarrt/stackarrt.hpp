#ifndef STACKARRT1
#define STACKARRT1

#include <stdexcept>
#include <cstddef>

template<class T>
class StackArrT {
public:
    StackArrT() = default;
    StackArrT(StackArrT&& rhs) noexcept;
    StackArrT(const StackArrT& rhs);

    StackArrT& operator=(StackArrT&& rhs) noexcept;
    StackArrT& operator=(const StackArrT& rhs);

    void Push(const T& rhs);
    void Pop() noexcept;
    T& Top();

    const T& Top() const;

    void Clear() noexcept;

    bool IsEmpty() const noexcept;

    ~StackArrT();
private:
//    текущий индекс - индекс последнего внесённого элемента (НЕ следующего)
    int current_index = -1;
    std::ptrdiff_t capacity = 0;
    T* data_ = nullptr;
};

template<class T>
StackArrT<T>::StackArrT(const StackArrT& rhs)
        : current_index(rhs.current_index), capacity(rhs.capacity) {
    data_ = new T[capacity];
    for (std::ptrdiff_t i = 0; i < capacity; i++) {
        data_[i] = rhs.data_[i];
    }
}

template<class T>
StackArrT<T>::StackArrT(StackArrT&& rhs) noexcept
        : current_index(rhs.current_index), capacity(rhs.capacity), data_(rhs.data_)
{
    rhs.current_index = -1;
    rhs.capacity = 0;
    rhs.data_ = nullptr;
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(StackArrT&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(current_index, rhs.current_index);
        std::swap(capacity, rhs.capacity);
        std::swap(data_, rhs.data_);
    }

    return *this;
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT& rhs) {
    if (rhs.IsEmpty()) {
        Clear();
    }
    if (capacity < rhs.capacity) {
        capacity = rhs.capacity;
        delete[] data_;
        data_ = new T[capacity];
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

template<class T>
void StackArrT<T>::Push(const T& rhs) {
    if (current_index + 1 < capacity && data_ != nullptr) {
        data_[current_index + 1] = rhs;
    } else {
        T* data = new T[(capacity + 1) * 2];
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

template<class T>
void StackArrT<T>::Pop() noexcept {
    if (!IsEmpty()) {
        data_[current_index] = T();
        if (current_index > -1) {
            current_index--;
        }
    }
}

template<class T>
T& StackArrT<T>::Top() {
    if (IsEmpty()) {
        throw std::logic_error("StackArrT is empty");
    }

    return data_[current_index];
}

template<class T>
const T& StackArrT<T>::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("StackArrT is empty");
    }
    return data_[current_index];
}

template<class T>
bool StackArrT<T>::IsEmpty() const noexcept {
    return current_index == -1;
}

template<class T>
void StackArrT<T>::Clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    capacity = 0;
    current_index = -1;
}

template<class T>
StackArrT<T>::~StackArrT() {
    delete[] data_;
}

#endif //STACKARRT1