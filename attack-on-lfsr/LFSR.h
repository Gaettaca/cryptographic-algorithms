//
// Created by User on 13.04.2022.
//

#ifndef CPP_LAB2_LFSR_H
#define CPP_LAB2_LFSR_H

#include <bitset>
#include <vector>

class LFSR {
private:
    std::bitset<16> state;
    size_t init;
    std::vector<size_t> polinom;
public:
    LFSR(const size_t &_init, const std::vector<size_t> &_polinom) {
        init = _init;
        state = std::bitset<16>(_init);
        polinom = _polinom;
    }

    std::bitset<8> GenerateWord() {
        auto bitword = std::bitset<8>(0);
        auto bitone = std::bitset<16>(1);
        auto newbit = std::bitset<16>(0);
        for (size_t k = 0; k < 8; ++k) {
            newbit = state ^ (state >> polinom[0]);
            for (size_t i = 1; i < polinom.size(); ++i) {
                newbit ^= (state >> polinom[i]);
            }
            newbit &= bitone;
            bitword[7 - k] = (state & bitone)[0];
            state = (state >> 1) | (newbit << 15);
        }
        return bitword;
    }
};
#endif //CPP_LAB2_LFSR_H
