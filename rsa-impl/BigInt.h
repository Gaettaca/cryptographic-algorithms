#ifndef LAB6_BIGINT_H
#define LAB6_BIGINT_H

//#include <boost/random/mersenne_twister.hpp>
//#include <boost/random/uniform_int_distribution.hpp>
//#include <boost/random/random_device.cpp>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <random>
#include <sstream>

class BigInt {
private:
    static const int BASE = 1000000000;
    std::vector<int> _digits;
    bool _is_negative;

    void _remove_leading_zeros();

public:
    class divide_by_zero : public std::exception {
    };

    void _shift_right();

    BigInt();

    BigInt(const size_t &n, const bool &ex = true) {
        _is_negative = false;
        _digits = std::vector<int>(n, 0);
    }

    BigInt(std::string);

    BigInt(signed short);

    BigInt(unsigned short);

    BigInt(signed int);

    BigInt(unsigned int);

    BigInt(signed long);

    BigInt(unsigned long);

    BigInt(signed long long);

    BigInt(unsigned long long);

    friend std::ostream &operator<<(std::ostream &, const BigInt &);

    operator std::string() const;

    const BigInt operator+() const;

    const BigInt operator-() const;

    const BigInt operator++();

    const BigInt operator++(int);

    const BigInt operator--();

    const BigInt operator--(int);

    friend bool operator==(const BigInt &, const BigInt &);

    friend bool operator<(const BigInt &, const BigInt &);

    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator<=(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);

    friend bool operator>=(const BigInt &, const BigInt &);

    friend const BigInt operator+(BigInt, const BigInt &);

    BigInt &operator+=(const BigInt &);

    friend const BigInt operator-(BigInt, const BigInt &);

    BigInt &operator-=(const BigInt &);

    friend const BigInt operator*(const BigInt &, const BigInt &);

    BigInt &operator*=(const BigInt &);

    friend BigInt operator/(const BigInt &, const BigInt &);

    BigInt &operator/=(const BigInt &);

    friend BigInt operator%(const BigInt &, const BigInt &);

    BigInt &operator%=(const BigInt &);

    bool odd() const;

    bool even() const;

    BigInt pow(BigInt) const;

    static BigInt modpow(BigInt a, BigInt n, const BigInt &m);

    static BigInt generate(const size_t &lower_bound, const size_t &upper_bound) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> digit_distrib(lower_bound, upper_bound);

        size_t n = digit_distrib(gen);
        BigInt res(n, true);

        std::uniform_int_distribution<int> distrib(2, BASE - 1);
        for (size_t i = 0; i < n; ++i) {
            res._digits[i] = distrib(gen);
        }

        return BigInt(res);
    }

    void Print() {
        for (const auto &i: this->_digits) {
            std::cout << i << "..";
        }
        std::cout << "\n";
    }

    size_t GetDigit() const {
        return this->_digits.size();
    }
};

// создает длинное целое число со значением 0
BigInt::BigInt() {
    this->_is_negative = false;
}

// создает длинное целое число из C++-строки
BigInt::BigInt(std::string str) {
    if (str.length() == 0) {
        this->_is_negative = false;
    } else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->_is_negative = true;
        } else {
            this->_is_negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9) {
                this->_digits.push_back(std::stoi(str.substr(0, i).c_str()));
            } else {
                this->_digits.push_back(std::stoi(str.substr(i - 9, 9).c_str()));
            }
        }

        this->_remove_leading_zeros();
    }
}

BigInt::BigInt(signed short s) {
    if (s < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(s));
}

// преобразует unsigned short к big_integer
BigInt::BigInt(unsigned short s) {
    this->_is_negative = false;
    this->_digits.push_back(s);
}

// преобразует signed int к big_integer
BigInt::BigInt(signed int i) {
    if (i < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(i) % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->_digits.push_back(std::abs(i));
}

// преобразует unsigned int к big_integer
BigInt::BigInt(unsigned int i) {
    this->_digits.push_back(i % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->_digits.push_back(i);
}

// преобразует signed long к big_integer
BigInt::BigInt(signed long l) {
    if (l < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(l) % BigInt::BASE);
    l /= BigInt::BASE;
    if (l != 0) this->_digits.push_back(std::abs(l));
}

// преобразует unsigned long к big_integer
BigInt::BigInt(unsigned long l) {
    this->_digits.push_back(l % BigInt::BASE);
    l /= BigInt::BASE;
    if (l != 0) this->_digits.push_back(l);
}

// преобразует signed long long к big_integer
BigInt::BigInt(signed long long l) {
    if (l < 0) {
        this->_is_negative = true;
        l = -l;
    }
    else this->_is_negative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

// преобразует unsigned long long к big_integer
BigInt::BigInt(unsigned long long l) {
    this->_is_negative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

// удаляет ведущие нули
void BigInt::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// печатает число в поток вывода
std::ostream &operator<<(std::ostream &os, const BigInt &bi) {
    if (bi._digits.empty()) os << 0;
    else {
        if (bi._is_negative) os << '-';
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) {
            os << std::setw(9) << bi._digits[i];
        }
        os.fill(old_fill);
    }

    return os;
}

// сравнивает два числа на равенство
bool operator==(const BigInt &left, const BigInt &right) {
    if (left._is_negative != right._is_negative) return false;
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

// возвращает копию переданного числа
const BigInt BigInt::operator+() const {
    return BigInt(*this);
}

// возвращает переданное число с другим знаком
const BigInt BigInt::operator-() const {
    BigInt copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

// проверяет, является ли левый операнд меньше правого
bool operator<(const BigInt &left, const BigInt &right) {
    if (left == right) return false;
    if (left._is_negative) {
        if (right._is_negative) return ((-right) < (-left));
        else return true;
    } else if (right._is_negative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        } else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }

            return false;
        }
    }
}

// сравнивает два числа на неравенство
bool operator!=(const BigInt &left, const BigInt &right) {
    return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator<=(const BigInt &left, const BigInt &right) {
    return (left < right || left == right);
}

// проверяет, является ли левый операнд больше правого
bool operator>(const BigInt &left, const BigInt &right) {
    return !(left <= right);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator>=(const BigInt &left, const BigInt &right) {
    return !(left < right);
}

// складывает два числа
const BigInt operator+(BigInt left, const BigInt &right) {
    if (left._is_negative) {
        if (right._is_negative) return -(-left + (-right));
        else return right - (-left);
    } else if (right._is_negative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= BigInt::BASE;
        if (carry != 0) left._digits[i] -= BigInt::BASE;
    }

    return left;
}

// прибавляет к текущему числу новое
BigInt &BigInt::operator+=(const BigInt &value) {
    return *this = (*this + value);
}

// префиксный инкремент
const BigInt BigInt::operator++() {
    return (*this += 1);
}

// преобразует число к строке
BigInt::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}


//// преобразует signed int к BigInt
//BigInt::BigInt(signed int i) {
//    if (i < 0) this->_is_negative = true;
//    else this->_is_negative = false;
//    this->_digits.push_back(std::abs(i) % BigInt::BASE);
//    i /= BigInt::BASE;
//    if (i != 0) this->_digits.push_back(std::abs(i));
//}
//
//
//
//// преобразует unsigned long long к BigInt
//BigInt::BigInt(unsigned long long l) {
//    this->_is_negative = false;
//    do {
//        this->_digits.push_back(l % BigInt::BASE);
//        l /= BigInt::BASE;
//    } while (l != 0);
//}

// постфиксный инкремент
const BigInt BigInt::operator++(int) {
    *this += 1;
    return *this - 1;
}

// префиксный декремент
const BigInt BigInt::operator--() {
    return *this -= 1;
}

// постфиксный декремент
const BigInt BigInt::operator--(int) {
    *this -= 1;
    return *this + 1;
}

// вычитает два числа
const BigInt operator-(BigInt left, const BigInt &right) {
    if (right._is_negative) return left + (-right);
    else if (left._is_negative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += BigInt::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

// вычитает из текущего числа новое
BigInt &BigInt::operator-=(const BigInt &value) {
    return *this = (*this - value);
}

// перемножает два числа
const BigInt operator*(const BigInt &left, const BigInt &right) {
    BigInt result;
    result._digits.resize(left._digits.size() + right._digits.size());
    for (size_t i = 0; i < left._digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
                            left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % BigInt::BASE);
            carry = static_cast<int>(cur / BigInt::BASE);
        }
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// домножает текущее число на указанное
BigInt &BigInt::operator*=(const BigInt &value) {
    return *this = (*this * value);
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInt::_shift_right() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

// делит два числа
BigInt operator/(const BigInt &left, const BigInt &right) {
    if (right == 0) throw BigInt::divide_by_zero();

    BigInt b = right;
    b._is_negative = false;
    BigInt result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shift_right();
        current._digits[0] = left._digits[i];
        current._remove_leading_zeros();
        int x = 0, l = 0, r = BigInt::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInt t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            } else { r = m - 1; }
        }
        result._digits[i] = x;
        current = current - b * x;
    }
    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// делит текущее число на указанное
BigInt &BigInt::operator/=(const BigInt &value) {
    return *this = (*this / value);
}

// возвращает остаток от деления двух чисел
BigInt operator%(const BigInt &left, const BigInt &right) {
//    std::cout << left << " " << right << "\n";
    BigInt result = left - (left / right) * right;
//    std::cout << result << "\n";
    if (result._is_negative) result += right;
    return result;
}

// присваивает текущему числу остаток от деления на другое число
BigInt &BigInt::operator%=(const BigInt &value) {
    return *this = (*this % value);
}

// проверяет, является ли текущее число нечетным
bool BigInt::odd() const {
    if (this->_digits.size() == 0) return false;
    return this->_digits[0] & 1;
}

// проверяет, является ли текущее число четным
bool BigInt::even() const {
    return !this->odd();
}

// возводит текущее число в указанную степень
BigInt BigInt::pow(BigInt n) const {
    BigInt a(*this), result(1);
    while (n != 0) {
        if (n.odd()) result *= a;
        a *= a;
        n /= 2;
    }
    return result;
}

BigInt BigInt::modpow(BigInt a, BigInt n, const BigInt &m) {
    BigInt result(1);
    while (n != 0) {
        if (n.odd()) {
            result *= a;
            result %= m;
        }

        a *= a;
        a %= m;
        n /= 2;
    }
    return result;
}

#endif