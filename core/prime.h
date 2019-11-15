#pragma once
#include "integer.h"

#ifndef PRIME_H
#define PRIME_H

BigInteger GeneratePrime(int len);
BigInteger GenerateOddInteger(int len);
void IsPrime(const BigInteger &n, bool &result);
bool MillerRabin(const BigInteger &n);

#endif