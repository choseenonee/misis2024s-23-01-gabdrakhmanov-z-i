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