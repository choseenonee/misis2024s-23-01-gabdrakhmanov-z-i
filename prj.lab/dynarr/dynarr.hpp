#ifndef DYNARR_HPP
#define DYNARR_HPP

#include <stdexcept>
#include <cstddef>

class DynArr {
public:
    DynArr() = default;
    DynArr(const DynArr&);
    explicit DynArr(const std::ptrdiff_t size);

    DynArr& operator=(const DynArr& rhs);

    void Resize(const std::ptrdiff_t size);

    std::ptrdiff_t Size() const noexcept;
    std::ptrdiff_t Capacity() const noexcept;

    float& operator[](const std::ptrdiff_t idx);
    const float& operator[](const std::ptrdiff_t idx) const;

    ~DynArr();
private:
    std::ptrdiff_t size_ = 0;
    std::ptrdiff_t capacity = 0;
    float* data_ = nullptr;
};

#endif //DYNARR_HPP
