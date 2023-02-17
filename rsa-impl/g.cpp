#ifndef CPP_LAB3_REMASTERED_G_MODEL_CPP
#define CPP_LAB3_REMASTERED_G_MODEL_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <bitset>
#include <vector>
#include <cmath>
#include "g.h"

void PrintResult(std::bitset<32> hash, std::ofstream &out, std::ofstream &bin) {
    bin << hash.to_string() << " ";
    std::vector<char> output(4);
    for (int i = 3; i >= 0; --i) {
        output[i] = static_cast<char>(((hash << 24) >> 24).to_ulong());
        hash >>= 8;
    }
    for (auto c: output) {
        bin << std::bitset<8>(c).to_string() << " ";
    }
}

void G::Encryption(std::bitset<8> &a, std::bitset<8> &b) {
    auto temp = b;
    for (size_t i = 0; i < 8; ++i) {
        b ^= clock_keys[i];

        auto s1 = (b >> 4);
        auto s2 = (b << 4) >> 4;

        b = std::bitset<8>(((((IntPow(3, s1.to_ulong()) % 17) + 2) % 16) << 4)
                           | (((IntPow(5, s2.to_ulong()) % 17) + 7) % 16));
        b = ((b << 3) | (b >> 5)) ^ a;
        a = temp;
        temp = b;
    }
}

std::bitset<32> G::HashFile(const std::string &file) {
    std::ifstream fin(file, std::ifstream::binary | std::ifstream::in);
    std::ofstream fout("hash.txt", std::ifstream::binary | std::ofstream::out);
    std::ofstream bin_hash("bin_hash.txt", std::ifstream::binary | std::ofstream::out);

    fin >> std::noskipws;
    fout << std::noskipws;

    char input;
    std::bitset<32> first_block, hash;
    hash = std::bitset<32>(93292932);
    bool file_ended = false;
    long long int counter = 0;

    while (fin >> input) {
        ++counter;
        first_block = std::bitset<32>(0);
        first_block |= std::bitset<32>(input);
        for (int i = 0; i < 3; ++i) {
            if (fin >> input) {
                ++counter;
                first_block <<= 8;
                first_block |= std::bitset<32>(input);
            } else {
                file_ended = true;
                break;
            }
        }
        hash = GetHash(first_block, hash);

        if (file_ended) {
            first_block = std::bitset<32>(counter);
            hash = GetHash(first_block, hash);
        }
    }
    if (!file_ended) {
        first_block = std::bitset<32>(counter);
        hash = GetHash(first_block, hash);
    }
//    PrintResult(hash, fout, bin_hash);
    return hash;
}

std::bitset<32> G::GetHash(const std::bitset<32> &X, const std::bitset<32> &Y) {
    return X ^ Y ^ GetCipher(Y, X);
}

std::bitset<32> G::GetCipher(std::bitset<32> block, std::bitset<32> _key) {
    SetKey(_key);
//    std::bitset<32> result(0);
    std::vector<std::bitset<8>> chars(4);

    for (size_t i = 0; i < 4; ++i) {
        chars[i] = std::bitset<8>(((block << 8 * i) >> 24).to_ulong());
    }

    block >>= 32;
    for (size_t i = 0; i < 2; ++i) {
        this->Encryption(chars[2 * i], chars[2 * i + 1]);
        block |= std::bitset<32>(chars[2 * i].to_ulong());
        block <<= 8;
        block |= std::bitset<32>(chars[2 * i + 1].to_ulong());
        block <<= 8;
    }
    return block;
}


#endif