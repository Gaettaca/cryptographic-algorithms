//
// Created by User on 13.04.2022.
//

#ifndef CPP_LAB3_REMASTERED_G_MODEL_H
#define CPP_LAB3_REMASTERED_G_MODEL_H

#include <fstream>
#include <string>
#include <map>
#include <bitset>
#include <vector>
#include <cmath>

class G {
private:
    std::bitset<32> key;
    std::vector<std::bitset<8>> clock_keys;

    static long long int IntPow(long long int base, unsigned int exp) {
        long long int result = 1;
        while (exp) {
            if (exp % 2)
                result *= base;
            exp /= 2;
            base *= base;
        }
        return result;
    }

public:
    G() {}

    std::bitset<32> HashFile(const std::string &file);
    void Encryption(std::bitset<8> &a, std::bitset<8> &b);

    std::bitset<32> GetCipher(std::bitset<32> block, const std::bitset<32> _key);
    std::bitset<32> GetHash(const std::bitset<32> &X, const std::bitset<32> &Y);

    void SetKey(std::bitset<32> &_key) {
        key = std::bitset<32>(_key);
        clock_keys = std::vector<std::bitset<8>>(8);
        for (int i = 31, j = 0; i >= 0; --i) {
            clock_keys[j][i % 8] = key[i];
            clock_keys[j + 4][i % 8] = key[i];
            if (i % 8 == 0) { ++j; }
        }
    }
};


#endif //CPP_LAB3_REMASTERED_G_MODEL_H
