#include "rsa.h"
#include "prime.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

RSA::RSA()
{
    this->bit = 0;
}

RSA::RSA(int len)
{
    GenerateKey(len);
    this->bit = len;
}

RSA::RSA(const RSA &a)
{
    this->p = a.p;
    this->q = a.q;
    this->n = a.n;
    this->phi = a.phi;
    this->d = a.d;
    this->e = a.e;
    this->bit = a.bit;
}

RSA::~RSA()
{
}

RSA &RSA::operator=(const RSA &a)
{
    this->p = a.p;
    this->q = a.q;
    this->n = a.n;
    this->phi = a.phi;
    this->d = a.d;
    this->e = a.e;
    this->bit = a.bit;
    return *this;
}

void RSA::GenerateKey(int len)
{
    if (len % 8 != 0)
        throw "Length must be the multiple of 8.";
    p = GeneratePrime(len / 2);
    // printf("p = ");
    // p.Print();
    q = GeneratePrime(len / 2);
    // printf("q = ");
    // q.Print();
    n = p * q;
    // printf("n = ");
    // n.Print();
    phi = (p - 1LL) * (q - 1LL);
    // printf("phi = ");
    // phi.Print();
    e = phi.GenerateRandomInteger();
    for (; GCD(phi, e) != 1LL;)
        e = phi.GenerateRandomInteger();
    // printf("e = ");
    // e.Print();
    BigInteger x, y;
    ExGCD(e, phi, x, y);
    d = x % phi;
    // printf("d = ");
    // d.Print();
}

void RSA::Encrypt(char message[], char result[])
{
    int len = strlen(message);
    BigInteger b(message, len);
    if (b >= n)
        throw "Too long.";
    BigInteger c = Power(b, e, n);
    c.ToHex(result);
}

void RSA::Decrypt(char text[], char result[])
{
    BigInteger b(text);
    BigInteger m = Power(b, d, n);
    m.ToString(result);
}

BigInteger RSA::GetP()
{
    return p;
}

BigInteger RSA::GetQ()
{
    return q;
}

BigInteger RSA::GetN()
{
    return n;
}

BigInteger RSA::GetD()
{
    return d;
}

BigInteger RSA::GetE()
{
    return e;
}

BigInteger RSA::GetPHI()
{
    return phi;
}

int RSA::GetBit()
{
    return bit;
}