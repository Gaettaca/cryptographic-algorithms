//
// Created by User on 13.04.2022.
//

#ifndef CPP_LAB3_REMASTERED_G_MODEL_H
#define CPP_LAB3_REMASTERED_G_MODEL_H

#include <boost/math/special_functions/gamma.hpp>
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
    size_t clocks;

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
    void PrintInfo() {
        std::cout << "---------------G MODEL PARAMS----------------";
        std::cout << "\nkey:\n" << ">> " << key;
        std::cout << "\namount of clocks:\n" << ">> " << clocks;
        std::cout << "\nclock's keys:\n";
        for (const auto &i: clock_keys) {
            std::cout << ">> " << i << "\n";
        }
        std::cout << "==============================================\n";
    }

    G(const uint32_t &_key, const size_t &_clocks = 8) {
        key = std::bitset<32>(_key);
        clocks = _clocks;
        clock_keys = std::vector<std::bitset<8>>(8);
        for (int i = 31, j = 0; i >= 0; --i) {
            clock_keys[j][i % 8] = key[i];
            clock_keys[j + 4][i % 8] = key[i];
            if (i % 8 == 0) { ++j; }
        }
    }

    void Encryption(std::bitset<8> &a, std::bitset<8> &b);
    void Decryption(std::bitset<8> &a, std::bitset<8> &b);

    void ECBEncryption(const size_t &clocks_number, const std::string &input, const std::string &output);
    void ECBDecryption(const size_t &clocks_number, const std::string &input, const std::string &output);

    void CBCEncryption(const size_t &clocks_number, int &a, int &b, const std::string &input, const std::string &output);
    void CBCDecryption(const size_t &clocks_number, const std::string &input, const std::string &output);

    void CFBEncryption(const size_t &clocks_number, int &a, int &b, const std::string &input, const std::string &output);
    void CFBDecryption(const size_t &clocks_number, const std::string &input, const std::string &output);

    void OFBEncryption(const size_t &clocks_number, int &a, int &b, const std::string &input, const std::string &output);
    void OFBDecryption(const size_t &clocks_number, const std::string &input, const std::string &output);

    static double Phi(size_t n, size_t m, std::string sequence) {
        double phi{};
        sequence += sequence.substr(0, m - 1);
        std::map<std::string, size_t> freq;
        for (size_t i = 0; i < IntPow(2, m); ++i) {
            freq[std::bitset<9>(i).to_string()] = 0;
        }

        std::string buf = freq.begin()->first.substr(0, 9 - m);
        for (size_t i = 0; i < n; ++i) {
            ++freq[buf + sequence.substr(i, m)];
        }

        std::string temp;
        for (size_t i = 0; i < IntPow(2, m); ++i) {
            double logarithm{};
            temp = std::bitset<9>(i).to_string();
            double a = (double) freq[temp] / (double) n;
            if (freq[temp]) {
                logarithm = log(a);
            }
            phi += a * logarithm;
        }
        return phi;
    }

    static void ApproximateEntropyTest(const size_t &m, const size_t &n, std::string &sequence) {
        std::vector<double> phi(2, 0.0);
        phi[0] = Phi(n, m, sequence);
        phi[1] = Phi(n, m + 1, sequence);

        double chi2 = 2.0 * (double)n * (std::log(2) - (phi[0] - phi[1]));
        double igamc = boost::math::gamma_q(IntPow(2, m - 1), chi2 / 2);

        std::cout << std::setprecision(10);
        std::cout << "phi1: " << phi[0] << "\n";
        std::cout << "phi2: " << phi[1] << "\n";
        std::cout << "apen: " << phi[0] - phi[1] << "\n";
        std::cout << "chi2: " << chi2 << "\n";
        std::cout << "igamc: " << igamc << "\n";
        std::cout << "--------------------------------\n";
    }

    void AET(const std::string &input, std::ofstream &out) {
        std::ifstream in(input, std::ios::binary);
//        std::cout << ">> " << input << "\n";

        in >> std::noskipws;
        char c;
        std::string sequence;
        while (in >> c) {
            sequence += std::bitset<8>(c).to_string();
        }

//        std::cout << "[" << sequence.length() << "]\n";
        ApproximateEntropyTest(8, sequence.length(), sequence);
        in.close();
    }

    void Entropy(const std::string &input) {
        std::ifstream in(input, std::ios::binary);
//        std::cout << ">> " << input << "\n";

        in >> std::noskipws;
        char c;
        std::string sequence;
        while (in >> c) {
            sequence += std::bitset<8>(c).to_string();
        }
        std::cout << -Phi(sequence.length(), 8, sequence) << "\n";
    }

    void SetClocks(const size_t &num) {
        clocks = num;
    }

    void TestCorrectnessOfECB();
    void TestAET();
};


#endif //CPP_LAB3_REMASTERED_G_MODEL_H
