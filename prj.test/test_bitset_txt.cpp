#include <bitset/bitset.hpp>
#include <sstream>
#include <fstream>

int main() {
    BitSet bs(66);

    bs.Set(1, true);
    bs.Set(33, true);
    bs.Set(60, true);

    std::ofstream myfile;
    myfile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.test/binary");
    bs.WriteBinary(myfile);
    myfile.close();

    myfile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.test/bitset.txt");
    bs.WriteTxt(myfile);
    myfile.close();

    return 0;
}