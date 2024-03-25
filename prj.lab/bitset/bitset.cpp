#include "bitset.hpp"

BitSet::BitSet(const int32_t size)
        : size_(size)
{
    int k = size / 32;
    if (size%32 != 0) {
        k++;
    }

    for (int i = 0; i < k; i++) {
        data_.push_back(0);
    }
}

BitSet::BitSet(const BitSet& rhs)
        : size_(rhs.size_), data_(rhs.data_)
{
}

BitSet::BitSet(BitSet&& rhs) noexcept {
    std::swap(data_, rhs.data_);
    std::swap(size_, rhs.size_);
}

BitSet& BitSet::operator=(const BitSet& rhs) {
    if (this != &rhs) {
        size_ = rhs.size_;
        data_ = std::vector<uint32_t>(rhs.data_);
    }

    return *this;
}

BitSet& BitSet::operator=(BitSet&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(size_, rhs.size_);
        std::swap(data_, rhs.data_);
    }

    return *this;
}

int32_t BitSet::Size() const noexcept {
    return size_;
}

void BitSet::Resize(const int32_t size) {
    // количество блоков, если больше щас то поп если меньше то пуш

    int k = size / 32;
    if (size%32 != 0) {
        k++;
    }

    while (data_.size() != k) {
        if (data_.size() < k) {
            data_.push_back(0);
        } else {
            data_.pop_back();
        }
    }

    size_ = size;
}

void BitSet::Fill(const bool v) {
    int k = size_ / 32;
    if (size_%32 != 0) {
        k++;
    }
    if (v) {
        for (int i = 0; i < k; i++) {
            data_[i] = ~uint32_t(0);
        }
    } else {
        for (int i = 0; i < k; i++) {
            data_[i] = uint32_t(0);
        }
    }
}

void BitSet::Set(const int32_t index, const bool v) {
    if (index >= size_) {
        throw std::out_of_range("set index cant be more than size");
    }

    int32_t block = index/32;
    if (index%32 != 0 && block != 0) {
        block++;
    }

    int32_t index_in_block = index - block*32;
    if (v) {
        uint32_t mask = 1 << index_in_block;
        data_[block] = data_[block] | mask;
    } else {
        uint32_t mask = ~(1 << index_in_block);
        data_[block] = data_[block] & mask;
    }
}

bool BitSet::Get(const int32_t index) const {
    if (index >= size_) {
        throw std::out_of_range("set index cant be more than size");
    }

    int32_t block = index/32;
    if (index%32 != 0 && block != 0) {
        block++;
    }

    int32_t index_in_block = index - block*32;

    uint32_t mask = (1 << index_in_block);

    mask = data_[block] & mask;
    if (mask != 0) {
        return true;
    }
    return false;
}