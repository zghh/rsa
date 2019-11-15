#pragma once
#include "const.h"

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

class BigInteger
{
private:
    int len;
    bool flag;
    UI value[MAX_LEN];
    BigInteger Add(const BigInteger &a, const BigInteger &b) const;
    BigInteger Add(const BigInteger &a, const UI &b) const;
    BigInteger Sub(const BigInteger &a, const BigInteger &b) const;
    BigInteger Sub(const BigInteger &a, const UI &b) const;
    BigInteger Mul(const BigInteger &a, const BigInteger &b) const;
    BigInteger Mul(const BigInteger &a, const UI &b) const;
    BigInteger Div(const BigInteger &a, const BigInteger &b) const;
    BigInteger Div(const BigInteger &a, const UI &b) const;
    BigInteger Mod(const BigInteger &a, const BigInteger &b) const;
    UI Mod(const BigInteger &a, const UI &b) const;
    void DivideAndRemainder(const BigInteger &a, const BigInteger &b, BigInteger result[]) const;
    void DivideAndRemainder(const BigInteger &a, const UI &b, BigInteger &result, UI &mod) const;
    void Append(BigInteger &a, const UI &b) const;
    UI ToUI(const BigInteger &a) const;
    int CompareTo(const BigInteger &a, const BigInteger &b) const;
    int CompareTo(const BigInteger &a, const int &b) const;
    int CompareToWithoutSign(const BigInteger &a, const BigInteger &b) const;
    int CompareToWithoutSign(const BigInteger &a, const int &b) const;

public:
    BigInteger();
    BigInteger(const char s[]);
    BigInteger(int a);
    BigInteger(UI a, bool flag);
    BigInteger(const BigInteger &a);
    BigInteger(const char s[], int len);
    ~BigInteger();
    BigInteger &operator=(const BigInteger &a);
    BigInteger operator+(const BigInteger &a) const;
    BigInteger operator+(const int &a) const;
    BigInteger operator-(const BigInteger &a) const;
    BigInteger operator-(const int &a) const;
    BigInteger operator*(const BigInteger &a) const;
    BigInteger operator*(const int &a) const;
    BigInteger operator/(const BigInteger &a) const;
    BigInteger operator/(const int &a) const;
    BigInteger operator%(const BigInteger &a) const;
    BigInteger operator%(const int &a) const;
    BigInteger operator<<(const int &a) const;
    BigInteger operator>>(const int &a) const;
    BigInteger operator-() const;
    bool operator<(const BigInteger &a) const;
    bool operator<(const int &a) const;
    bool operator<=(const BigInteger &a) const;
    bool operator<=(const int &a) const;
    bool operator>(const BigInteger &a) const;
    bool operator>(const int &a) const;
    bool operator>=(const BigInteger &a) const;
    bool operator>=(const int &a) const;
    bool operator==(const BigInteger &a) const;
    bool operator==(const int &a) const;
    bool operator!=(const BigInteger &a) const;
    bool operator!=(const int &a) const;
    BigInteger GenerateRandomInteger() const;
    void Print() const;
    void Out(char *s) const;
    bool IsOdd() const;
    int GetLength() const;
    void DivideAndRemainder(const BigInteger &a, BigInteger result[]) const;
    void ToString(char result[]) const;
    void ToHex(char result[]) const;
};

#endif