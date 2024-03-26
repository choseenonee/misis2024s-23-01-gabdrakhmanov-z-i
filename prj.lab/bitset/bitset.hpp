#ifndef MISIS2024S_23_01_GABDRAKHMANOV_Z_I_BITSET_H
#define MISIS2024S_23_01_GABDRAKHMANOV_Z_I_BITSET_H

#include <vector>
#include <cstdint>

class BitSet {
public:
    BitSet() = default;

    BitSet(const int32_t size);

    BitSet(const BitSet& rhs) = default;

    BitSet(BitSet&& rhs) noexcept;

    BitSet& operator=(const BitSet& rhs) = default;

    BitSet& operator=(BitSet&& rhs) noexcept;

    bool operator==(const BitSet& rhs) const noexcept;

    bool operator!=(const BitSet& rhs) const noexcept;

    int32_t Size() const noexcept;

    void Resize(const int32_t size);

    void Set(const int32_t index, const bool v);

    bool Get(const int32_t index) const;

    void Fill(const bool v);

    BitSet& operator&=(const BitSet& rhs);

    BitSet& operator|=(const BitSet& rhs);

    BitSet& operator^=(const BitSet& rhs);

    bool operator[](const int32_t rhs) const;

    struct BitAccessor {
        BitSet& bst_;
        int32_t index_ = 0;

        BitSet::BitAccessor& operator=(const bool& rhs);
        operator bool() const noexcept;
    };

    BitAccessor operator[](const int32_t rhs);

    BitSet operator~();

    ~BitSet() = default;

private:
    std::vector<uint32_t> data_ = std::vector<uint32_t>();
    int32_t size_ = 0;
};

BitSet operator&(const BitSet& lhs, const BitSet& rhs);

BitSet operator|(const BitSet& lhs, const BitSet& rhs);

BitSet operator^(const BitSet& lhs, const BitSet& rhs);

#endif //MISIS2024S_23_01_GABDRAKHMANOV_Z_I_BITSET_H
