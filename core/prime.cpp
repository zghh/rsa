#include "prime.h"
#include "const.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>

using namespace std;

BigInteger GeneratePrime(int len)
{
    if (len % 4 != 0)
    {
        throw "Length must be the multiple of 4.";
    }
    BigInteger n = GenerateOddInteger(len);
    for (;;)
    {
        BigInteger b[NUMBER_THREAD];
        thread t[NUMBER_THREAD];
        bool flag[NUMBER_THREAD];
        for (int i = 0; i < NUMBER_THREAD; i++)
        {
            b[i] = n + 2LL * i;
            t[i] = thread(IsPrime, ref(b[i]), ref(flag[i]));
        }
        for (int i = 0; i < NUMBER_THREAD; i++)
            t[i].join();
        for (int i = 0; i < NUMBER_THREAD; i++)
            if (flag[i])
                return b[i];
        n = n + 2LL * NUMBER_THREAD;
    }
    return n;
}

BigInteger GenerateOddInteger(int len)
{
    len = len / 4;
    char *s = new char[len + 1];
    s[0] = len == 1 ? OUT[((rand() % 8) << 1) | 1] : OUT[rand() % 15 + 1];
    for (int i = 1; i < len; i++)
    {
        if (i < len - 1)
            s[i] = OUT[rand() % 16];
        else
            s[i] = OUT[((rand() % 8) << 1) | 1];
    }
    s[len] = '\0';
    BigInteger result(s);
    delete[] s;
    return result;
}

void IsPrime(const BigInteger &n, bool &result)
{
    if (n == 1LL)
    {
        result = false;
        return;
    }
    if (n == 2LL)
    {
        result = false;
        return;
    }
    int len = n.GetLength() * BASE_BIT;
    int count = 0;
    if (len < 100)
        count = 50;
    else if (len < 256)
        count = 27;
    else if (len < 512)
        count = 15;
    else if (len < 768)
        count = 8;
    else if (len < 1024)
        count = 4;
    else
        count = 2;
    for (int i = 0; i < count; i++)
        if (!MillerRabin(n))
        {
            result = false;
            return;
        }
    result = true;
}

bool MillerRabin(const BigInteger &n)
{
    BigInteger a;
    if (n >= MAX_RAND_INTEGER)
        a = BigInteger((rand() % (MAX_RAND_INTEGER - 1) + 1));
    else
        a = n.GenerateRandomInteger();
    BigInteger one(1);
    BigInteger p = n - 1LL;
    // if (Power(a, p, n) != one)
    //     return false;
    BigInteger m = p;
    for (; !m.IsOdd();)
    {
        m = m >> 1;
        BigInteger q = Power(a, m, n);
        if (q == p)
            break;
        else if (q != one)
            return false;
    }
    return true;
}