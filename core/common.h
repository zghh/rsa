#pragma once
#include "integer.h"

#ifndef COMMON_H
#define COMMON_H

BigInteger Power(BigInteger a, BigInteger n, BigInteger mod);
BigInteger GCD(BigInteger a, BigInteger b);
void ExGCD(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y);

#endif