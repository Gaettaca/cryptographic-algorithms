#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include "LFSR.h"


void FindInitial() {
    std::ofstream fout("ct3-init-out.fb2");
    for (size_t k = 1; k < 65535; ++k) {
        std::ifstream fin("ct3.fb2", std::ios::binary);
        fin >> std::noskipws;
        LFSR gen(k, {15, 12, 10});
        char c;
        fout << ">> " << k << "\n";
        for (size_t i = 0; i < 100; ++i) {
            fin >> c;
            fout << char(c ^ (char) gen.GenerateWord().to_ulong());
        }
        fout << "-------------------------------------\n";
    }
    fout.close();
}

// ct1 = 3490
// ct8 = 21895

void Decode() {
    std::ifstream fin("ct3.fb2", std::ios::binary);
    std::ofstream fout("ct3-out.fb2");

    LFSR gen(34903, {15, 12, 10});
    fin >> std::noskipws;
    char c;
    for (size_t i = 0; i < 1456130 ; ++i) {
        fin >> c;
        fout << char(c ^ (char) gen.GenerateWord().to_ulong());
    }
}

int main() {
    FindInitial();
//    Decode();
    return 0;
}
