#ifndef QUEUEARR
#define QUEUEARR

#include "complex/complex.hpp"

class QueueArr {
public:
    QueueArr() = default;

    QueueArr(const QueueArr& rhs);

    QueueArr& operator=(const QueueArr& rhs) noexcept;

    void Push(const Complex& rhs);

    void Pop() noexcept;

    Complex& Top();

    const Complex& Top() const;

    void Clear() noexcept;

    int Size() const noexcept;

    bool IsEmpty() const noexcept;

    ~QueueArr();
private:
    int head_ = -1;
    int tail_ = -1;

    int size_ = 0;
    std::ptrdiff_t capacity = 0;

    Complex* data_ = nullptr;
};

#endif //QUEUEARR
