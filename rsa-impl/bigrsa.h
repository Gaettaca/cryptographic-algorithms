
#ifndef LAB6_BIGRSA_H
#define LAB6_BIGRSA_H

#include <vector>
#include "g.h"
#include "BigInt.h"


typedef unsigned long long int ull;

class BigRSA {
private:
    BigInt d, p, q, phi;
    std::vector<int> first_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
                                            83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                                            173, 179, 181, 191, 193, 197, 199, 211, 223,
                                            227, 229, 233, 239, 241, 251, 257};

    BigInt gcdex(BigInt a, BigInt b, BigInt &x, BigInt &y) {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        BigInt x1, y1;
        BigInt d = gcdex(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }

    BigInt InverseModulo(const BigInt &a, const BigInt &m) {
        BigInt x, y;
        BigInt g = gcdex(a, m, x, y);
        if (g != 1) { std::cout << "There is no inversed modulo"; }
        else { x = (x % m + m) % m; }
        return x;
    }

    BigInt BinPow(const BigInt &base, const BigInt &m, BigInt p) {
        if (p == 1) { return base; }
        if (p % 2 == 0) {
            BigInt t = BinPow(base, m, p / 2);
            return t * t % m;
        } else {
            return BinPow(base, m, p - 1) * base % m;
        }
    }

    static bool MillerRabinTest(const BigInt &n, const size_t &k) {
        if (n == 2 || n == 3) { return true; }
        if (n < 2 || n % 2 == 0) { return false; }

        BigInt t = n - 1;
        int s = 0;

        while (t % 2 == 0) {
            t /= 2;
            s += 1;
        }

        for (size_t i = 0; i < k; ++i) {
            BigInt a("0");
            while (a < 2 || a >= n - 2) {
                a = BigInt::generate(5, n.GetDigit());
            }

            BigInt x = BigInt::modpow(a, t, n);
            if (x == 1 || x == n - 1) { continue; }

            for (size_t r = 1; r < s; ++r) {
                x = BigInt::modpow(x, 2, n);
                if (x == 1) { return false; }
                if (x == n - 1) { break; }
            }
            if (x != n - 1) { return false; }
        }
        return true;
    }

    bool CheckFirstPrimes(const BigInt &bigint) {
        for (const auto &i : first_primes) {
            if (bigint % i == 0) { return false; }
        }
        return true;
    }

    BigInt GeneratePrime(const size_t &nd) {
        bool flag = false;
        BigInt res;
        while (!flag) {
            res = BigInt::generate(5, nd);
            if (CheckFirstPrimes(res)) {
                flag = MillerRabinTest(res, 32);
            } else { continue; }
        }
        return res;
    }

public:
    BigRSA(const size_t &nd) {
        e = GeneratePrime(nd);
        p = GeneratePrime(nd);
        q = GeneratePrime(nd);

        phi = (p - 1) * (q - 1);
        n = phi + p + q - 1;
        d = InverseModulo(e, phi);
    }

    void Encrypt() {}

    void Decrypt() {}

    std::vector<BigInt> CreateSignature(const std::string &file, bool public_key) {
        G g;
        auto hash = g.HashFile("signature.txt");

        BigInt key;
        if (public_key) { key = e; }
        else { key = d; }

        std::vector<BigInt> signature(4, 0);
        for (size_t i = 0; i < 4; ++i) {
            signature[i] = BinPow(BigInt(((hash << 8 * i) >> 24).to_ulong()), this->n, key);
        }

        return signature;
    }

    void CheckSignature(std::vector<BigInt> &bobs_sign, const std::string &file) {
        std::ifstream fin(file, std::ifstream::binary | std::ifstream::in);
        G g;
        auto hash = g.HashFile(file);

        std::vector<BigInt> bobs_hash(4, 0);
        for (size_t i = 0; i < 4; ++i) {
            bobs_hash[i] = BinPow(bobs_sign[i], n, e);
        }

        std::cout << "BOB'S DECRYPTED SIGN:\n >>> ";
        for (const auto &i: bobs_hash) {
            std::cout << i << " ";
        }
        std::cout << "\n";

        std::vector<BigInt> alice_hash(4);
        for (size_t i = 0; i < 4; ++i) {
            alice_hash[i] = ((hash << 8 * i) >> 24).to_ulong();
        }

        std::cout << "ALICE'S HASH:\n >>> ";
        for (const auto &i: alice_hash) {
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

    BigInt e, n;

    void PrintState() {
        std::cout << "======== [ STATE ] ========\n";
        std::cout << " e: " << e << "\n";
        std::cout << " d: " << d << "\n";
        std::cout << " phi: " << phi << "\n";
        std::cout << " p: " << p << "\n";
        std::cout << " q: " << q << "\n";
        std::cout << " n: " << n << "\n";
        std::cout << "===========================\n";
    }
};

#endif //LAB6_BIGRSA_H
