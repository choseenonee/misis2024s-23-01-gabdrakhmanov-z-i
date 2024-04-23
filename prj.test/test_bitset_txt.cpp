#include <bitset/bitset.hpp>
#include <sstream>

int main() {
    BitSet bs(61);

    bs.Set(27, true);

    bs.Set(60, true);

    std::cout << bs;

    BitSet bs2(1);

    std::stringstream strm;

    strm << bs;

    strm >> bs2;

    std::cout << (bs == bs2);
}