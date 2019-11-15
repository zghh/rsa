#pragma once
#include "integer.h"

#ifndef RSA_H
#define RSA_H

class RSA
{
private:
    BigInteger p, q, n;
    BigInteger d, e;
    BigInteger phi;
    int bit;

public:
    RSA();
    RSA(int len);
    RSA(const RSA &a);
    ~RSA();
    RSA &operator=(const RSA &a);
    void GenerateKey(int len);
    void Encrypt(char message[], char result[]);
    void Decrypt(char text[], char result[]);
    BigInteger GetP();
    BigInteger GetQ();
    BigInteger GetN();
    BigInteger GetD();
    BigInteger GetE();
    BigInteger GetPHI();
    int GetBit();
};

#endif