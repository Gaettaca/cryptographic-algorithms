#ifndef CPP_LAB3_REMASTERED_G_MODEL_CPP
#define CPP_LAB3_REMASTERED_G_MODEL_CPP

#include <boost/math/special_functions/gamma.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <map>
#include <bitset>
#include <vector>
#include <cmath>
#include "g-model.h"

void G::Encryption(std::bitset<8> &a, std::bitset<8> &b) {
    auto temp = b;
    for (size_t i = 0; i < clocks; ++i) {
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

void G::Decryption(std::bitset<8> &a, std::bitset<8> &b) {
    auto temp = a;
    for (size_t i = 0; i < clocks; ++i) {
        a ^= clock_keys[clocks - 1 - i];

        auto s1 = (a >> 4);
        auto s2 = (a << 4) >> 4;

        a = std::bitset<8>(((((IntPow(3, s1.to_ulong()) % 17) + 2) % 16) << 4)
                           | (((IntPow(5, s2.to_ulong()) % 17) + 7) % 16));
        a = ((a << 3) | (a >> 5)) ^ b;
        b = temp;
        temp = a;

    }
}

void G::ECBEncryption(const size_t &clocks_number, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();
    char c1, c2;

    in >> std::noskipws;
    out << std::noskipws;
    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        this->Encryption(a, b);
        out << (char) a.to_ulong() << (char) b.to_ulong();
    }
    in.close();
    out.close();
}

void G::ECBDecryption(const size_t &clocks_number, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();
    char c1, c2;

    in >> std::noskipws;
    out << std::noskipws;
    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        this->Decryption(a, b);
        out << (char) a.to_ulong() << (char) b.to_ulong();
    }
    in.close();
    out.close();
}

void G::CBCEncryption(const size_t &clocks_number, int &fa, int &sb, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    in >> std::noskipws;
//    out << std::noskipws;

    auto init_a = std::bitset<8>(fa);
    auto init_b = std::bitset<8>(sb);
    out << (char) init_a.to_ulong() << (char) init_b.to_ulong();

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();
    char c1, c2;

    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        a ^= init_a;
        b ^= init_b;
        this->Encryption(a, b);

        init_a = a;
        init_b = b;
        out << (char) a.to_ulong() << (char) b.to_ulong();
    }
}

void G::CBCDecryption(const size_t &clocks_numbers, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_numbers);

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();

    in >> std::noskipws;
//    out << std::noskipws;

    char c1, c2;
    in >> c1 >> c2;
    auto init_a = std::bitset<8>(c1);
    auto init_b = std::bitset<8>(c2);

    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        auto temp_a = a;
        auto temp_b = b;
        this->Decryption(a, b);

        a ^= init_a;
        b ^= init_b;

        init_a = temp_a;
        init_b = temp_b;
        out << (char) a.to_ulong() << (char) b.to_ulong();
    }
}

void G::CFBEncryption(const size_t &clocks_number, int &fa, int &sb, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(1, 255);

    in >> std::noskipws;
    out << std::noskipws;

    auto init_a = std::bitset<8>(fa);
    auto init_b = std::bitset<8>(sb);
    out << (char) init_a.to_ulong() << (char) init_b.to_ulong();

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();
    char c1, c2;
    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        this->Encryption(init_a, init_b);
        init_a ^= a;
        init_b ^= b;

        out << (char) init_a.to_ulong() << (char) init_b.to_ulong();
    }
}

void G::CFBDecryption(const size_t &clocks_number, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    in >> std::noskipws;
    out << std::noskipws;

    char c1, c2;
    in >> c1 >> c2;

    auto init_a = std::bitset<8>(c1);
    auto init_b = std::bitset<8>(c2);

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();
    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        this->Encryption(init_a, init_b);

        init_a ^= a;
        init_b ^= b;

        out << (char) init_a.to_ulong() << (char) init_b.to_ulong();

        init_a = a;
        init_b = b;
    }
}

void G::TestCorrectnessOfECB() {
    this->SetClocks(8);

    auto a = std::bitset<8>("10011011");
    auto b = std::bitset<8>("00110111");
    char c1, c2;

    std::cout << "Base:\n" << ">> " << a << " " << b << "\n";
    this->Encryption(a, b);
    std::cout << "Encrypted: " << ">> " << a << " " << b << "\n";
    this->Decryption(a, b);
    std::cout << "Decrypted: " << ">> " << a << " " << b << "\n";
}


void G::TestAET() {
    std::ofstream out("basic-test.txt");
    std::string seq = "1100100100001111110110101010001000100001011010001100001000110100110001001100011001100010100010111000";
    ApproximateEntropyTest(2, 100, seq);

    seq = "0100110101";
    ApproximateEntropyTest(3, 10, seq);
    out.close();
}

void G::OFBEncryption(const size_t &clocks_number, int &fa, int &sb, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    in >> std::noskipws;
    out << std::noskipws;

    auto init_a = std::bitset<8>(fa);
    auto init_b = std::bitset<8>(sb);
    out << (char) init_a.to_ulong() << (char) init_b.to_ulong();

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();
    char c1, c2;

    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        this->Encryption(init_a, init_b);

        a ^= init_a;
        b ^= init_b;

        out << (char) a.to_ulong() << (char) b.to_ulong();
    }
}

void G::OFBDecryption(const size_t &clocks_number, const std::string &input, const std::string &output) {
    std::ifstream in(input, std::ios::binary);
    std::ofstream out(output);

    this->SetClocks(clocks_number);

    in >> std::noskipws;
    out << std::noskipws;
    char c1, c2;

    in >> c1 >> c2;
    auto init_a = std::bitset<8>(c1);
    auto init_b = std::bitset<8>(c2);

    auto a = std::bitset<8>();
    auto b = std::bitset<8>();

    while (in >> c1 >> c2) {
        a = std::bitset<8>(c1);
        b = std::bitset<8>(c2);

        this->Encryption(init_a, init_b);

        a ^= init_a;
        b ^= init_b;

        out << (char) a.to_ulong() << (char) b.to_ulong();
    }
}

#endif