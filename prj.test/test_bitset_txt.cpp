#include <bitset/bitset.hpp>
#include <sstream>
#include <fstream>

void WriteBS(BitSet& bs) {
    std::ofstream myfile;
    myfile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.test/binary");
    bs.WriteBinary(myfile);
    myfile.close();

    myfile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.test/bitset.txt");
    bs.WriteTxt(myfile);
    myfile.close();
}

void ReadBS(BitSet& bs) {
    BitSet readed_bs;
    std::ifstream myfile;
    myfile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.test/binary_bilikto");
    readed_bs.ReadBinary(myfile);
    if (readed_bs != bs) {
        std::cout << ("binary read error");
    }

    myfile.close();

    myfile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.test/bitset.txt");
    readed_bs.ReadTxt(myfile);
    if (readed_bs != bs) {
        std::cout << ("txt read error");
    }
    myfile.close();
}

int main() {
    BitSet bs(66);
    bs.Set(1, true);
    bs.Set(33, true);
    bs.Set(60, true);

    WriteBS(bs);

    ReadBS(bs);

    std::cout << "success!";

    return 0;
}