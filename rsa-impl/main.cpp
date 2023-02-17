#include <boost/math/special_functions/binomial.hpp>
#include <iostream>
#include <bitset>
#include "big_int.h"
#include "BigInt.h"
#include "rsa.h"
#include "bigrsa.h"
#include "g.h"


bool MillerRabinTest(const BigInt &n, const size_t &k) {
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
//            a = BigInt::generate(1, n.GetDigit());
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

void PrimeTest() {
    BigInt bi("502295622263112702220260543540794911664518847800699039");
    std::cout << bi << " " << (MillerRabinTest(bi, 32) ? "prime" : "not prime") << "\n";
}

void TestBigSignature() {
    BigRSA bs1(8);
    bs1.PrintState();

    std::string file = "signature.txt";
    std::vector<BigInt> bobs_sign = bs1.CreateSignature(file, false);

    std::cout << "BOB'S ENCRYPTED SIGN:\n";
    for (const auto &i: bobs_sign) {
        std::cout << i << "\n";
    }
    std::cout << "\n";


    bs1.CheckSignature(bobs_sign, "signature.txt");
//    bs1.CheckSignature(bobs_sign, "signature1.txt");
}

void test() {
    boost::multiprecision::uint512_t a("502295622263112702220260543540794911664518847800699039");
    boost::multiprecision::uint512_t b("31127022202605435407949116");
    std::cout << a % b << "\n";

    BigInt bi1("502295622263112702220260543540794911664518847800699039");
    BigInt bi2("31127022202605435407949116");
    std::cout << bi1 % bi2 << "\n";
}

int main() {
    test();
//    TestBigSignature();
//    PrimeTest();

    return 0;
}