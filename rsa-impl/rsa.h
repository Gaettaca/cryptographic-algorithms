//
// Created by User on 16.05.2022.
//

#ifndef LAB6_RSA_H
#define LAB6_RSA_H

#include "g.h"
#include "BigInt.h"
typedef unsigned long long int ull;

class RSA {
private:
    ull d, p, q, phi;

    ull gcdex(ull a, ull b, ull &x, ull &y) {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        ull x1, y1;
        ull d = gcdex(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }

    ull InverseModulo(const ull &a, const ull &m) {
        ull x, y;
        ull g = gcdex(a, m, x, y);
        if (g != 1) { std::cout << "There is no inversed modulo"; }
        else { x = (x % m + m) % m; }
        return x;
    }


    ull BinPow(const ull &base, const ull &m, ull p) {
        if (p == 1) { return base; }
        if (p % 2 == 0) {
            ull t = BinPow(base, m, p / 2);
            return t * t % m;
        } else {
            return BinPow(base, m, p - 1) * base % m;
        }
    }

public:
    RSA(const long long &_e, const long long &_p, const long long &_q) {
        q = _q;
        p = _p;
        n = _p * _q;
        phi = (_p - 1) * (_q - 1);
        e = _e;
        d = InverseModulo(e, phi);
    }

    void Encrypt() {}
    void Decrypt() {}

    std::vector<ull> CreateSignature(const std::string &file, bool public_key) {
        G g;
        auto hash = g.HashFile("signature.txt");

        ull key;
        if (public_key) { key = e; }
        else { key = d; }

        std::vector<ull> signature(4, 0);
        for (size_t i = 0; i < 4; ++i) {
            signature[i] = BinPow((ull)((hash << 8 * i) >> 24).to_ulong(), n, key);
        }

        return signature;
    }

    void CheckSignature(std::vector<ull> &bobs_sign, const std::string &file) {
        std::ifstream fin(file, std::ifstream::binary | std::ifstream::in);
        G g;
        auto hash = g.HashFile(file);

        std::vector<ull> bobs_hash(4, 0);
        for (size_t i = 0; i < 4; ++i) {
            bobs_hash[i] = BinPow(bobs_sign[i], n, e);
        }

        std::cout << "BOB'S DECRYPTED SIGN:\n >>> ";
        for (const auto &i : bobs_hash) {
            std::cout << i << " ";
        }
        std::cout << "\n";

        std::vector<ull> alice_hash(4);
        for (size_t i = 0; i < 4; ++i) {
            alice_hash[i] = ((hash << 8 * i) >> 24).to_ulong();
        }

        std::cout << "ALICE'S HASH:\n >>> ";
        for (const auto &i : alice_hash) {
            std::cout << i << " ";
        }
        std::cout << "\n";

        size_t count = 0;
        for (size_t i = 0; i < 4; ++i) {
            if (bobs_hash[i] == alice_hash[i]) { ++count; }
        }
        
        if (count == 4) { std::cout << " >>> Verified!\n"; }
        else { std::cout << " >>> Denied!\n"; }
    }

    long long int e, n;

    void PrintState() {
        std::cout << "======== [ STATE ] ========\n";
        std::cout << "\te: " << e << "\n";
        std::cout << "\td: " << d << "\n";
        std::cout << "\tphi: " << phi << "\n";
        std::cout << "\tp: " << p << "\n";
        std::cout << "\tq: " << q << "\n";
        std::cout << "\tn: " << n << "\n";
        std::cout << "===========================\n";
    }
};

#endif //LAB6_RSA_H
