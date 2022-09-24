#include "BigInt/BigInt.h"
#include <climits>
#include <algorithm>


#define CELL_LIMIT 1000000000
#define MAX_OF_DIGITS 9

int BigInt::countIntLength(int num) {
    int lengthOfNum = 0;
    while (num) {
        num /= 10;
        ++lengthOfNum;
    }
    if (lengthOfNum == 0)
        ++lengthOfNum;
    return lengthOfNum;
}

bool BigInt::vctcmp(const std::vector<int> &bigger, const std::vector<int> &smaller) {
    return std::search(bigger.begin(), bigger.end(), smaller.begin(), smaller.end()) != bigger.end();
}

void BigInt::removeZeros() {
    while (number.back() == 0 && number.size() > 1)
        number.pop_back();

    remainderLength = countIntLength(number[0]);
}

BigInt::BigInt() : sign('+'), remainderLength(1) {
    number.push_back(0);
}

BigInt::BigInt(int num) {
    if (num >= CELL_LIMIT) {
        number.push_back(abs(num) % CELL_LIMIT);
        number.push_back(abs(num) / CELL_LIMIT);
    } else
        number.push_back(abs(num));

    (num < 0) ? this->sign = '-' : this->sign = '+';
}

BigInt::BigInt(std::string str) {
    bool isSigned = false;

    switch (str[0]) {
        case '-':
            sign = '-';
            isSigned = true;
            break;
        case '+':
            sign = '+';
            isSigned = true;
    }
    if (isSigned)
        str = str.substr(1);

    for (char el: str)
        if (el < '0' || el > '9')
            throw std::invalid_argument("invalid input string");


    for (int i = str.length(); i > 0; i -= 9) {
        if (i < 9)
            number.push_back(atoi(str.substr(0, i).c_str()));
        else
            number.push_back(atoi(str.substr(i - 9, 9).c_str()));


    }

    removeZeros();

    remainderLength = countIntLength(number.back());

    if (remainderLength == 0)
        remainderLength = 9;

}

BigInt::BigInt(const BigInt &num) : sign(num.sign), number(num.number), remainderLength(num.remainderLength) {}

BigInt::~BigInt() {
    number.clear();
}

//TODO: понять как сделать
BigInt BigInt::operator~() const {}


BigInt &BigInt::operator++() {
    return (*this += 1);
}

const BigInt BigInt::operator++(int) const {
    BigInt tmp = *this;



    return tmp;
}

BigInt &BigInt::operator--() {
    return (*this -= 1);
}

const BigInt BigInt::operator--(int num) const {
    BigInt tmp = *this;
    tmp -= 1;

    return tmp;
}

BigInt &BigInt::operator+=(const BigInt &num) {
    if (this->sign == '-') {
        if (num.sign == '-') {
            *this = -*this;
            BigInt tmp = -num;
            *this += tmp;
            *this = -*this;

            return *this;
        }

        *this = -*this;
        *this -= num;
        *this = -*this;

        return *this;
    }

    if (num.sign == '-') {
        BigInt tmp = -num;
        *this -= tmp;

        return *this;
    }

    int overLimit = 0;

    for (int i = 0; i < std::max(this->size(), num.size()) || overLimit != 0; ++i) {

        if (i == this->number.size())
            this->number.push_back(0);

        this->number[i] += overLimit + (i < num.number.size() ? num.number[i] : 0);
        overLimit = this->number[i] >= CELL_LIMIT;

        if (overLimit != 0)
            this->number[i] -= CELL_LIMIT;
    }

    return *this;
}

BigInt &BigInt::operator*=(const BigInt &num) {
    BigInt result;
    result.number.resize(this->number.size() + num.number.size());

    for (int i = 0; i < this->number.size(); ++i) {
        int overLimit = 0;
        for (int j = 0; j < num.number.size(); ++j) {
            long long tmpRes = result.number[i + j] +
                               static_cast<long long>(this->number[i] * (j < num.number.size() ? num.number[j] : 0) +
                                                      overLimit);
            result.number[i + j] = static_cast<int>(tmpRes % CELL_LIMIT);
            overLimit = static_cast<int>(tmpRes / CELL_LIMIT);
        }

    }

    if (this->sign == '-' && num.sign == '+')
        result.sign = '-';

    if (num.sign == '-' && this->sign == '+')
        result.sign = '-';

    result.removeZeros();
    this->number.clear();

    *this = result;

    return *this;
}


BigInt &BigInt::operator-=(const BigInt &num) {
    if (num.sign == '-') {
        *this += (-num);
        return *this;
    }

    if (this->sign == '-') {
        *this = -*this;
        *this += num;
        *this = -*this;
        return *this;
    }

    if (*this < num) { //
        *this = -*this;
        *this -= (-num);
        return *this;
    }

    int overLimit = 0;

    for (int i = 0; i < num.size() || overLimit; ++i) {
        this->number[i] -= overLimit + (i < num.size() ? num.number[i] : 0);
        overLimit = this->number[i] < 0;

        if (overLimit)
            this->number[i] += CELL_LIMIT;
    }

    removeZeros();

    return *this;
}


BigInt &BigInt::operator/=(const BigInt &num) {
    if (num == BigInt(0))
        throw std::invalid_argument("Division by zero")



}


BigInt &BigInt::operator=(const BigInt &num) {
    if (this == &num)
        return *this;

    this->number = num.number;
    this->sign = num.sign;
    this->remainderLength = num.remainderLength;

    return *this;
};


BigInt BigInt::operator+() const {
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt copy(*this);
    copy.sign == '-' ? copy.sign = '+' : copy.sign = '-';
    return copy;
}

bool BigInt::operator==(const BigInt &num) const {
    if (sign != num.sign)
        return false;

    if (remainderLength != num.remainderLength)
        return false;

    if (number.size() != num.number.size())
        return false;

    if (!vctcmp(number, num.number))
        return false;

    return true;
}

bool BigInt::operator!=(const BigInt &num) const {
    return !operator==(num);
}

bool BigInt::operator<(const BigInt &num) const {
    if (sign < num.sign) // '-' - 55, '+' - 53
        return false;

    if (sign > num.sign)
        return true;

    if (number.size() > num.number.size()) {
        if (sign == '+')
            return false;
        else
            return true;
    }

    if (number.size() < num.size()) {
        if (sign == '+')
            return true;
        else
            return false;
    }

    if (vctcmp(number, num.number)) // maybe to delete
        return false;

    bool isBigger = false;
    for (int i = 0; i < number.size(); ++i) {
        if (number[i] > num.number[i]) {
            isBigger = true;
            break;
        }
    }

    if (isBigger) {
        if (sign == '+')
            return false;
        else
            return true;
    }

    return true;
}

bool BigInt::operator>(const BigInt &num) const {
    return !operator<(num);
}

bool BigInt::operator<=(const BigInt &num) const {
    if (sign == num.sign && vctcmp(number, num.number))
        return true;

    return operator<(num);
}

bool BigInt::operator>=(const BigInt &num) const {
    if (sign == num.sign && vctcmp(number, num.number))
        return true;

    return operator>(num);
}

BigInt::operator int() const {
    if (number.size() > 1)
        throw std::length_error("Number exceeds int limit");

    int num = number[0];

    if (sign == '-')
        num *= -1;

    return num;
}


BigInt::operator std::string() const {
    std::string str;

    if (sign == '-')
        str += '-';

    str.append(std::to_string(number[number.size() - 1]));

    for (int i = number.size() - 2; i >= 0; --i) {
        int lengthOnNum = countIntLength(number[i]);

        for (int j = 0; j < MAX_OF_DIGITS - lengthOnNum; ++j)
            str += '0';

        str.append(std::to_string(number[i]));
    }

    return str;
}

size_t BigInt::size() const {
    return number.size();
}


BigInt operator+(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp += num2;

    return tmp;
}

BigInt operator-(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp -= num2;

    return tmp;
}

BigInt operator*(const BigInt &num1, const BigInt &num2) {
    BigInt tmp = num1;
    tmp *= num2;

    return tmp;
}