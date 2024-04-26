#include <bitset/bitset.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sstream>

TEST_CASE("size ctor, resize, get, set") {
    BitSet bs;

    CHECK_EQ(bs.Size(), 0);

    CHECK_THROWS(bs.Set(1, true));
    CHECK_THROWS(bs.Get(1));

    CHECK_NOTHROW(bs.Resize(10));

    CHECK_NOTHROW(bs.Fill(true));

    CHECK_EQ(bs.Get(9), true);

    CHECK_NOTHROW(bs.Fill(false));

    CHECK_EQ(bs.Get(8), false);

    CHECK_NOTHROW(bs.Set(8, true));
    CHECK_EQ(bs.Get(8), true);
    CHECK_EQ(bs.Get(9), false);

    CHECK_NOTHROW(bs.Set(7, true));

    CHECK_NOTHROW(bs.Resize(8));
    CHECK_EQ(bs.Get(7), true);

    CHECK_NOTHROW(bs.Resize(33));
    CHECK_NOTHROW(bs.Set(32, true));
    CHECK_EQ(bs.Get(32), true);
}

TEST_CASE("math methods") {
    BitSet lhs(10);
    BitSet rhs(11);

    CHECK_THROWS(rhs&lhs);

    rhs.Resize(10);

    CHECK(lhs == rhs);

    lhs.Set(3, true);
    rhs.Set(3, true);
    rhs.Set(9, true);

    rhs&=lhs;

    CHECK_EQ(rhs.Get(9), false);
    CHECK_EQ(rhs.Get(3), true);

    rhs.Set(9, true);

    lhs |= rhs;

    CHECK_EQ(lhs.Get(3), true);
    CHECK_EQ(lhs.Get(9), true);
}

TEST_CASE("ctor") {
    BitSet bitset(8);
    CHECK_EQ(bitset.Size(), 8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, false));
    CHECK_EQ(bitset.Size(), 8);
    CHECK_EQ(bitset.Get(0), 1);
    CHECK_EQ(bitset.Get(1), 0);
    CHECK_EQ(bitset.Get(2), 1);
    CHECK_EQ(bitset.Get(3), 0);
    CHECK_EQ(bitset.Get(4), 1);
    CHECK_EQ(bitset.Get(5), 0);
    CHECK_EQ(bitset.Get(6), 1);
    CHECK_EQ(bitset.Get(7), 0);
}

TEST_CASE("resize test") {
    BitSet bitset(8);
    CHECK_EQ(bitset.Size(), 8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, false));

    bitset.Resize(10);
    CHECK_EQ(bitset.Size(), 10);
    CHECK_EQ(bitset.Get(8), 0);
    CHECK_EQ(bitset.Get(9), 0);

    CHECK_EQ(bitset.Get(0), 1);
    CHECK_EQ(bitset.Get(1), 0);
    CHECK_EQ(bitset.Get(2), 1);
    CHECK_EQ(bitset.Get(3), 0);
    CHECK_EQ(bitset.Get(4), 1);
    CHECK_EQ(bitset.Get(5), 0);
    CHECK_EQ(bitset.Get(6), 1);
    CHECK_EQ(bitset.Get(7), 0);
}

TEST_CASE("clear test") {
    BitSet bitset(8);
    CHECK_EQ(bitset.Size(), 8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, false));
}

TEST_CASE("out of range test") {
    BitSet bitset(8);
    CHECK_EQ(bitset.Size(), 8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, false));

    CHECK_THROWS_AS(bitset.Get(8), std::out_of_range);
    CHECK_THROWS_AS(bitset.Get(-1), std::out_of_range);
    CHECK_THROWS_AS(bitset.Get(32), std::out_of_range);
    CHECK_THROWS_AS(bitset.Set(8, 1), std::out_of_range);
    CHECK_THROWS_AS(bitset.Set(-1, 1), std::out_of_range);
    CHECK_THROWS_AS(bitset.Get(-1), std::out_of_range);
}

TEST_CASE("bit operations test") {
    BitSet bitset(8);
    CHECK_EQ(bitset.Size(), 8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, false));

    BitSet bitset1(8);
    CHECK_EQ(bitset1.Size(), 8);
    bitset1 = ~bitset;
    CHECK_FALSE(bitset1.Get(0) == bitset.Get(0));
    CHECK_FALSE(bitset1.Get(1) == bitset.Get(1));
    CHECK_FALSE(bitset1.Get(2) == bitset.Get(2));
    CHECK_FALSE(bitset1.Get(3) == bitset.Get(3));
    CHECK_FALSE(bitset1.Get(4) == bitset.Get(4));
    CHECK_FALSE(bitset1.Get(5) == bitset.Get(5));
    CHECK_FALSE(bitset1.Get(6) == bitset.Get(6));
    CHECK_FALSE(bitset1.Get(7) == bitset.Get(7));

    BitSet bitset2(8);
    CHECK_EQ(bitset2.Size(), 8);
    CHECK_NOTHROW(bitset2.Set(0, true));
    CHECK_NOTHROW(bitset2.Set(1, true));
    CHECK_NOTHROW(bitset2.Set(2, true));
    CHECK_NOTHROW(bitset2.Set(3, true));
    CHECK_NOTHROW(bitset2.Set(4, true));
    CHECK_NOTHROW(bitset2.Set(5, true));
    CHECK_NOTHROW(bitset2.Set(6, true));
    CHECK_NOTHROW(bitset2.Set(7, true));

    BitSet bitset3(8);
    CHECK_EQ(bitset3.Size(), 8);
    bitset3 = bitset & bitset2;
    CHECK_EQ(bitset3.Get(0), bitset.Get(0));
    CHECK_EQ(bitset3.Get(1), bitset.Get(1));
    CHECK_EQ(bitset3.Get(2), bitset.Get(2));
    CHECK_EQ(bitset3.Get(3), bitset.Get(3));
    CHECK_EQ(bitset3.Get(4), bitset.Get(4));
    CHECK_EQ(bitset3.Get(5), bitset.Get(5));
    CHECK_EQ(bitset3.Get(6), bitset.Get(6));
    CHECK_EQ(bitset3.Get(7), bitset.Get(7));

    BitSet bitset4(8);
    CHECK_EQ(bitset4.Size(), 8);
    bitset4 = bitset | bitset2;
    CHECK_EQ(bitset4.Get(0), 1);
    CHECK_EQ(bitset4.Get(1), 1);
    CHECK_EQ(bitset4.Get(2), 1);
    CHECK_EQ(bitset4.Get(3), 1);
    CHECK_EQ(bitset4.Get(4), 1);
    CHECK_EQ(bitset4.Get(5), 1);
    CHECK_EQ(bitset4.Get(6), 1);
    CHECK_EQ(bitset4.Get(7), 1);

    BitSet bitset5(8);
    CHECK_EQ(bitset5.Size(), 8);
    bitset5 = bitset ^ bitset1;
    CHECK_EQ(bitset5.Get(0), 1);
    CHECK_EQ(bitset5.Get(1), 1);
    CHECK_EQ(bitset5.Get(2), 1);
    CHECK_EQ(bitset5.Get(3), 1);
    CHECK_EQ(bitset5.Get(4), 1);
    CHECK_EQ(bitset5.Get(5), 1);
    CHECK_EQ(bitset5.Get(6), 1);
    CHECK_EQ(bitset5.Get(7), 1);

    bitset2.Resize(7);
    CHECK_THROWS_AS(bitset2.Set(7, 1), std::out_of_range);
    CHECK_THROWS(bitset2 & bitset);
    CHECK_THROWS(bitset2 | bitset);
    CHECK_THROWS(bitset2 ^ bitset);
    CHECK_FALSE(bitset2 == bitset);
    CHECK(bitset2 != bitset);
}

TEST_CASE("comparison test") {
    BitSet bitset(8);
    CHECK_EQ(bitset.Size(), 8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, true));

    BitSet bitset1(8);
    CHECK_EQ(bitset1.Size(), 8);
    CHECK_NOTHROW(bitset1.Set(0, true));
    CHECK_NOTHROW(bitset1.Set(1, false));
    CHECK_NOTHROW(bitset1.Set(2, true));
    CHECK_NOTHROW(bitset1.Set(3, false));
    CHECK_NOTHROW(bitset1.Set(4, true));
    CHECK_NOTHROW(bitset1.Set(5, false));
    CHECK_NOTHROW(bitset1.Set(6, true));
    CHECK_NOTHROW(bitset1.Set(7, true));

    CHECK(bitset == bitset1);

//    CHECK_NOTHROW(bitset1.Set(0, false));

    CHECK_NOTHROW(bitset1.Resize(7));
    CHECK_NOTHROW(bitset1.Resize(8));

    CHECK(bitset != bitset1);

    CHECK_NOTHROW(bitset.Set(7, false));

    BitSet bitset2(8);
    CHECK_EQ(bitset2.Size(), 8);
    CHECK_NOTHROW(bitset2.Set(0, true));
    CHECK_NOTHROW(bitset2.Set(1, true));
    CHECK_NOTHROW(bitset2.Set(2, true));
    CHECK_NOTHROW(bitset2.Set(3, true));
    CHECK_NOTHROW(bitset2.Set(4, true));
    CHECK_NOTHROW(bitset2.Set(5, true));
    CHECK_NOTHROW(bitset2.Set(6, true));
    CHECK_NOTHROW(bitset2.Set(7, true));

    CHECK(bitset != bitset2);

    CHECK_NOTHROW(bitset2.Set(1, false));
    CHECK_NOTHROW(bitset2.Set(3, false));
    CHECK_NOTHROW(bitset2.Set(5, false));
    CHECK_NOTHROW(bitset2.Set(7, false));

    CHECK(bitset == bitset2);
}

TEST_CASE("bigger size") {
    BitSet bitset(38);
    CHECK_EQ(bitset.Size(), 38);
    CHECK_NOTHROW(bitset.Set(32, true));
    CHECK_NOTHROW(bitset.Set(33, false));
    CHECK_NOTHROW(bitset.Set(34, true));
    CHECK_NOTHROW(bitset.Set(35, false));
    CHECK_NOTHROW(bitset.Set(36, true));
    CHECK_NOTHROW(bitset.Set(37, false));
    CHECK_EQ(bitset.Get(32), 1);
    CHECK_EQ(bitset.Get(33), 0);
    CHECK_EQ(bitset.Get(34), 1);
    CHECK_EQ(bitset.Get(35), 0);
    CHECK_EQ(bitset.Get(36), 1);
    CHECK_EQ(bitset.Get(37), 0);
}

TEST_CASE("time test") {
    long long diff = 0;

    BitSet bit1(100000);
    for (int i = 0; i < 100000; i++) {
        bit1.Set(i, 1);
    }
    auto start = std::chrono::steady_clock::now();
    BitSet bit2(bit1);
    auto end = std::chrono::steady_clock::now();
    CHECK_EQ(bit2.Get(0), 1);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    BitSet bit3(std::move(bit1));
    end = std::chrono::steady_clock::now();
    CHECK_EQ(bit3.Get(0), 1);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);

    BitSet bit4(100000);
    for (int i = 0; i < 100000; i++) {
        bit4.Set(i, 1);
    }
    BitSet bit5;
    start = std::chrono::steady_clock::now();
    bit5 = bit4;
    end = std::chrono::steady_clock::now();
    CHECK_EQ(bit5.Get(0), 1);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    BitSet bit6 = std::move(bit4);
    end = std::chrono::steady_clock::now();
    CHECK_EQ(bit6.Get(0), 1);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);
}

TEST_CASE("operator[] both") {
    BitSet bs(10);

    CHECK_THROWS(bs[50]);

    bool a = bs[9];

    CHECK_EQ(a, false);

    CHECK_NOTHROW(bs[9] = true);

    CHECK_EQ(a, false);

    a = bs[9];

    CHECK_EQ(a, true);
}

TEST_CASE("operator[] test") {
    BitSet bitset(8);
    CHECK_NOTHROW(bitset.Set(0, true));
    CHECK_NOTHROW(bitset.Set(1, false));
    CHECK_NOTHROW(bitset.Set(2, true));
    CHECK_NOTHROW(bitset.Set(3, false));
    CHECK_NOTHROW(bitset.Set(4, true));
    CHECK_NOTHROW(bitset.Set(5, false));
    CHECK_NOTHROW(bitset.Set(6, true));
    CHECK_NOTHROW(bitset.Set(7, false));

    CHECK_EQ(bitset[0], true);
    CHECK_EQ(bitset[1], false);
    CHECK_EQ(bitset[2], true);
    CHECK_EQ(bitset[3], false);
    CHECK_EQ(bitset[4], true);
    CHECK_EQ(bitset[5], false);
    CHECK_EQ(bitset[6], true);
    CHECK_EQ(bitset[7], false);

    bool temp = false;
    for (int i = 0; i < 8; i++) {
        temp = bitset[i];
        CHECK_EQ(temp, bitset[i]);
    }
}

TEST_CASE("resize зануляет лишнее ") {
    BitSet bs(5);

    bs.Set(4, true);

    bs.Resize(4);
    bs.Resize(5);

    CHECK_EQ(bs.Get(4), false);

    bs.Resize(35);

    bs.Set(34, true);

    CHECK_EQ(bs.Get(34), true);

    bs.Resize(34);
    bs.Resize(35);

    CHECK_EQ(bs.Get(34), false);
}

TEST_CASE("input out binary 1") {
    BitSet bs(10);
    bs.Set(7, true);

    std::stringstream strm;

    strm << bs;

    BitSet bs2{};

    strm >> bs2;

    CHECK(bs == bs2);
}

TEST_CASE("input out binary 2") {
    BitSet bs(33);
    bs.Set(8, true);
    bs.Set(32, true);

    std::stringstream strm;

    strm << bs;

    BitSet bs2{};

    strm >> bs2;

    CHECK(bs == bs2);
}

TEST_CASE("input out binary 3") {
    BitSet bs(66);
    bs.Set(1, true);
    bs.Set(35, true);
    bs.Set(65, true);

    std::stringstream strm;

    strm << bs;

    BitSet bs2{};

    strm >> bs2;

    CHECK(bs == bs2);
}

TEST_CASE("bitset_copy_ctor") {
    BitSet bs_orig;
    const int size = 100;

    bs_orig.Resize(size);

    for (int32_t i = 0; i < size; ++i) {
        bs_orig.Set(i, i % 2);
    }

    BitSet bs_copy(bs_orig);

    CHECK_EQ(bs_orig.Size(), bs_copy.Size());
    for (int32_t i = 0; i < size; ++i) {
        CHECK_EQ(bs_orig.Get(i), bs_copy.Get(i));
    }
}

TEST_CASE("bitset_move_ctor") {
    BitSet bs_orig;
    const int size = 100;

    bs_orig.Resize(size);

    for (int32_t i = 0; i < size; ++i) {
        bs_orig.Set(i, i % 2);
    }

    BitSet bs_copy(std::move(bs_orig));

    CHECK_EQ(size, bs_copy.Size());
    for (int32_t i = 0; i < size; ++i) {
        CHECK_EQ(i % 2, bs_copy.Get(i));
    }
}

TEST_CASE("bitset_size_ctor") {
    const int size = 100;
    BitSet bs_def(size);

    CHECK_EQ(size, bs_def.Size());

    for (int32_t i = 0; i < size; ++i) {
        CHECK_EQ(bs_def.Get(i), 0);
    }
}

TEST_CASE("bitset_op=") {
    BitSet bs_orig;
    const int size_1 = 100;

    bs_orig.Resize(size_1);

    for (int32_t i = 0; i < size_1; ++i) {
        bs_orig.Set(i, i % 2);
    }

    const int size_2 = 5;
    BitSet bs_copy(size_2);

    for (int32_t i = 0; i < size_2; ++i) {
        bs_copy.Set(i, ~(i % 2));
    }

    bs_copy = bs_orig;

    CHECK_EQ(bs_orig.Size(), bs_copy.Size());
    for (int32_t i = 0; i < bs_orig.Size(); ++i) {
        CHECK_EQ(bs_orig.Get(i), bs_copy.Get(i));
    }
}

TEST_CASE("bitset_move_op=") {
    BitSet bs_orig;
    const int size_1 = 100;

    bs_orig.Resize(size_1);

    for (int32_t i = 0; i < size_1; ++i) {
        bs_orig.Set(i, i % 2);
    }

    const int size_2 = 5;
    BitSet bs_copy(size_2);

    for (int32_t i = 0; i < size_2; ++i) {
        bs_copy.Set(i, ~(i % 2));
    }

    bs_copy = std::move(bs_orig);

    CHECK_EQ(size_1, bs_copy.Size());
    for (int32_t i = 0; i < size_1; ++i) {
        CHECK_EQ(i % 2, bs_copy.Get(i));
    }
}

TEST_CASE("bitset_Size") {
    BitSet bs_def;
    const int size = 10;

    bs_def.Resize(size);

    CHECK_EQ(bs_def.Size(), size);
}

TEST_CASE("bitset_Resize") {
    const int size_1 = 45;
    const int size_2 = 70;
    const int size_3 = 3;
    const int size_error = -5;

    BitSet bs_def(size_1);
    for (int i = 0; i < size_1; ++i) {
        bs_def.Set(i, i % 2);
    }

    bs_def.Resize(size_2);
    CHECK_EQ(bs_def.Size(), size_2);
    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_def.Get(i), i % 2);
    }

    bs_def.Resize(size_3);
    CHECK_EQ(bs_def.Size(), size_3);
    for (int i = 0; i < size_3; ++i) {
        CHECK_EQ(bs_def.Get(i), i % 2);
    }

    bs_def.Resize(size_1);
    for (int i = size_3; i < size_1; ++i) {
        CHECK_EQ(bs_def.Get(i), 0);
    }

    CHECK_THROWS(bs_def.Resize(size_error));
}

TEST_CASE("bitset_Set") {
    const int size = 100;
    BitSet bs_def(size);

    for (int i = 31; i < size; ++i) {
        bs_def.Set(i, i % 2);
        CHECK_EQ(bs_def.Get(i), i % 2);
    }

    CHECK_THROWS(bs_def.Set(-1, 0));
    CHECK_THROWS(bs_def.Set(size, 0));
}

TEST_CASE("bitset_Get") {
    const int size = 100;
    BitSet bs_def(size);

    for (int i = 31; i < size; ++i) {
        bs_def.Set(i, i % 2);
        CHECK_EQ(bs_def.Get(i), i % 2);
    }

    CHECK_THROWS(bs_def.Get(-1));
    CHECK_THROWS(bs_def.Get(size));
}

TEST_CASE("bitset_Fill") {
    const int size_1 = 100;
    BitSet bs_def(size_1);

    for (int i = 0; i < size_1; ++i) {
        bs_def.Set(i, i % 2);
    }

    bs_def.Fill(true);

    CHECK_EQ(size_1, bs_def.Size());
    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_def.Get(i), 1);
    }

    bs_def.Fill(false);

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_def.Get(i), 0);
    }

    bs_def.Fill(true);

    const int size_2 = 200;
    bs_def.Resize(size_2);

    for (int i = size_1; i < size_2; ++i) {
        CHECK_EQ(bs_def.Get(i), 0);
    }
}

TEST_CASE("bitset_op~") {
    const int size_1 = 100;
    BitSet bs_def(size_1);
    BitSet bs;

    bs = ~bs_def;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_def.Get(i), 0);
        CHECK_EQ(bs.Get(i), 1);
    }

    const int size_2 = 200;
    bs.Resize(size_2);

    for (int i = size_1; i < size_2; ++i) {
        CHECK_EQ(bs.Get(i), 0);
    }
}

TEST_CASE("bitset_op&") {
    const int size_1 = 100;
    BitSet bs_first(size_1);
    BitSet bs_second(size_1);

    bs_second.Fill(1);

    bs_first = bs_first & bs_second;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }

    bs_first.Fill(1);

    bs_first = bs_first & bs_second;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 1);
    }

    BitSet bs_error(size_1 + 1);
    CHECK_THROWS(bs_first & bs_error);

    const int size_2 = 200;
    bs_first.Resize(size_2);

    for (int i = size_1; i < size_2; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }
}

TEST_CASE("bitset_op|") {
    const int size_1 = 100;
    BitSet bs_first(size_1);
    BitSet bs_second(size_1);

    bs_first = bs_first | bs_second;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }

    bs_second.Fill(1);

    bs_first = bs_first | bs_second;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 1);
    }

    BitSet bs_error(size_1 + 1);
    CHECK_THROWS(bs_first | bs_error);

    const int size_2 = 200;
    bs_first.Resize(size_2);

    for (int i = size_1; i < size_2; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }
}

TEST_CASE("bitset_op^") {
    const int size_1 = 100;
    BitSet bs_first(size_1);
    BitSet bs_second(size_1);

    bs_first = bs_first ^ bs_second;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }

    bs_second.Fill(1);

    bs_first = bs_first ^ bs_second;
    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 1);
    }

    bs_first = bs_first ^ bs_second;

    for (int i = 0; i < size_1; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }

    BitSet bs_error(size_1 + 1);
    CHECK_THROWS(bs_first ^ bs_error);

    bs_first ^= bs_second;

    const int size_2 = 200;
    bs_first.Resize(size_2);

    for (int i = size_1; i < size_2; ++i) {
        CHECK_EQ(bs_first.Get(i), 0);
    }
}

TEST_CASE("bitset_op[]") {
    const int size = 100;
    BitSet bs_first(size);
    BitSet bs_second(size);
    BitSet bs_third(size);
    const int idx = 70;

    bs_first[idx] = true;
    CHECK_EQ(bs_first.Get(idx), true);

    CHECK_THROWS(bs_first[-1]);
    CHECK_THROWS(bs_first[size]);
}

TEST_CASE("bitset_op_bool()") {
    const int size = 100;
    const int idx = 70;
    BitSet bs_def(size);
    bool flag = false;

    if (bs_def[idx]) {
        flag = true;
    }
    else {
        flag = false;
    }

    CHECK_EQ(flag, false);

    CHECK(bs_def[idx] == false);
    CHECK(bs_def[idx] != true);
}

TEST_CASE("bitset_bool_ops") {
    const int size = 100;
    BitSet bs_first(size);
    BitSet bs_second(size);
    BitSet bs_third(size / 2);

    CHECK(bs_first == bs_second);
    CHECK(bs_first != bs_third);

    const int idx = 40;
    bs_first[idx] = true;

    CHECK(bs_first != bs_second);
}