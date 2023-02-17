#ifndef LAB6_BIG_INT_H
#define LAB6_BIG_INT_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

typedef long long int ll;

class BigInteger {
private:
    static const long long BASE = 1e9;
    static const long long MIN_SIZE = 4;
    std::vector<int> digits;
public:
    BigInteger(const size_t &n) {
        digits = std::vector<int>(n, 0);
    }

    BigInteger(const std::string &str_num) {
        for (int i = (int) str_num.length(); i > 0; i -= 9) {
            if (i < 9) {
                digits.push_back(std::stoi(str_num.substr(0, i)));
            } else {
                digits.push_back(std::stoi(str_num.substr(i - 9, 9)));
            }
        }
    }

    BigInteger &operator=(const BigInteger &b) = default;

    BigInteger operator+(const BigInteger &b) {
        BigInteger res = *this;
        int carry = 0;
        for (size_t i = 0; i < std::max(res.digits.size(), b.digits.size()) || carry; ++i) {
            if (i == res.digits.size()) { res.digits.emplace_back(0); }
            // если false, то переносится остаток на следующий разряд
            res.digits[i] += carry + (i < b.digits.size() ? b.digits[i] : 0);
            carry = res.digits[i] >= BASE;
            if (carry) { res.digits[i] -= BASE; }
        }
        return res;
    }

    BigInteger operator-(const BigInteger &b) {
        BigInteger res = *this;
        int carry = 0;
        for (size_t i = 0; i < b.digits.size() || carry; ++i) {
            res.digits[i] -= carry + (i < b.digits.size() ? b.digits[i] : 0);
            carry = res.digits[i] < 0;
            if (carry) { res.digits[i] += BASE; }
        }
        while (res.digits.size() > 1 && res.digits.back() == 0) {
            res.digits.pop_back();
        }
        return res;
    }

    BigInteger operator*(const ll &b) {
        BigInteger res = *this;
        int carry = 0;
        for (size_t i = 0; i < res.digits.size() || carry; ++i) {
            if (i == res.digits.size()) {
                res.digits.emplace_back(0);
            }
            long long cur = carry + res.digits[i] * 1ll * b;
            res.digits[i] = int(cur % BASE);
            carry = int(cur / BASE);
        }
        while (res.digits.size() > 1 && res.digits.back() == 0) {
            res.digits.pop_back();
        }
        return res;
    }

    BigInteger operator*(const BigInteger &b) {
        BigInteger res(this->digits.size() + b.digits.size());
        for (size_t i = 0; i < this->digits.size(); ++i)
            for (int j = 0, carry = 0; j < (int) b.digits.size() || carry; ++j) {
                long long cur =
                        res.digits[i + j] + this->digits[i] * 1ll * (j < (int) b.digits.size() ? b.digits[j] : 0) +
                        carry;
                res.digits[i + j] = int(cur % BASE);
                carry = int(cur / BASE);
            }
        while (res.digits.size() > 1 && res.digits.back() == 0)
            res.digits.pop_back();
        return res;
    }

    BigInteger operator/(const ll &b) {
        BigInteger res = *this;
        int carry = 0;
        for (int i = (int) res.digits.size() - 1; i >= 0; --i) {
            long long cur = res.digits[i] + carry * 1ll * BASE;
            res.digits[i] = int(cur / b);
            carry = int(cur % b);
        }
        while (res.digits.size() > 1 && res.digits.back() == 0) {
            res.digits.pop_back();
        }
        return res;
    }

    void shift_right() {
        this->digits.insert(this->digits.begin(), 0);
    }

    BigInteger operator/(BigInteger b) {
        BigInteger res = *this;
        BigInteger result(this->digits.size()), current("0");
        for (long long i = this->digits.size(); i >= 0; --i) {

        }
        return 0;
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInteger &bigInteger);

    void Print() {
        printf("%d", this->digits.empty() ? 0 : this->digits.back());
        for (int i = (int) this->digits.size() - 2; i >= 0; --i)
            printf(".%09d", this->digits[i]);
    }
};

std::ostream &operator<<(std::ostream &os, const BigInteger &bigInteger) {
    std::string zero_temp = "000000000";
    std::string output;
    for (int i = bigInteger.digits.size() - 1; i >= 0; --i) {
        size_t part_length = std::to_string(bigInteger.digits[i]).length();
        if (part_length < 9 && i != bigInteger.digits.size() - 1) {
            output += zero_temp.substr(0, 9 - part_length);
        }
        output += std::to_string(bigInteger.digits[i]) + "";
    }
    os << output;
    return os;
}

#endif //LAB6_BIG_INT_H
