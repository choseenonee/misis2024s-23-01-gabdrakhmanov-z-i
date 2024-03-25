#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <bitset/bitset.hpp>

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
    CHECK_NOTHROW(bitset.Set(7, false));

    BitSet bitset1(8);
    CHECK_EQ(bitset1.Size(), 8);
    CHECK_NOTHROW(bitset1.Set(0, true));
    CHECK_NOTHROW(bitset1.Set(1, false));
    CHECK_NOTHROW(bitset1.Set(2, true));
    CHECK_NOTHROW(bitset1.Set(3, false));
    CHECK_NOTHROW(bitset1.Set(4, true));
    CHECK_NOTHROW(bitset1.Set(5, false));
    CHECK_NOTHROW(bitset1.Set(6, true));
    CHECK_NOTHROW(bitset1.Set(7, false));

    CHECK(bitset == bitset1);

    CHECK_NOTHROW(bitset1.Set(0, false));

    CHECK(bitset != bitset1);

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
