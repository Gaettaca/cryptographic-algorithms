#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include "LFSR.h"

void lfsr() {
    uint16_t S = 17590;
    for (size_t i = 1; i < 65; ++i) {
        std::cout << int(S & 1);
        S = (((S >> 15) ^ (S >> 12) ^ (S >> 10) ^ S) << 15) | (S >> 1);
        if (i % 8 == 0) { std::cout << "\n"; }
    }
}

void OpenTestFile() {
//    std::ofstream fout("out-test.txt");

    for (size_t i = 17584; i < 17600; ++i) {
        std::ifstream fin("out-test.txt", std::ios::binary);
        LFSR gen(i, {15, 12, 10});
        char c;
        fin >> std::noskipws;
        std::cout << ">> " << i << " ";
        while (fin >> c) {
            std::cout << char(c ^ (char) gen.GenerateWord().to_ulong());
        }
        std::cout << "\n";
    }
}

void RussianTextOpenFile() {
    std::ifstream fin("rus.txt", std::ios::binary);
    std::ofstream fout("out-rus.txt");
    uint8_t c;
    while (fin >> c) {
        fout << c << "";
    }
}

void LuEncryption() {
    std::ifstream fin("Lu.fb2", std::ios::binary);
    std::ofstream fout("Lu-out.fb2");

    char c;
    fin >> std::noskipws;
    LFSR gen(21089, {15, 12, 10});
    for (size_t i = 0; i < 100; ++i) {
        fin >> c;
        fout << char (c ^ (char) gen.GenerateWord().to_ulong());
    }
    fin.close();
    fout.close();
}

void LuDecryption() {
    std::ofstream fout("Lu-out-dec.fb2");


    for (size_t k = 21089; k < 21090; ++k) {
        std::ifstream fin("Lu-out.fb2", std::ios::binary);
        fin >> std::noskipws;
        LFSR gen(k, {15, 12, 10});
        char c;
        for (size_t i = 0; i < 100; ++i) {
            fin >> c;
            fout << char(c ^ (char) gen.GenerateWord().to_ulong());
        }
    }
    fout.close();
}

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

//    LuEncryption();
//    LuDecryption();

//    OpenTestFile();
//    RussianTextOpenFile();

//    LFSR gen(17590, {15, 12, 10});
//    for (size_t i = 0; i < 13; ++i) {
//        std::cout << gen.GenerateWord() << "\n";
//    }
    return 0;
}
