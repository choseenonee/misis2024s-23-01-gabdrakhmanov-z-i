#include <bitset/bitset.hpp>
#include <sstream>

int main() {
    BitSet bs(61);

    bs.Set(27, true);

    bs.Set(60, true);
    std::cout << bs;
}