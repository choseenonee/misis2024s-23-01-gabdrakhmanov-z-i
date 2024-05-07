#ifndef QueueArrTT1
#define QueueArrTT1

#include <cstddef>
#include <stdexcept>

template<class T>
class QueueArrT {
public:
    QueueArrT() = default;
    QueueArrT(QueueArrT&& rhs) noexcept;

    QueueArrT(const QueueArrT& rhs);

    QueueArrT& operator=(QueueArrT&& rhs) noexcept;
    QueueArrT& operator=(const QueueArrT& rhs) noexcept;

    void Push(const T& rhs);

    void Pop() noexcept;

    T& Top();

    const T& Top() const;

    void Clear() noexcept;

    int Size() const noexcept;

    bool IsEmpty() const noexcept;

    ~QueueArrT();
private:
    int head_ = -1;
    int tail_ = -1;

    int size_ = 0;
    std::ptrdiff_t capacity = 0;

    T* data_ = nullptr;
};

template<class T>
QueueArrT<T>::QueueArrT(const QueueArrT& rhs)
        : capacity(rhs.capacity), size_(rhs.size_), head_(rhs.head_), tail_(rhs.tail_)
{
    data_ = new T[rhs.capacity];
    for (std::ptrdiff_t i = 0; i < rhs.size_; i++) {
        data_[i] = rhs.data_[i];
    }
}

template<class T>
bool QueueArrT<T>::IsEmpty() const noexcept {
    return size_ == 0;
}

template<class T>
T& QueueArrT<T>::Top() {
    if (IsEmpty()) {
        throw std::logic_error("no elements to show top");
    }
    return data_[head_];
}

template<class T>
const T& QueueArrT<T>::Top() const {
    if (IsEmpty()) {
        throw std::logic_error("no elements to show top");
    }
    return data_[head_];
}

template<class T>
void QueueArrT<T>::Push(const T &rhs) {
    if (head_==-1) {
        head_++;
        if (tail_==-1) {
            tail_++;
            if (data_ == nullptr) {
                capacity = 2;
                data_ = new T[capacity];
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
                auto* new_data = new T[capacity*2+2];
                for (std::ptrdiff_t i = 0; i < capacity; i++) {
                    new_data[i] = data_[i];
                }
                tail_++;
                new_data[tail_] = rhs;

                delete[] data_;
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
            auto* new_data = new T[capacity*2+2];
            for (std::ptrdiff_t i = head_; i < capacity; i++) {
                new_data[i-head_] = data_[i];
            }
            for (std::ptrdiff_t i = 0; i <= tail_; i++) {
                new_data[i+head_] = data_[i];
            }
            tail_ = tail_ + head_ + 1;
            new_data[tail_] = rhs;
            capacity = capacity*2+2;

            delete[] data_;
            data_ = new_data;
        }
    }
    else {
        if (tail_ + 1 < capacity) {
            tail_++;
            data_[tail_] = rhs;
        } else {
            tail_ = 0;
            auto* new_data = new T[capacity*2+2];
            if (data_ != nullptr) {
                for (std::ptrdiff_t i = 0; i < capacity; i++) {
                    new_data[i] = data_[i];
                }
                delete[] data_;
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

template<class T>
void QueueArrT<T>::Pop() noexcept {
    if (IsEmpty()) {
        return;
    }
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

template<class T>
QueueArrT<T>::QueueArrT(QueueArrT&& rhs) noexcept
        : head_(rhs.head_), tail_(rhs.tail_), size_(rhs.size_), capacity(rhs.capacity), data_(rhs.data_)
{
    rhs.head_ = -1;
    rhs.tail_ = -1;
    rhs.size_ = 0;
    rhs.capacity = 0;
    rhs.data_ = nullptr;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT &&rhs) noexcept {
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    std::swap(size_, rhs.size_);
    std::swap(capacity, rhs.capacity);
    std::swap(data_, rhs.data_);

    return *this;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT& rhs) noexcept {
    if (this != &rhs) {
        size_ = rhs.size_;
        head_ = rhs.head_;
        tail_ = rhs.tail_;
        if (capacity < rhs.capacity) {
            delete[] data_;
            data_ = new T[rhs.capacity];
            capacity = rhs.capacity;
        }
        for (std::ptrdiff_t i = 0; i < rhs.size_; i++) {
            data_[i] = rhs.data_[i];
        }
    }

    return *this;
}

template<class T>
void QueueArrT<T>::Clear() noexcept {
    size_ = 0;
    head_ = -1;
    tail_ = -1;
    capacity = 0;
    delete[] data_;
    data_ = nullptr;
}

template<class T>
QueueArrT<T>::~QueueArrT() {
    Clear();
}

template<class T>
int QueueArrT<T>::Size() const noexcept {
    return size_;
}

#endif //QueueArrTT1
