#ifndef MISIS2024S_23_01_GABDRAKHMANOV_Z_I_BITSET_H
#define MISIS2024S_23_01_GABDRAKHMANOV_Z_I_BITSET_H

#include <vector>
#include <cstdint>
#include <iostream>

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

    class BitAccessor {
    public:
        BitAccessor() = delete;
        BitAccessor(BitSet& bst, const std::int32_t idx) noexcept : bst_(bst), idx_(idx) {}
        ~BitAccessor() = default;
        BitAccessor(const BitAccessor&) = delete;
        BitAccessor(BitAccessor&&) noexcept = default;
        BitAccessor& operator=(const BitAccessor&) = delete;
        BitAccessor& operator=(BitAccessor&&) noexcept = default;
        BitAccessor& operator=(const bool v) { bst_.Set(idx_, v); return *this; }
        operator bool() const { return bst_.Get(idx_); }
    private:
        BitSet& bst_;
        const std::int32_t idx_ = -1;
    };

    BitAccessor operator[](const int32_t rhs);

    BitSet operator~();

    ~BitSet() = default;

    std::ostream& WriteTxt(std::ostream& rhs);
    std::ostream& WriteBinary(std::ostream& rhs) const noexcept;
    std::istream& ReadTxt(std::istream& rhs);
    std::istream& ReadBinary(std::istream& rhs) noexcept;

private:
    char start_mark_ = 's';
    char end_mark_ = 'f';

    std::ostream& writeBinaryData(std::ostream& rhs) const noexcept;

    std::vector<uint32_t> data_ = std::vector<uint32_t>();
    int32_t size_ = 0;
};

inline std::ostream& operator<<(std::ostream& ostrm, const BitSet& rhs)
{
    return rhs.WriteBinary(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, BitSet& rhs)
{
    return rhs.ReadBinary(istrm);
}

BitSet operator&(const BitSet& lhs, const BitSet& rhs);

BitSet operator|(const BitSet& lhs, const BitSet& rhs);

BitSet operator^(const BitSet& lhs, const BitSet& rhs);

#endif //MISIS2024S_23_01_GABDRAKHMANOV_Z_I_BITSET_H
